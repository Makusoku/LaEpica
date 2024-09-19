#include <sys/un.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <errno.h>
#include <string.h>

#define SV_SOCK_PATH "/tmp/us_xfr"

#define BUF_SIZE 100

#define BACKLOG 5

int main (int argc, char *argv[]) {
    struct sockaddr_un addr;
    int sfd, cfd;
    ssize_t numread;
    char buf[BUF_SIZE];

    sfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sfd == -1) perror ("socket");

    if (remove (SV_SOCK_PATH) == -1 && errno != ENONET) 
        perror ("remove");
    
    memset (&addr, 0, sizeof (struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy (addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path) - 1);

    if (bind (sfd, (struct sockaddr *) &addr, sizeof (struct sockaddr_un)) == -1) 
        perror ("bind");

    if (listen (sfd, BACKLOG) == -1) {
        perror ("listen");
    }

    for (;;) {
        cfd = accept (sfd, NULL, NULL);
        if (cfd == -1) 
            perror ("accept");

        while ((numread = read (cfd, buf, BUF_SIZE)) > 0)
            if (write (STDOUT_FILENO, buf, numread) != numread)
                perror ("partial/failed write");
        
        if (numread == -1)
            perror ("read");
        
        if (close (cfd) == -1)  
            perror ("close");
    }
}