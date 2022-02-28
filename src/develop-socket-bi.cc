
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
    oct::net::SocketBi server;
    
     
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
    err = server.bind(PORT);
    if (err != oct::net::Socket::ErroCode::NO_ERROR)
    {
        std::cout << "[SERVER-error]: socket bind failed. (" << errno << ") " << strerror( errno ) << "\n";
        return -1;
    } 
    else
    {
        std::cout << "[SERVER]: Socket successfully binded \n";
    }
	
	err = server.connect(argv[1],PORT);
    if (err != oct::net::Socket::ErroCode::NO_ERROR) 
    {
        std::cout << "connection with the server failed...\n";  
        return EXIT_FAILURE;
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
   	while(true)
   	{
        new_socket = server.accept(); 	
        buff_rx = new_socket->read(BUF_SIZE);  
		if(strcmp("Hi",buff_rx) == 0)
		{
			err = server.connect(SERVER_ADDRESS,PORT);
			if (err != oct::net::Socket::ErroCode::NO_ERROR) 
			{ 
				std::cout << "connection with the server failed...\n";  
				return EXIT_FAILURE;
			}
		}
		else if(strcmp("Bye",buff_rx) == 0)
		{

		}
			   
		std::cout << "[CLIENT] : " << buff_rx << "\n";
    }
} 
