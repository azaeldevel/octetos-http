

#include <chrono>

#include "config.h"
#include "http.hh"



namespace octetos::http
{

uint64_t timeSinceEpochMillisec() 
{
  using namespace std::chrono;
  return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}


cgicc::const_form_iterator search(cgicc::const_form_iterator first, cgicc::const_form_iterator last, const std::string& val)
{
	cgicc::const_form_iterator it = first;
  	while (it!=last) 
  	{
  		//std::cout << "Processing " << (*it).getName() << "<br>";
		if((*it).getName().compare(val) == 0)
		{
			return it;
		}
		++it;
  	}
  	return last;
}



	octetos::http::db::Session& Session::getSession()
	{
		return session;
	}
	const std::string& Session::getSessionID() const
	{
		return session.getSession();
	}
	const std::string& Session::getHost() const
	{
		return host;
	}
	const std::string& Session::getDatabaseFilename() const
	{
		return dbfn;
	}

	Session::Session()
	{
		dbfn = DBDIR;
		dbfn += "/database";
	}
	Session::Session(const std::string& id)
	{
		dbfn = DBDIR;
		dbfn += "/database";
		
		//session = id;
		unsigned char digest[MD5_DIGEST_LENGTH];
		char mdString[33];
		char* h = getenv("REMOTE_ADDR");
		time_t now = time(0);
		char* dt = ctime(&now);
        std::string md5semilla = h;
        md5semilla += dt;
		MD5((unsigned char*)md5semilla.c_str(), strlen(md5semilla.c_str()), (unsigned char*)&digest);
		for(int i = 0; i < 16; i++)
        {
        	sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);
        }
        //session = mdString;
        host = h;
        //
		
        octetos::http::db::Conector conn(dbfn);
   		conn.begin();
   		
   		if(id.empty())
   		{
		   	if(session.selectByRemoteAddr(conn,host))//existe?
		   	{
		  		if(session.downloadIDs(conn))
		  		{
		  			//std::cout << "Descargo : " << user.getRomoteAddress() << "<br>";
		  		}
		  		else
		  		{
		  			std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";
		  		}
		   	}
		   	else
		   	{
		   		
		   		if(session.insert(conn,host,mdString,std::to_string(timeSinceEpochMillisec())))
		   		{
		   			//std::cout << "Inserted addr: (" << host << ") - (" << user.getID() << ")<br>";
		   			if(session.downloadIDs(conn))
			  		{
			  			
			  		}
			  		else
			  		{
			  			std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";
			  		}
		   		}
		   		else
		   		{
		  			std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";
		  		}
		   	}
	   	}
	   	else
	   	{
	   		if(session.selectBySession(conn,id))
	   		{
	   			//std::cout << "Sesion : " << id << " encontrada <br>";
		   		if(session.downloadIDs(conn))
			  	{
			  		//std::cout << "Sesion : " << session.getID() << " datos descargados <br>";
			  	}
			  	else
			  	{
			  			std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";
			  	}
	   		}
	   		else
	   		{
	   			std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";
	   		}
	   	}
	   	conn.commit();
	   	conn.close();
	}
	
}