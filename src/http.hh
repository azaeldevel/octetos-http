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
#include <string>


#define PORT 8888


namespace octetos::http
{
	class Response;

	class Connection
	{
	public:
		Connection(MHD_Connection * connection);
		
		operator MHD_Connection*();
		int response (unsigned int status_code, Response& response);
		char* auth_get(char** pass);
		int auth_fail(const char* str, MHD_Response* response);
		
	private:
		MHD_Connection* connection;
	};


	class Service 
	{
	public:
		Service();
		Service(unsigned int flags, unsigned short port, MHD_AcceptPolicyCallback apc, void *apc_cls, void *dh_cls);
		
		operator MHD_Daemon* ();
		bool start(unsigned int flags, unsigned short port, MHD_AcceptPolicyCallback apc, void *apc_cls, void *dh_cls);
		bool start(MHD_AccessHandlerCallback dh);
		void stop();
	private:
		MHD_Daemon* service;
		unsigned int flags;
		unsigned short port;
		MHD_AcceptPolicyCallback apc;
		void *apc_cls;
		void *dh_cls;
	};

	class Response
	{
	public:
		Response();
		~Response();
		
		bool from(size_t size, void *data, enum MHD_ResponseMemoryMode mode);
		bool from(const std::string&, enum MHD_ResponseMemoryMode mode);
		operator MHD_Response* ();
		const Response& operator =(MHD_Response* response);
	private:
		MHD_Response* response;
	};

}

#endif