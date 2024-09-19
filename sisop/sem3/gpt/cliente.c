#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/servidor_socket"
#define BUFFER_SIZE 256

int main() {
    int client_fd;
    struct sockaddr_un server_addr;
    char buffer[BUFFER_SIZE] = "Hola, servidor";

    // Crear el socket
    client_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (client_fd == -1) {
        perror("Error al crear el socket");
        exit(EXIT_FAILURE);
    }

    // Configurar la dirección del servidor
    memset(&server_addr, 0, sizeof(struct sockaddr_un));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path) - 1);

    // Conectar al servidor
    if (connect(client_fd, (struct sockaddr *) &server_addr, sizeof(struct sockaddr_un)) == -1) {
        perror("Error al conectar al servidor");
        exit(EXIT_FAILURE);
    }

    // Enviar mensaje al servidor
    if (write(client_fd, buffer, strlen(buffer)) == -1) {
        perror("Error al enviar el mensaje");
        exit(EXIT_FAILURE);
    }

    printf("Mensaje enviado al servidor: %s\n", buffer);

    // Cerrar el socket
    close(client_fd);

    return 0;
}
