

#define SERVER_ADDRESS  "0.0.0.0"     /* server IP */
#define PORT            8080 
char buf_tx[] = "Hello server. I am a client";

#include <iostream>

#include "Socket.hh"
 
/* This clients connects, sends a text and disconnects */
int main() 
{ 
	oct::net::Socket::ErroCode err;
    oct::net::Socket socket;
    
    /* Socket creation */
    err = socket.create(AF_INET, SOCK_STREAM); 
    if (err != oct::net::Socket::ErroCode::NO_ERROR) 
    { 
        std::cout << "CLIENT: socket creation failed...\n"; 
        return EXIT_FAILURE;  
    } 
    else
    {
        printf("CLIENT: Socket successfully created..\n"); 
    }
    
    /* try to connect the client socket to server socket */
    err = socket.connect(SERVER_ADDRESS,PORT);
    if (err != oct::net::Socket::ErroCode::NO_ERROR) 
    { 
        std::cout << "connection with the server failed...\n";  
        return EXIT_FAILURE;
    } 
    
    printf("connected to the server..\n"); 
  
    /* send test sequences*/
    socket.write(buf_tx, sizeof(buf_tx));
    std::cout << "CLIENT:Received: " << socket.read(100) << "\n"; 
   	
   	return EXIT_SUCCESS;
} 
