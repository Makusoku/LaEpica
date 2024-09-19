#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main () {
    char buffer[64];
    char mess[] = "hi\n";
    int ii, pipe_fd[2];
    pipe(pipe_fd);

    if (fork() == 0) {
        // hijo
        close (pipe_fd[0]);
        printf ("hijo %d\n", getpid());
        for (ii = 0; ii < 5; ii++)
            write (pipe_fd[1], mess, sizeof (mess) - 1);
        close (pipe_fd[1]);
    }
    else {
        close (pipe_fd[1]);
        printf ("padre %d\n", getpid());
        memset (buffer, 0, sizeof (buffer));
        while ((ii = read (pipe_fd[0], buffer, 63)) != 0){
            printf ("papa leyo [%d]:\n%s\n", (int)ii, buffer);
            memset (buffer, 0, sizeof(buffer));
        }
        close (pipe_fd[0]);

    }
    return 0;
}