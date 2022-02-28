
#include <iostream>
#include <string.h>

#include "Socket.hh"  
 

/* server parameters */
#define SERVER_ADDRESS  "0.0.0.0"     /* server IP */
#define PORT            8080 
#define BUF_SIZE        100               /* Buffer rx, tx max size  */
#define BACKLOG         5                 /* Max. client pending connections  */

int main(int argc, char* argv[])          /* input arguments are not used */
{ 
    int  len_rx, len_tx = 0;                     /* received and sent length, in bytes */
    char buff_tx[BUF_SIZE] = "Hello client, I am the server";
    const char* buff_rx;   /* buffers for reception  */
	oct::net::Socket::ErroCode err;
    oct::net::Socket server;
    
     
    /* socket creation */
    err = server.create(AF_INET, SOCK_STREAM); 
    if (err != oct::net::Socket::ErroCode::NO_ERROR)
    { 
        std::cout << "[SERVER-error]: socket creation failed. (" << errno << ") " << strerror( errno ) << "\n";
        return -1;
    } 
    else
    {
        std::cout << "[SERVER]: Socket successfully created..\n";
    }
    
    /* Bind socket */
    err = server.bind(SERVER_ADDRESS,PORT);
    if (err != oct::net::Socket::ErroCode::NO_ERROR)
    {
        std::cout << "[SERVER-error]: socket bind failed. (" << errno << ") " << strerror( errno ) << "\n";
        return -1;
    } 
    else
    {
        std::cout << "[SERVER]: Socket successfully binded \n";
    }
  
    /* Listen */
    err = server.listen(BACKLOG);
    if (err != oct::net::Socket::ErroCode::NO_ERROR)
    {
        std::cout << "[SERVER-error]: socket listen failed. (" << errno << ") " << strerror( errno ) << "\n";
        return -1;
    } 
    else
    {
        std::cout << "[SERVER]: Listening on SERV_PORT. " << ntohs(server.get_address().sin_port) << "\n";
    }
      
      /* Accept the data from incoming sockets in a iterative way */
	std::shared_ptr<oct::net::Socket> new_socket;
   	while(1)
   	{
        new_socket = server.accept(); 
        if (new_socket->get_file() < 0) 
        { 
            fprintf(stderr, "[SERVER-error]: connection not accepted. %d: %s \n", errno, strerror( errno ));
            return -1;
        } 
        else
        {              
            while(1) /* read data from a client socket till it is closed */ 
            {  
                /* read client message, copy it into buffer */
                buff_rx = new_socket->read(100);  
                
                if(not buff_rx)
                {
                    fprintf(stderr, "[SERVER-error]: connfd cannot be read. %d: %s \n", errno, strerror( errno ));
                }
                else if(strlen(buff_rx) == 0) /* if length is 0 client socket closed, then exit */
                {
                    printf("[SERVER]: client socket closed \n\n");
                    
                    break; 
                }
                else
                {
                    new_socket->write(buff_tx, strlen(buff_tx));
                    printf("[SERVER]: %s \n", buff_rx);
                }            
            }  
        }                      
    }    
} 
