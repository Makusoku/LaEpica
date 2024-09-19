#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/un.h>

#define SV_SOCK_PATH "/tmp/fib_svr"
#define BUF_SIZE 100

int main(int argc, char *argv[]) {
    int sockfd;
    struct sockaddr_un addr;
    ssize_t numread;
    char buf[BUF_SIZE];

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sockfd == -1) 
        perror("socket");

    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path) - 1);

    if (connect(sockfd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
        perror("connect");

    write(sockfd, argv[1], strlen(argv[1]));
    numread = read(sockfd, buf, BUF_SIZE - 1);
    if (numread == -1) {
        perror("read");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    buf[numread] = '\0';
    printf("Fibonacci sequence: %s\n", buf);

    close(sockfd);
    return 0;
}
