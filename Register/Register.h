//gsoap ns service name: Register
//gsoap ns service namespace: urn:Register
//gsoap ns service location: http://187.223.183.56/cgi-bin/Register.cgi
//gsoap ns schema namespace: urn:Register

struct User{
  const char *Nombre;
  const char *Apellido;
  const char *mail;
  char *pass;
};
struct ns__registrarResponse{
  char *reception;
};

int ns__registrar(struct User *insert, struct ns__registrarResponse *result_soap);
