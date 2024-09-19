#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main (int n, char *argv[]) {
    int x, y, np;
    np = atoi (argv[1]);
    for (x = 0; x < np; x++)
        if (fork () == 0) {
            for (y = 0; y < x; y++)
                if (fork() > 0) break;
            sleep (4);
            exit (0);
        }
    sleep (4);
    exit (0);
}