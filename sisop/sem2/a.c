#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

void hijo (int x, int *fd) {
    int y, mypid;
    for (y = 0; y < x; ++y)
        if (fork () > 0) break;
    mypid = getpid();
    write (fd[1], &mypid, sizeof (int));
    for (;;);
}

int main(int narg, char *argv[]){
    int x, z, np, fd[2], pids[40], total;
    char cmd[15];
    pipe (fd);
    np = atoi (argv[1]);
    sprintf (cmd, "pstree -lc %d", getpid());
    for (x = 0; x < np; x++)    
        if (fork() == 0) hijo(x, fd);
    total = (1 + np) * np / 2;
    for (z = 0; z < total; z++) 
        read (fd[0], &pids[z], sizeof(int));
    system (cmd);
    for (z = 0; z < total; z++)
        kill (pids[z], SIGTERM);
    exit (0);
    return 0;
}