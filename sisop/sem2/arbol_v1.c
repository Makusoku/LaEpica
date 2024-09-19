#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void f (int n, int k) {
    // La condicion de parada sera cuando el hijo alcance el nivel solicitado
    // Ademas el hijo ya no continuara su proceso, por ende usamos un sleep
    if (n == k + 1) {pause (); return;}


    // Dato curioso: si quieres que en cada nivel imprima un numero 'x', 
    // solo cambiar el 'n', el n indica el nivel en que te encuentras
    for (int i = 0; i < n; i++) {

        // Solo el hijo continuara dividiendose
        if (fork () == 0) {
            f (n + 1, k);
        }
    }   

    // cuando el padre termine su proceso, lo pausamos hasta imprimir todo
    pause ();
}

int main (int n, char *argv[]) {
    if (n != 2) {
        printf ("Se debe ingresar un argumento\n");
    }
    else {
        // Convertimos el caracter pasado como argumento a entero
        int x = atoi (argv[1]);

        // Ingresamos a la funcion recursiva
        f (1, x);
    }
    return 0;   
}