#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>

#define PORT 9734
#define BUF_SIZE 100
#define BACKLOG 5

void fibonacci(int n, char *result) {
    if (n <= 0) {
        result[0] = '\0';
        return;
    }
    int a = 0, b = 1, c;
    int len = 0;
    for (int i = 0; i < n; i++) {
        len += sprintf(result + len, "%d ", a);
        c = a + b;
        a = b;
        b = c;
    }
    result[len - 1] = '\0'; // Eliminar el espacio final
}

void *handle_client(void *client_sockfd_ptr) {
    int client_sockfd = *(int *)client_sockfd_ptr;
    free(client_sockfd_ptr);

    char buf[BUF_SIZE];
    ssize_t numread;
    int n;

    numread = read(client_sockfd, buf, BUF_SIZE - 1);
    if (numread == -1) {
        perror("read");
        close(client_sockfd);
        pthread_exit(NULL);
    }
    buf[numread] = '\0';
    n = atoi(buf);

    char result[BUF_SIZE];
    fibonacci(n, result);

    write(client_sockfd, result, strlen(result));

    if (close(client_sockfd) == -1)
        perror("close");

    pthread_exit(NULL);
}

int main() {
    int server_sockfd, client_sockfd;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    socklen_t server_len, client_len;

    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sockfd == -1)
        perror("socket");

    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(PORT);
    server_len = sizeof(server_address);

    if (bind(server_sockfd, (struct sockaddr *)&server_address, server_len) == -1)
        perror("bind");

    if (listen(server_sockfd, BACKLOG) == -1)
        perror("listen");

    while (1) {
        pthread_t thread_id;
        printf("Server waiting\n");

        client_len = sizeof(client_address);
        int *client_sockfd_ptr = malloc(sizeof(int));
        if (client_sockfd_ptr == NULL) {
            perror("malloc");
            continue;
        }

        *client_sockfd_ptr = accept(server_sockfd, (struct sockaddr *)&client_address, &client_len);
        if (*client_sockfd_ptr == -1) {
            perror("accept");
            free(client_sockfd_ptr);
            continue;
        }

        int ret = pthread_create(&thread_id, NULL, handle_client, client_sockfd_ptr);
        if (ret != 0) {
            fprintf(stderr, "Error from pthread_create %d\n", ret);
            close(*client_sockfd_ptr);
            free(client_sockfd_ptr);
        } else {
            pthread_detach(thread_id);
        }
    }

    close(server_sockfd);
    return 0;
}
