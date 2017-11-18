#include "cs537.h"
#include "request.h"

// 
// server.c: A very, very simple web server
//
// To run:
//  server <portnum (above 2000)>
//
// Repeatedly handles HTTP requests sent to this port number.
// Most of the work is done within routines written in request.c
//

// CS537: Parse the new arguments too
void getargs(int *port, int *threads, int *buffers, int argc, char *argv[])
{
    if (argc != 4) {
	fprintf(stderr, "Usage: %s <port> <threads> <buffers>\n", argv[0]);
	exit(1);
    }
    *port = atoi(argv[1]);
    *threads = atoi(argv[2]);
    if(*threads <= 0) {
      fprintf(stderr, "Threads must be a positive integer\n");
      exit(1);  
    }
    *buffers = atoi(argv[3]);
    if(*buffers <= 0) {
      fprintf(stderr, "Buffers must be a positive integer\n");
      exit(1);
    }

}


int main(int argc, char *argv[])
{
    int listenfd, connfd, port, clientlen, threads, buffers;
    struct sockaddr_in clientaddr;

    getargs(&port, &threads, &buffers, argc, argv);

    // 
    // CS537: Create some threads...
    //

    listenfd = Open_listenfd(port);
    while (1) {
	clientlen = sizeof(clientaddr);
	connfd = Accept(listenfd, (SA *)&clientaddr, (socklen_t *) &clientlen);

	// 
	// CS537: In general, don't handle the request in the main thread.
	// Save the relevant info in a buffer and have one of the worker threads 
	// do the work. 
	// 
	requestHandle(connfd);

	Close(connfd);
    }

}


    


 
