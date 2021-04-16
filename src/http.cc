

#include <chrono>

#include "config.h"
#include "http.hh"



namespace octetos::http
{







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
	
}