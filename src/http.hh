#ifndef SYSAPP_HTTP_HH
#define SYSAPP_HTTP_HH

#include <openssl/md5.h>
#include <iostream>
#include <string.h>
#include <cgicc/Cgicc.h> 


#include "http-db.hh"

namespace octetos::http
{

cgicc::const_form_iterator search(cgicc::const_form_iterator first, cgicc::const_form_iterator last, const std::string& val);

class Session
{
private:	
	std::string host;
	//std::string session;
	octetos::http::db::Session session;
	
public:
	const std::string& getSessionID() const;
	const std::string& getHost() const;
	Session(const std::string& id);	
	octetos::http::db::Session& getSession();
};

}

#endif