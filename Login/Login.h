//gsoap ns service name: Login
//gsoap ns service namespace: urn:Login
//gsoap ns service location: http://localhost/cgi-bin/Login.cgi
//gsoap ns schema namespace: urn:Login

#import "Usuario.h"
struct Input{
  char *correo;
  char *contrasena;
};

int ns__iniciar(struct Input *search, ns__Usuario *result_soap);
