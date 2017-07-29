#include "soapH.h" /* get the gSOAP-generated definitions */
#include "Register.nsmap" /* get the gSOAP-generated namespace bindings */
#include <iostream>
#include <string>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#define PATH "/var/log/Register/"
#define server "localhost"
#define user "root"
#define database "Tupper"
#define table "User"


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
int ns__registrar(struct soap *soap, struct User *insert, struct ns__registrarResponse *result_soap)
{
	sql::Driver *driver;
	sql::Connection *con;
	sql::Statement *stmt;
	sql::ResultSet *res;
	sql::PreparedStatement *pstmt;

	std::string nombre(insert->Nombre);
	std::string apellido(insert->Apellido);
	std::string mail(insert->mail);
	std::string pass(insert->pass);


	char query[1000];

	//char nombre[45];

	//sprintf(nombre,insert->nombre);

	try{
		driver = get_driver_instance();
		con = driver->connect(server, user, "");
		con->setSchema(database);

	}catch(sql::SQLException &e){
		 return soap_sender_fault(soap, "Error -1", "ERROR Conexion con Base de Datos");
	}

	try{

		//sprintf(query, "INSERT INTO %s(UserFirstLastName, UserSecondLastName, UserRealName, UserTelephone, UserEmail, UserDel, UserPass, UserDir) VALUES(?, ?, ?, ?, ?, ?, ?, ?)", table);

		pstmt = con->prepareStatement("CALL sp_registerUser(?, ?, ?, ?)");
		pstmt->setString(1, nombre);
		pstmt->setString(2, apellido);
		pstmt->setString(3, mail);
		pstmt->setString(4, pass);

		pstmt->executeUpdate();

	}catch(sql::SQLException &e){

		 return soap_sender_fault(soap, "Error 3", e.what());

	}
	result_soap->reception="OK";

	return SOAP_OK;
	delete pstmt;
}
