
#include <stdlib.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include "Socket.hh"

namespace oct::net
{

Socket::Socket() : read_buffer(NULL),file(-1)
{
}

Socket::~Socket()
{
	free(read_buffer);
	if(file != -1)close(file);
}

Socket::ErroCode Socket::create(int d, int t, int p)
{
	file = socket(d,t,p);
	if (file == -1) return FAIL_ON_CREATE_SOCKET;
	
		
	return NO_ERROR;
}
Socket::ErroCode Socket::connect(const char* a,unsigned int p)
{
	struct sockaddr_in address; 
	address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(a); 
    address.sin_port = htons(p);
    
    if(::connect(file, (struct sockaddr*)&address, sizeof(address)) == -1) return FAIL_ON_CONNECT_SOCKET;
    
    return NO_ERROR;
}
void Socket::write(const char* s,unsigned int l)
{
	//if (file == -1)
	::write(file, s, l);
}
const char* Socket::read(unsigned int l)
{
	//if (file == -1)
	if(not read_buffer) free(read_buffer);
	read_buffer = (char*) malloc(l);
	if(not read_buffer) return NULL;
	
	::read(file, read_buffer, l);
	return read_buffer;
}

}