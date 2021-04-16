#ifndef SYSAPP_DB_SQLITE_HH
#define SYSAPP_DB_SQLITE_HH

#include <string>
#include <vector>


namespace octetos::http::db
{
	class Variable;


    class Conector
    {
    private:
        void* serverConnector;
    public:

		/**
		*@brief Crean una conexion a la base de dato indicada
		*@param filename Nombre de archivo de la base de datos.
		*/
        Conector(const std::string& filename);
        ~Conector();

		/**
		*@brief Realiza una consula
		*@return true si la consulta se completo satisfactoriamente(incluso si no returna registros), falso si hubo un error. 
		*/
        bool query(const std::string&,int (*callback)(void*,int,char**,char**),void* obj);

		/**
		*@brief Realiza una consula
		*@return true si la consulta se completo satisfactoriamente(incluso si no returna registros), falso si hubo un error. 
		*/
		bool query(const std::string&);
		//bool update(const std::string&);
        void* getServerConnector();
		void close();
		const char* getErrorMessage()const;
		int getErrorCode()const;
		bool begin();
		bool commit();
		bool rollback();
    };
    
	class Table
	{

	};
	/**
	*@brief Tabla principal para almacenar la informacion de sesion.
	*
	*/
    class Session : public Table
    {
	private:
		static std::string TABLE_NAME;
        int id;
		std::string remote_addr;
		std::string session;
        
        static int callbackBySession(void *data, int argc, char **argv, char **azColName);
        static int callbackByRemoteAddr(void *data, int argc, char **argv, char **azColName);
		static int callbackIDs(void *data, int argc, char **argv, char **azColName);
			
    public:
        bool selectByRemoteAddr(Conector& conect, const std::string&);
		bool selectBySession(Conector& conect, const std::string&);
        static bool selectAll(Conector& conect, std::vector<Session*>& vec);
		bool downloadIDs(Conector& conect);
		bool inserteRemoteAddr(Conector& conect,const std::string&);
		bool insert(Conector& conect,const std::string& remote_addr,const std::string& session,const std::string& lasttime);
		Session();
		const std::string& getRomoteAddress()const;
		const std::string& getSession()const;
		int getID()const;
		bool updateSession(Conector& connect,const std::string& str);
		bool remove(Conector& connect);
		/**
		*@brief Modifica el valor de la variable indicada
		*@return true si existe y escribe el valor, falso en otro caso.
		*/
		bool setVariable(Conector& conect,const std::string& name,const std::string& value);
		/**
		*@brief Agrega una variable a la tabla de variable para esta sesion
		*@return true si crea la variable, falso si ya existe
		*/
		bool addVariable(Conector& conect,const std::string& name,const std::string& value);
		/**
		*@brief Busca y retuna una variable
		*@return true si encuentra la variable, falso en otro caso.
		*/
		bool getVariable(Conector& conect,const std::string& name, Variable&);
		/**
		*@brief Busca todas las variables asignadas a esta session
		*@return true si encuentra alguna, falso en otro caso.
		*/
		bool getVariables(Conector& conect, std::vector<Variable*>& vec);
    }; 

	  
	class Variable : public Table
	{
	private:
		static std::string TABLE_NAME;
        int id;
		std::string name;
		std::string value;
		
		static int callbackBySession(void *data, int argc, char **argv, char **azColName);
		static int callbackID(void *data, int argc, char **argv, char **azColName);
    public:
		int getID() const;
		bool insert(Conector& conect,const Session& session,const std::string& name,const std::string& value);
		bool select(Conector& conect,const Session& session, const std::string& name);
		const std::string& getName()const;
		const std::string& getValue()const;
		bool remove(Conector& connect);
		static bool select(Conector& conect,const Session& session, std::vector<Variable*>& vec);
		static bool remove(Conector& connect,const Session& session);
		bool updateValue(Conector& connect,const Session& session,const std::string& name,const std::string& value);
	};    
}


#endif
