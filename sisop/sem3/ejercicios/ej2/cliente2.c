#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define PORT 9734
#define BUF_SIZE 100

int main(int argc, char *argv[]) {
    int sockfd;
    struct sockaddr_in server_address;
    ssize_t numread;
    char buf[BUF_SIZE];

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
        perror("socket");

    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(PORT);

    if (connect(sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
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
