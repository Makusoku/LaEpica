#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int n, char *argv[]) {
    char buffer[1024];
    int pipe_fd[2];

    pipe (pipe_fd);

    if (fork() == 0) {
        // Proceso hijo
        close(pipe_fd[0]);  // Cerrar el descriptor de lectura en el hijo

        // Redirigir la salida estándar al descriptor de escritura del pipe
        dup2(pipe_fd[1], STDOUT_FILENO); //STDOUT_FILENO es la salida estandar del terminal
        close(pipe_fd[1]);  // Ya no necesitamos el descriptor de escritura

        // Ejecutar el script con un argumento
        execl("/home/marcos/Documents/pucp/sisop/sem2/factor.sh", "factor.sh", argv[1], (char *)NULL);

    } else {
        // Proceso padre
        close(pipe_fd[1]);  // Cerrar el descriptor de escritura en el padre
        int pato;
        // Leer la salida del pipe
        read (pipe_fd[0], buffer, sizeof(buffer) - 1);
        sscanf (buffer, "%d", &pato); 

        close(pipe_fd[0]);  // Cerrar el descriptor de lectura
        if (pato == atoi (argv[1])) printf ("Es primo\n");
        else printf ("Es compuesto\n");
        wait(NULL);         // Esperar a que el hijo termine
    }
    return 0;
}
