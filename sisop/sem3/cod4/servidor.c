#include <sys/un.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <pthread.h>

void *thread_func (void * tsocket) {
    long c_sockfd = (long) tsocket;
    char ch;

    read (c_sockfd, &ch, 1);
    sleep (5);
    ch++;
    write (c_sockfd, &ch, 1);
    close (c_sockfd);
    pthread_exit (NULL);
}

int main () {
    int server_sockfd, client_sockfd;
    int server_len, client_len;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    
    server_sockfd = socket (AF_INET, SOCK_STREAM, 0);
    
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl (INADDR_ANY);
    server_address.sin_port = htons(9734);
    server_len = sizeof (server_address);
    
    bind (server_sockfd, (struct sockaddr *) &server_address, server_len);

    listen (server_sockfd, 5);

    while (1) {
        pthread_t thread_id;
        printf ("server waiting\n");

        client_len = sizeof (client_address);
        client_sockfd = accept (server_sockfd, (struct sockaddr *) &client_address, &client_len);

        int ret = pthread_create (&thread_id, NULL, thread_func, (void *) client_sockfd);
        if (ret != 0) 
            {printf ("Error from pthread %d\n", ret); exit (1);}
    }
}