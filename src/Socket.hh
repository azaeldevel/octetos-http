
#ifndef OCTETOS_NETWORK_SOCKET_HH
#define OCTETOS_NETWORK_SOCKET_HH

#include <exception>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <memory>

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
		HAS_NOT_BEEN_CREATE_SOCKET,
		FAILK_ON_LISTEN,
	};
	class Exception : public std::exception
	{
	public:
		Exception(ErroCode code,const char* filename, unsigned int line);
		
		virtual const char* what() const throw();
		
	private:
		ErroCode code;
		const char* filename;
		unsigned int line;
	};
public:
	Socket();
	~Socket();

	const sockaddr_in& get_address()const;
	const Socketfile& get_file()const;

	ErroCode create(int domain, int type, int protocol = 0);
	ErroCode connect(const char* address,unsigned int port);
	void write(const char* string,unsigned int lengh);
	void read(char*& buff, int& lengh);
	const char* read(int lengh);
	ErroCode listen(unsigned int backlog);
	std::shared_ptr<Socket> accept();	
	ErroCode bind(const char* address,unsigned int port);
	
private:
	Socketfile file;
	//char* write_buffer;
	char* read_buffer;
	struct sockaddr_in address;
	unsigned int address_len;
};
}

#endif