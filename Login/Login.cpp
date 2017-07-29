#include "soapH.h" /* get the gSOAP-generated definitions */
#include "Login.nsmap" /* get the gSOAP-generated namespace bindings */
#include <iostream>
#include <string>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#define PATH "/var/log/Login"
#define table "Tupper"

int main(){
	struct soap soap;
	soap_init(&soap);


	time_t tiempo = time(0);
	struct tm *tlocal = localtime(&tiempo);
	char fechaActual[128];
	strftime(fechaActual,128,"%Y%m%d",tlocal);

	char fechaHora[128];
	strftime(fechaHora,128,"%Y%m%d%H%M%S",tlocal);


	char logf1[1000000];
	char logf2[1000000];
	char logf3[1000000];

	sprintf(logf1,"%s%s%s",PATH,fechaActual,"_entrada.log");
	sprintf(logf2,"%s%s%s",PATH,fechaActual,"_salida.log");
	sprintf(logf3,"%s%s%s",PATH,fechaHora,"_fordebug.log");
	soap_set_recv_logfile(&soap, logf1);
	soap_set_sent_logfile(&soap, logf2);
	soap_set_test_logfile(&soap, logf3);

	soap_serve(&soap);

}

int ns__iniciar(struct soap *soap, struct Input *search, ns__Usuario *result_soap){
	sql::Driver *driver;
	sql::Connection *con;
	sql::Statement *stmt;
	sql::ResultSet *res;
	sql::PreparedStatement *pstmt;

	char query[1000];
	char user[20];
	char pass[100];

	sprintf(user, "%s", search->correo);
	sprintf(pass, "%s", search->contrasena);
	//std::string usuario(search->user);
	//std::string usuario(search->user);
	//std::string psw(search->pass);

	//char nombre[45];

	//sprintf(nombre,insert->nombre);

	try{
		driver = get_driver_instance();

		con = driver->connect("localhost", "root", "");
		con->setSchema("Tupper");
		//mysql_options(con, MYSQL_SET_CHARSET_NAME, "utf8");

	}catch(sql::SQLException &e){
		 return soap_sender_fault(soap, "Error -1", "ERROR Conexion con Base de Datos");
	}

	try{
		stmt = con->createStatement();
		sprintf(query, "SELECT * FROM User WHERE BINARY Correo = '%s' AND Contraseña = '%s'",user, pass);
		res = stmt->executeQuery(query);
		while(res->next()){

			result_soap->Id = res->getInt(1);

			std::string nombre = res->getString(2);
			result_soap->Nombre = nombre.c_str();

			std::string apellido = res->getString(3);
			result_soap->Apellido = apellido.c_str();

			std::string correo = res->getString(4);
			result_soap->Correo = correo.c_str();

			std::string pass = res->getString(5);
			result_soap->Pass = pass.c_str();


		}
	}catch(sql::SQLException &e){
		  std::cout << "# ERR: SQLException in " << __FILE__;
  std::cout << "(" << __FUNCTION__ << ") on line "
     << __LINE__ << std::endl;
  std::cout << "#ERR: " << e.what();
  std::cout << " (MySQL error code: " << e.getErrorCode();
  std::cout << ", SQLState: " << e.getSQLState() <<
     " )" << std::endl;
		 return soap_sender_fault(soap, "Error 3", "No pude rescatar dato");
	}

	delete res;
	delete stmt;
	delete con;

	return SOAP_OK;

}
