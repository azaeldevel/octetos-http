
#ifndef OCTETOS_NETWORK_SOCKET_HH
#define OCTETOS_NETWORK_SOCKET_HH

#include <sys/socket.h>


namespace oct::net
{
	

class Socket
{
public:
	typedef int Socketfile;
	enum ErroCode
	{
		NO_ERROR,
		FAIL_ON_CREATE_SOCKET,
		FAIL_ON_CREATE_BUFFER,
		FAIL_ON_CONNECT_SOCKET,
	};
	
public:
	Socket();
	~Socket();

	ErroCode create(int domain, int type, int protocol = 0);
	ErroCode connect(const char* address,unsigned int port);
	void write(const char* string,unsigned int lengh);
	const char* read(unsigned int lengh);
	
private:
	Socketfile file;
	//char* write_buffer;
	char* read_buffer;
};
}

#endif