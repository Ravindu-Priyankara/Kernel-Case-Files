#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <linux/if_alg.h>

int main(){

    pid_t pid = 0;
    int sockfd = 0, err = -1, ret = 0;

    // setup the sockaddr_alg to pass the socket
    const struct sockaddr_alg sa = {
        .salg_family = AF_ALG,
        .salg_type = "aead",
        .salg_name = "authencesn(hmac(sha256),cbc(aes))"
    };

    // display the pid
    pid = getpid();
    printf("Process id: %d\n", pid);

    // create a socket
    sockfd = socket(AF_ALG, SOCK_SEQPACKET, 0);
    if(sockfd < 0){
        perror("Sockfd(AF_ALG): ");
        return -1;
    }

    // display the fd
    printf("Socket file descripter: %d\n", sockfd);

    err = bind(sockfd, (struct sockaddr *)&sa, sizeof(sa));
    if(err < 0){
        perror("Bind: ");
        ret = -1;
        goto cleanup;
    }

    // getchar
    getchar();

cleanup:
    // close the fd
    close(sockfd);

    return ret;
}


/*
*    1. trace socket
*    2. looks memory
*    3. answer one question
*        - is it suspicios? or normal behavior?
*    4. list down observations
*/