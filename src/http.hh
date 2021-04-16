#ifndef SYSAPP_HTTP_HH
#define SYSAPP_HTTP_HH

#include <openssl/md5.h>

#include <string.h>

#include <sys/types.h>
#ifndef _WIN32
#include <sys/select.h>
#include <sys/socket.h>
#else
#include <winsock2.h>
#endif
#include <string.h>
#include <microhttpd.h>
#include <stdio.h>

#define PORT 8888


namespace octetos::http
{
	class Response;

	class Connection
	{
	public:
		Connection(MHD_Connection * connection);
		
		int response (unsigned int status_code, Response& response);
	private:
		MHD_Connection* connection;
	};


	class Service 
	{
	public:
		Service();
		
		operator MHD_Daemon* ();
		bool start(unsigned int flags, unsigned short port, MHD_AcceptPolicyCallback apc, void *apc_cls, MHD_AccessHandlerCallback dh, void *dh_cls);
		void stop();
	private:
		MHD_Daemon* service;
	};

	class Response
	{
	public:
		~Response();
		
		bool from_buffer(size_t size, void *data, enum MHD_ResponseMemoryMode mode);
		operator MHD_Response* ();
	private:
		MHD_Response* response;
	};

}

#endif