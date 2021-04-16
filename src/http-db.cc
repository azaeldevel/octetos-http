#include "http-db.hh"

#include <stdio.h>
#include <sqlite3.h> 
#include <iostream>



namespace octetos::http::db
{
	bool Variable::remove(Conector& connect,const Session& session)
    {
        std::string sql = "DELETE FROM  ";
        sql += TABLE_NAME + " WHERE session = ";
        sql += std::to_string(session.getID());
        //std::cout << "SQL: " << sql << "<br>\n";
        if(connect.query(sql))
        {
            return true;
        }
		
		std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";
        return false;
    }
	bool Variable::remove(Conector& connect)
    {
        std::string sql = "DELETE FROM  ";
        sql += TABLE_NAME + " WHERE id = ";
        sql += std::to_string(id);
        //std::cout << "SQL: " << sql << "<br>\n";
        if(connect.query(sql))
        {
            return true;
        }
		
		std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";
        return false;
    }
   	int Variable::callbackID(void *obj, int argc, char **argv, char **azColName)
    {
        std::vector<Variable*>* vec = (std::vector<Variable*>*)obj;
        Variable* v = new Variable();        	
        v->id = std::atoi(argv[0]);	
        vec->push_back(v);
        
        return 0;
    }
	bool Variable::select(Conector& connect,const Session& s, std::vector<Variable*>& vec)
    {
        std::string sql = "SELECT id FROM  ";
        sql += TABLE_NAME + " WHERE session = ";
        sql += std::to_string(s.getID());
        if(connect.query(sql,callbackID,&vec))
        {
            return true;
        }
		
		std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";
        return false;
    }
	const std::string& Variable::getName()const
	{
		return name;
	}
	const std::string& Variable::getValue()const
	{
		return value;
	}
   	int Variable::callbackBySession(void *obj, int argc, char **argv, char **azColName)
    {
        Variable* p = (Variable*)obj;	
        p->id = std::atoi(argv[0]);	
        p->name = argv[1];
        p->value = argv[2];
        return 0;
    }
    bool Variable::select(Conector& connect,const Session& session, const std::string&)
    {
        std::string sql = "SELECT id,name,value FROM  ";
        sql += TABLE_NAME + " WHERE session = ";
        sql += std::to_string(session.getID());
        //std::cout << "SQL: " << sql << "<br>\n";
        if(connect.query(sql,callbackBySession,this))
        {
            return true;
        }
		
		std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";
        return false;
    }
	bool Variable::insert(Conector& connect,const Session& s ,const std::string& n,const std::string& v)
	{
		std::string sql = "INSERT INTO ";
        sql += TABLE_NAME + "(session,name,value) VALUES('";
        sql += std::to_string(s.getID()) + "','";
        sql += n + "','" + v + "')";
        //std::cout << sql << "<br>";
        if(connect.query(sql))
        {
        	id = sqlite3_last_insert_rowid((sqlite3*)connect.getServerConnector());
            return true;
        }
		
		std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";
        return false;
	}
	std::string Variable::TABLE_NAME = "Variables";








	bool Session::remove(Conector& connect)
	{
		if(not Variable::remove(connect,*this))
		{
			return false;
		}
		
		
        std::string sql = "DELETE FROM  ";
        sql += TABLE_NAME + " WHERE id = ";
        sql += std::to_string(id);
        //std::cout << "SQL: " << sql << "<br>\n";
        if(connect.query(sql))
        {
            return true;
        }
				
		std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";
		return false;
	}
	bool Session::insert(Conector& connect,const std::string& r,const std::string& s,const std::string& t)
	{
		std::string sql = "INSERT INTO ";
        sql += TABLE_NAME + "(remote_addr,session,lasttime) VALUES('";
        sql += r + "','" + s + "','" + t + "')";
        //std::cout << sql << "<br>";
        if(connect.query(sql))
        {
        	id = sqlite3_last_insert_rowid((sqlite3*)connect.getServerConnector());
            return true;
        }
		
		std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";
        return false;
	}
	bool Session::updateSession(Conector& connect,const std::string& str)
	{
		std::string sql = "UPDATE  ";
        sql += TABLE_NAME + " SET session = '";
        sql += str + "' WHERE id = " + std::to_string(id) + ";";
        std::cout << sql << "<br>";
        return connect.query(str);
	}
	const std::string& Session::getRomoteAddress()const
	{
		return remote_addr;
	}
	const std::string& Session:: getSession()const
	{
		return session;
	}
	int Session::getID()const
	{
		return id;
	}
	Session::Session()
	{
		id = -1;
	}
	bool Session::inserteRemoteAddr(Conector& connect,const std::string& str)
	{
		std::string sql = "INSERT INTO  ";
        sql += TABLE_NAME + "(remote_addr) VALUES('";
        sql += str + "')";
        if(connect.query(sql))
        {
        	id = sqlite3_last_insert_rowid((sqlite3*)connect.getServerConnector());
            return true;
        }
		
		std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";
        return false;
	}
   	int Session::callbackIDs(void *obj, int argc, char **argv, char **azColName)
    {
        Session* p = (Session*)obj;	
        p->remote_addr = argv[0] != NULL ? argv[0] : "";	
        p->session = argv[1] != NULL ? argv[1] : "";
        
        return 0;
    }
    bool Session::downloadIDs(Conector& connect)
    {
    	//std::cout << "download id : " << id << "\n";
    	std::string sql = "SELECT remote_addr,session FROM  ";
        sql += TABLE_NAME + " WHERE id = ";
        sql += std::to_string(id) ;
        //std::cout << sql << "\n";
        return connect.query(sql,callbackIDs,this);
    }
   	int Session::callbackBySession(void *obj, int argc, char **argv, char **azColName)
    {
        Session* p = (Session*)obj;	
        p->id = std::atoi(argv[0]);	
        
        return 0;
    }
    bool Session::selectBySession(Conector& connect, const std::string& r)
    {
        std::string sql = "SELECT id FROM  ";
        sql += TABLE_NAME + " WHERE session = '";
        sql += r + "'";
        if(connect.query(sql,callbackBySession,this))
        {
            return true;
        }
		
		std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";
        return false;
    }
    int Session::callbackByRemoteAddr(void *obj, int argc, char **argv, char **azColName)
    {
        Session* p = (Session*)obj;	
        p->id = std::atoi(argv[0]);	        
        //std::cout << "id : " << p->id << "\n";
        return 0;
    }
    bool Session::selectByRemoteAddr(Conector& connect, const std::string& r)
    {
        std::string sql = "SELECT id FROM ";
        sql += TABLE_NAME + " WHERE remote_addr = '";
        sql += r + "'";
        bool ret =  connect.query(sql,callbackByRemoteAddr,this);
        if(ret == false) return false;
        
        if(id < 0) return false;
        return true;
    }
	
	std::string Session::TABLE_NAME = "Session";
		
		
		
		
		
		
		
		
		
		
		
	
	bool Conector::begin()
	{
		return query("BEGIN TRANSACTION;",NULL,NULL);
	}
	bool Conector::commit()
	{
		return query("END TRANSACTION;",NULL,NULL);
	}
	bool Conector::rollback()
	{
		return query("ROLLBACK TRANSACTION;",NULL,NULL);
	}
	int Conector::getErrorCode()const
	{
		return sqlite3_errcode((sqlite3*)serverConnector);
	}
	const char* Conector::getErrorMessage()const
	{
		return sqlite3_errmsg((sqlite3*)serverConnector);
	}
	/*bool Conector::update(const std::string& str)
    {
        int rc = sqlite3_exec((sqlite3*)serverConnector, str.c_str(), 0, 0, NULL);
        if( rc != SQLITE_OK ) 			
        {
        	std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";
            return false;			
        } 
        else 
        {
            return true;			
        }			
    }*/
	void Conector::close()
	{
		if(serverConnector != NULL) 
		{
			sqlite3_close((sqlite3*)serverConnector);
			serverConnector = NULL;
		}
	}
	/**
    ***
    **/
    bool Conector::query(const std::string& str)
    {
        int rc = sqlite3_exec((sqlite3*)serverConnector, str.c_str(), 0, 0, NULL);
        if( rc != SQLITE_OK ) 			
        {
        	std::cout << "Fail : " << __FILE__ << ":" << __LINE__ << ":  " << str << "<br>";
        	std::cout << getErrorMessage() << "<br>";
            return false;			
        } 
        else 
        {
            return true;			
        }			
    }	
    /**
    ***
    **/
    bool Conector::query(const std::string& str, int (*callback)(void*,int,char**,char**),void* obj)
    {
        int rc = sqlite3_exec((sqlite3*)serverConnector, str.c_str(), callback, obj, NULL);
        if( rc != SQLITE_OK ) 			
        {
        	std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";
            return false;			
        } 
        else 
        {
            return true;			
        }			
    }
    void* Conector::getServerConnector()
    {
        return serverConnector;
    }
    Conector::~Conector()
    {
        close();
    }		
    Conector::Conector(const std::string& dbname)
    {
        serverConnector = NULL;
        int rc = sqlite3_open(dbname.c_str(), (sqlite3**)&serverConnector);
        if( rc ) 
        {
			//fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg((sqlite3*)serverConnector));
			std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";
			//return(0);
        } 
    }
}

