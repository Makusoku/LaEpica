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
    int server_fd, client_fd;
    struct sockaddr_un server_addr, client_addr;
    socklen_t client_len;
    char buffer[BUFFER_SIZE];

    // Crear el socket
    server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Error al crear el socket");
        exit(EXIT_FAILURE);
    }

    // Eliminar el archivo de socket si ya existe
    unlink(SOCKET_PATH);

    // Configurar la dirección del servidor
    memset(&server_addr, 0, sizeof(struct sockaddr_un));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path) - 1);

    // Vincular el socket a la dirección
    if (bind(server_fd, (struct sockaddr *) &server_addr, sizeof(struct sockaddr_un)) == -1) {
        perror("Error al vincular el socket");
        exit(EXIT_FAILURE);
    }

    // Escuchar conexiones entrantes
    if (listen(server_fd, 5) == -1) {
        perror("Error al escuchar en el socket");
        exit(EXIT_FAILURE);
    }

    printf("Servidor escuchando en %s\n", SOCKET_PATH);

    // Aceptar conexiones entrantes
    client_len = sizeof(struct sockaddr_un);
    client_fd = accept(server_fd, (struct sockaddr *) &client_addr, &client_len);
    if (client_fd == -1) {
        perror("Error al aceptar la conexión");
        exit(EXIT_FAILURE);
    }

    // Leer datos del cliente
    ssize_t num_read = read(client_fd, buffer, BUFFER_SIZE);
    if (num_read == -1) {
        perror("Error al leer del cliente");
        exit(EXIT_FAILURE);
    }

    buffer[num_read] = '\0'; // Agregar terminador de cadena
    printf("Mensaje recibido del cliente: %s\n", buffer);

    // Cerrar el socket del cliente
    close(client_fd);

    // Cerrar el socket del servidor
    close(server_fd);
    unlink(SOCKET_PATH); // Eliminar el archivo del socket

    return 0;
}
