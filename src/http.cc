

#include <chrono>

#include "config.h"
#include "http.hh"



namespace octetos::http
{

	Connection::Connection(MHD_Connection * c)
	{
		connection = c;
	}
	char* Connection::auth_get(char** pass)
	{
		return  MHD_basic_auth_get_username_password (connection, pass);
	}


	Connection::operator MHD_Connection*()
	{
		return connection;
	}

	int Connection::response(unsigned int status_code, Response& r)
	{
		return MHD_queue_response (connection, MHD_HTTP_OK, r);
	}




	






	Service::Service()
	{
		service = NULL;
	}
	Service::Service(unsigned int flags, unsigned short port, MHD_AcceptPolicyCallback apc, void *apc_cls, void *dh_cls)
	{
		service = NULL;		
		this->flags = flags;
		this->port = port;
		this->apc = apc;
		this->apc_cls = apc_cls;
		this->dh_cls = dh_cls;
	}

	Service::operator MHD_Daemon* ()
	{
		return service;
	}
	bool Service::start(unsigned int flags, unsigned short port, MHD_AcceptPolicyCallback apc, void *apc_cls, MHD_AccessHandlerCallback dh, void *dh_cls)
	{
		if(service) MHD_stop_daemon (service);
		service = MHD_start_daemon(flags,port,apc,apc_cls,dh,dh_cls, MHD_OPTION_END);
		return service ? true : false;
	}
	bool Service::start(MHD_AccessHandlerCallback dh)
	{
		if(service) MHD_stop_daemon (service);
		service = MHD_start_daemon(flags,port,apc,apc_cls,dh,dh_cls, MHD_OPTION_END);
		return service ? true : false;
	}
	void Service::stop()
	{
		if(service)
		{
			MHD_stop_daemon (service);
			service = NULL;
		}
	}




	Response::Response()
	{
		response = NULL;
	}
	Response::~Response()
	{
		MHD_destroy_response (response);
	}
	
	Response::operator MHD_Response* ()
	{
		return response;
	}
	const Response& Response::operator =(MHD_Response* r)
	{
		response = r;
		return *this;
	}
	bool Response::from(size_t size, void *data, enum MHD_ResponseMemoryMode mode)
	{
		if(not response) MHD_destroy_response (response);
		response = MHD_create_response_from_buffer(size,data,mode);
		return response ? true : false;
	}
	bool Response::from(const std::string& s, enum MHD_ResponseMemoryMode mode)
	{
		if(not response) MHD_destroy_response (response);
		response = MHD_create_response_from_buffer(s.size(),(void*)s.c_str(),mode);
		return response ? true : false;
	}
	
}