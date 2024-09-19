#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include <sys/un.h>

#define SV_SOCK_PATH "/tmp/fib_svr"
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
    struct sockaddr_un server_address;
    socklen_t server_len, client_len;
    struct sockaddr_un client_address;

    server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_sockfd == -1) 
        perror("socket");

    if (remove(SV_SOCK_PATH) == -1 && errno != ENOENT) 
        perror("remove");

    memset(&server_address, 0, sizeof(server_address));
    server_address.sun_family = AF_UNIX;
    strncpy(server_address.sun_path, SV_SOCK_PATH, sizeof(server_address.sun_path) - 1);

    if (bind(server_sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
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
