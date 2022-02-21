// Server side C/C++ program to demonstrate Socket programming
// This is only set to work with IPV4 and TCP
// Build and run. go to browser and type localhost:8080/'filename'.extension' to see message
// or use  curl -X GET "localhost:8080/'filename'.'extension'"
// review socket.h for function usage

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <fstream>

#define PORT 8080
int main()
{
	int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char* content = "Hello world!";

    // Creating socket file descriptor
    /*int sockfd = socket(domain, type, protocol)
    
    domain:
        AF_LOCAL - also known as AF_UNIX used to same host operations
        AF_INET - used with IPV4
            ---in this case we can use LOCALHOST:PORT#
    type:
        SOCK_STREAM - TCP
        SOCK_DGRAM - UDP

    
    */
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
       
    // Set socket options.
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(opt));

    //create address struct
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
       
    // Forcefully attaching socket to the port 8080
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));

    // prepare for connections on socket
    listen(server_fd, 3);

    // wait for connection and open a new socket when it arrives
    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);


    //block of code to act as a wait function
    unsigned long temp = 0;
    for(unsigned long i = 0; i < 18446744073709551610; i++){
        temp = temp + 1;
    }
    
    send(new_socket , content , strlen(content) , 0 );
    

	return 0;
}
