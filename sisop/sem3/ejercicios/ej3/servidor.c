#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define PORT 8080
#define BUF_SIZE 1024

void handle_client(int client_sockfd) {
    char buffer[BUF_SIZE];
    ssize_t bytes_received;

    // Leer la solicitud del cliente
    bytes_received = read(client_sockfd, buffer, sizeof(buffer) - 1);
    if (bytes_received < 0) {
        perror("read");
        close(client_sockfd);
        return;
    }

    // Asegurarse de que el buffer esté null-terminado
    buffer[bytes_received] = '\0';

    // Imprimir la solicitud (para depuración)
    printf("Request received:\n%s\n", buffer);

    // Crear una respuesta HTTP simple
    const char *response =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: 37\r\n"
        "Connection: close\r\n"
        "\r\n"
        "<html><body><h1>Hello, World!</h1></body></html>";

    // Enviar la respuesta al cliente
    write(client_sockfd, response, strlen(response));

    // Cerrar el socket del cliente
    close(client_sockfd);
}

int main() {
    int server_sockfd, client_sockfd;
    struct sockaddr_in server_address, client_address;
    socklen_t client_len;
    int opt = 1;

    // Crear un socket
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sockfd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Configurar el socket para reutilizar la dirección
    if (setsockopt(server_sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt");
        close(server_sockfd);
        exit(EXIT_FAILURE);
    }

    // Configurar la dirección del servidor
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(PORT);

    // Enlazar el socket a la dirección
    if (bind(server_sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("bind");
        close(server_sockfd);
        exit(EXIT_FAILURE);
    }

    // Escuchar conexiones entrantes
    if (listen(server_sockfd, 5) < 0) {
        perror("listen");
        close(server_sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    while (1) {
        client_len = sizeof(client_address);
        client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address, &client_len);
        if (client_sockfd < 0) {
            perror("accept");
            close(server_sockfd);
            exit(EXIT_FAILURE);
        }

        handle_client(client_sockfd);
    }

    close(server_sockfd);
    return 0;
}
