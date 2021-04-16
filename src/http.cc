

#include <chrono>

#include "config.h"
#include "http.hh"



namespace octetos::http
{

	Connection::Connection(MHD_Connection * c)
	{
		connection = c;
	}





	int Connection::response(unsigned int status_code, Response& r)
	{
		return MHD_queue_response (connection, MHD_HTTP_OK, r);
	}




	






	Service::Service() : service(NULL)
	{
	}

	Service::operator MHD_Daemon* ()
	{
		return service;
	}
	bool Service::start(unsigned int flags, unsigned short port, MHD_AcceptPolicyCallback apc, void *apc_cls, MHD_AccessHandlerCallback dh, void *dh_cls)
	{
		service = MHD_start_daemon(flags,port,apc,apc_cls,dh,dh_cls);
		return service ? true : false;
	}
	void Service::stop()
	{
		MHD_stop_daemon (service);
	}




	
	Response::~Response()
	{
		MHD_destroy_response (response);
	}
	
	Response::operator MHD_Response* ()
	{
		return response;
	}
	bool Response::from_buffer (size_t size, void *data, enum MHD_ResponseMemoryMode mode)
	{
		response = MHD_create_response_from_buffer(size,data,mode);
		return response ? true : false;
	}
	
}