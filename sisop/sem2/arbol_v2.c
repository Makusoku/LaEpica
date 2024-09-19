#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void f (pid_t id, int n, int k, int *fd) {
    if (n == k + 1) {for(;;); return;}
    for (int i = 0; i < n; i++) 
        if (fork () == 0) {
            pid_t aux = getpid ();
            write (fd[1], &aux, sizeof(int));
            f (id, n + 1, k, fd);
        }
    // cuando sea el proceso del padre
    if (id == getpid ()) {
        int total = 0, num_aux = 1, pids[1000];
        // Calculamos el numero totales de procesos
        for (int i = 1; i <= k; i++) {
            num_aux *= i;
            total += num_aux;
        }
        // Leemos todos los id del pipe para asegurarnos de que se hayan creado correctamente
        for (int i = 0; i < total; i++) 
            read (fd[0], &pids[i], sizeof (int));
        // Ejecutamos el comando pstree (ojo, con el id del padre se imprimen todos sus subprocesos)
        char cmd[200];
        sprintf (cmd, "pstree -lc %d", id);
        system (cmd);
        // Matamos a los subprocesos debido a que estan en bucle infinito
        for (int i = 0; i < total; i++) 
            kill (pids[i], SIGTERM);
        // Salimos
        exit (0);
    }
    else for (;;);
}

int main (int n, char *argv[]) {
    if (n != 2) {
        printf ("Se debe ingresar un argumento\n");
    }
    else {
        // Convertimos el caracter pasado como argumento a entero
        int fd[2];
        pipe (fd);
        int x = atoi (argv[1]);
        pid_t id = getpid ();
        // Ingresamos a la funcion recursiva
        f (id, 1, x, fd);
    }
    return 0;   
}