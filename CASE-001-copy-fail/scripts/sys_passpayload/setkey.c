#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <linux/if_alg.h>
#include <string.h>
#include <linux/uio.h>
#include <linux/types.h>
#include <stdint.h>

typedef struct {
    int sockfd;
    int session_fd;
}fds;

static inline void fd_init(fds *fds){
    if(!fds)
        return;

    fds->sockfd = 0;
    fds->session_fd = 0;
}

static void fds_cleanup(fds *fds){
    if(!fds)
        return;

    if(fds->sockfd > 0){
        close(fds->sockfd);
        fds->sockfd = 0;
    }

    if(fds->session_fd > 0){
        close(fds->session_fd);
        fds->session_fd = 0;
    }
}

int main(){

    int err = 0, i = 0; //default return 0;
    ssize_t retd = 0;
    fds fds;
    fd_init(&fds);

    // recv buffer
    unsigned char recv_buffer[64];

    const struct sockaddr_alg salg= {
        .salg_family = AF_ALG,
        .salg_type = "aead",
        .salg_name = "authencesn(hmac(sha256),cbc(aes))"
    };

    const char buf[40] = {
        0x08, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x10, // rtattr + AES key len, (Header)
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // HMAC KEY
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // HMAC KEY
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // AES KEY
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00  // AES KEY
    };

    const char encrypt[4] = {
        //0x00, 0x00, 0x00, 0x00 // decrypt
        0x01, 0x00, 0x00, 0x00 // => encrypt
    };

    /*
    *   - Layout:
    *       - first 4 byte = length(ivlen)
    *       - others = iv
    *   
    *   - Define it like this
    *       struct af_alg_iv {
    *           __u32	ivlen;
    *           __u8	iv[];
    *       }
    */
    const char af_alg_iv_data[20] = {
        0x10, 0x00, 0x00, 0x00,     // 0x00000010 = 16 bytes
        0x00, 0x00, 0x00, 0x00,     // iv
        0x00, 0x00, 0x00, 0x00,     // iv
        0x00, 0x00, 0x00, 0x00,     // iv
        0x00, 0x00, 0x00, 0x00      // iv
    };

    const char assoclen[4] = {
        0x08, 0x00, 0x00, 0x00
    };

    struct msghdr msg = {0};
    struct iovec iov[1];

    // data to pass iovec
    //char text[20];
    //memset(text, 'A', sizeof(text));
    char text[24] = {
        0x52, 0x61, 0x76, 0x69, 0x6e, 0x64, 0x75, 0x00,     // for associate data
        0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41,     // AAAAAAAA
        0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41
    };
    
    // assign the data to iovec
    iov[0].iov_base = text;
    iov[0].iov_len = sizeof(text);

    // link back it to msghdr
    msg.msg_iov = iov;
    msg.msg_iovlen = 1; // we have one vecterized input output

    //setup control buffer
    char control_bufffer[CMSG_SPACE(sizeof(encrypt)) + CMSG_SPACE(sizeof(af_alg_iv_data)) + CMSG_SPACE(sizeof(assoclen))];
    memset(control_bufffer, 0, sizeof(control_bufffer));

    msg.msg_control = control_bufffer;
    msg.msg_controllen = sizeof(control_bufffer);

    // setup control message header
    struct cmsghdr *cmsg = CMSG_FIRSTHDR(&msg);
    cmsg->cmsg_len = CMSG_LEN(sizeof(encrypt));
    cmsg->cmsg_level = SOL_ALG;
    cmsg->cmsg_type = ALG_SET_OP; // => include/uapi/linux/if_alg.h
    /*
    *   ALT:
    *       uint32_t op = ALG_OP_DECRYPT;
    *       - *(uint32_t *)CMSG_DATA(cmsg) = op;
    */
    memcpy(CMSG_DATA(cmsg), encrypt, sizeof(encrypt));

    // second control message header
    cmsg = CMSG_NXTHDR(&msg, cmsg);
    cmsg->cmsg_len = CMSG_LEN(sizeof(af_alg_iv_data));
    cmsg->cmsg_level = SOL_ALG;
    cmsg->cmsg_type = ALG_SET_IV;
    memcpy(CMSG_DATA(cmsg), af_alg_iv_data, sizeof(af_alg_iv_data));

    // third control message header
    cmsg = CMSG_NXTHDR(&msg, cmsg);
    cmsg->cmsg_len = CMSG_LEN(sizeof(assoclen));
    cmsg->cmsg_level = SOL_ALG;
    cmsg->cmsg_type = ALG_SET_AEAD_ASSOCLEN;
    memcpy(CMSG_DATA(cmsg), assoclen, sizeof(assoclen));

    printf("reach to socket\n");
    fflush(stdout);
    fds.sockfd = socket(AF_ALG, SOCK_SEQPACKET, 0);
    if(fds.sockfd < 0){
        perror("Socket(AF_ALG):");
        return -1;
    }

    printf("reach to bind\n");
    fflush(stdout);
    err = bind(fds.sockfd, (struct sockaddr *)&salg, sizeof(salg));
    if(err < 0){
        fds_cleanup(&fds);
        perror("Bind:");
        goto exit;
    }

    printf("reach to setsockopt key\n");
    fflush(stdout);
    err = setsockopt(fds.sockfd, SOL_ALG, ALG_SET_KEY, buf, sizeof(buf));
    if(err < 0){
        fds_cleanup(&fds);
        perror("Setsockopt(ALG_SET_KEY):");
        goto exit;
    }

    getchar();

    printf("reach to setsockopt authsize\n");
    fflush(stdout);
    uint32_t authsize = 16;
    err = setsockopt(fds.sockfd, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, &authsize, authsize);
    if(err < 0){
        fds_cleanup(&fds);
        perror("SETSOCKOPT(AUTHSIZE):");
        goto exit;
    }

    getchar();

    printf("reach to accept\n");
    fflush(stdout);
    fds.session_fd = accept(fds.sockfd, NULL, 0);
    if(fds.session_fd < 0){
        fds_cleanup(&fds);
        perror("Accept:");
        err = -1;
        goto exit;
    }

    printf("reach to sendmsg\n");
    fflush(stdout);
    retd = sendmsg(fds.session_fd, &msg, 0); // remove msg more
    if(retd < 0){
        fds_cleanup(&fds);
        perror("Sendmsg:");
        err = -1; 
        goto exit;
    }

    printf("sendmsg returned: %zd\n", retd);

    printf("reach to recv\n");
    fflush(stdout);
    retd = recv(fds.session_fd, recv_buffer, sizeof(recv_buffer), MSG_DONTWAIT);
    if(retd < 0){
        fds_cleanup(&fds);
        perror("Recv:");
        err = -1;
        goto exit;
    }

    for(; i < retd; i++){
        printf("%02x", recv_buffer[i]);
    }
    printf("\n");

    fflush(stdout);

    fds_cleanup(&fds);

exit:
    return err;
}