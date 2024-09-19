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

void *handle_client(void *client_sockfd_ptr) {
    int client_sockfd = *(int *)client_sockfd_ptr;
    free(client_sockfd_ptr);  // Liberar memoria después de usar el puntero

    char buf[BUF_SIZE];
    ssize_t numread;

    numread = read(client_sockfd, buf, BUF_SIZE - 1);  // Leer hasta BUF_SIZE-1 para asegurar espacio para el terminador nulo
    if (numread == -1) {
        perror("read");
        close(client_sockfd);
        pthread_exit(NULL);
    }
    buf[numread] = '\0';  // Asegurarse de que el buffer esté terminado en nulo

    int x = atoi(buf);
    if (x & 1) {
        write(client_sockfd, "IMPAR", strlen("IMPAR"));  // Enviar longitud fija para "IMPAR"
    } else {
        write(client_sockfd, "PAR", strlen("PAR"));  // Enviar longitud fija para "PAR"
    }

    if (close(client_sockfd) == -1)  
        perror("close");
    
    pthread_exit(NULL);
}

int main() {
    int server_sockfd, client_sockfd;
    int server_len, client_len;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;

    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sockfd == -1) 
        perror("socket");

    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);  // Escuchar en todas las interfaces
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
        int *client_sockfd_ptr = malloc(sizeof(int));  // Alocar memoria para el descriptor del socket del cliente
        if (client_sockfd_ptr == NULL) {
            perror("malloc");
            continue;
        }

        *client_sockfd_ptr = accept(server_sockfd, (struct sockaddr *)&client_address, &client_len);
        if (*client_sockfd_ptr == -1) {
            perror("accept");
            free(client_sockfd_ptr);  // Liberar memoria si la aceptación falla
            continue;
        }

        int ret = pthread_create(&thread_id, NULL, handle_client, client_sockfd_ptr);
        if (ret != 0) {
            fprintf(stderr, "Error from pthread_create %d\n", ret);
            close(*client_sockfd_ptr);  // Cerrar el socket si no se pudo crear el hilo
            free(client_sockfd_ptr);    // Liberar memoria si la creación del hilo falla
        } else {
            pthread_detach(thread_id);  // Desvincular el hilo para que termine por sí mismo
        }
    }

    close(server_sockfd);
    return 0;
}
