
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#include "Socket.hh"

namespace oct::net
{


Socket::Socket() : read_buffer(NULL),file(-1),address({0}),address_len(0)
{
}

Socket::~Socket()
{
	close();
}

void Socket::close()
{
	if(read_buffer) 
	{
		read_buffer = NULL;
		free(read_buffer);
	}
	if(file != -1) 
	{
		::close(file);
		file = -1;
	}
}
const sockaddr_in& Socket::get_address()const
{
	return address;
}
const Socket::Socketfile& Socket::get_file()const
{
	return file;
}
Socket::ErroCode Socket::create(int d, int t, int p)
{
	file = socket(d,t,p);
	if (file == -1) return FAIL_ON_CREATE_SOCKET;
	
		
	return NO_ERROR;
}
Socket::ErroCode Socket::connect(const char* a,unsigned int p)
{
	address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(a); 
    address.sin_port = htons(p);
    
    if(file == -1) if(::connect(file, (struct sockaddr*)&address, sizeof(address)) == -1) return FAIL_ON_CONNECT_SOCKET;
    
    return NO_ERROR;
}
Socket::ErroCode Socket::bind(const char* a,unsigned int p)
{
	address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(a); 
    address.sin_port = htons(p);
    
    if(file == -1) if(::bind(file, (struct sockaddr*)&address, sizeof(address)) == -1) return FAIL_ON_CONNECT_SOCKET;
    
    return NO_ERROR;
}
void Socket::write(const char* s,unsigned int l)
{
	if (file == -1) throw Exception(HAS_NOT_BEEN_CREATE_SOCKET,__FILE__,__LINE__);
	::write(file, s, l);
}
void Socket::write(const char* s)
{
	if (file == -1) throw Exception(HAS_NOT_BEEN_CREATE_SOCKET,__FILE__,__LINE__);
	::write(file, s, strlen(s));
}
void Socket::read(char*& b, int& l)
{
	//if (file == -1)
	//if(not read_buffer) free(read_buffer);
	//read_buffer = (char*) malloc(l);
	//if(not read_buffer) throw Exception(FAIL_ON_CREATE_BUFFER,__FILE__,__LINE__);
	l = ::read(file, b, l);
}
const char* Socket::read(int l)
{
	if(not read_buffer) free(read_buffer);
	read_buffer = (char*) malloc(l);
	if(not read_buffer) throw Exception(FAIL_ON_CREATE_BUFFER,__FILE__,__LINE__);
	l = ::read(file, read_buffer, l);
	if(l == -1 ) return NULL;
	return read_buffer;
}
Socket::ErroCode Socket::listen(unsigned int b)
{
	if(::listen(file,b) == -1) return FAILK_ON_LISTEN;
	
	return NO_ERROR;
}
std::shared_ptr<Socket> Socket::accept()
{
	std::shared_ptr<Socket> new_socket = std::shared_ptr<Socket>(new Socket);
	
    new_socket->file = ::accept(file,(struct sockaddr*)&new_socket->address, &new_socket->address_len);
    return new_socket;
}





Socket::Exception::Exception(ErroCode c,const char* fn, unsigned int l) : code(c),filename(fn),line(l)
{
}
const char* Socket::Exception::what() const throw()
{
	switch(code)
	{
		case FAIL_ON_CREATE_SOCKET:
			return "Fallo al crear el socket";
		case FAIL_ON_CREATE_BUFFER:
			return "Fallo al crear buffer";
		case FAIL_ON_CONNECT_SOCKET:
			return "Fallo al conectar socket";
		case HAS_NOT_BEEN_CREATE_SOCKET:
			return "No se ha creado el socket";
		default:
			return "Error desconocido";
	}
}

}