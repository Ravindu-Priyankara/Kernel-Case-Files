#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>

int main(){

    pid_t pid = 0;
    int sockfd = 0;

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

    // getchar
    getchar();

    // close the fd
    close(sockfd);

    return 0;
}