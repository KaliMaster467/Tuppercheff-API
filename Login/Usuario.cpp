#include "Usuario.h"

ns__Usuario::ns__Usuario(){

}
ns__Usuario::~ns__Usuario(){

}
void ns__Usuario::setNombre(const char *nombre){
  this->Nombre = Nombre;
}
void ns__Usuario::setApellido(const char *apellido){
  this->Apellido = Apellido;
}
void ns__Usuario::setCorreo(const char *correo){
  this->Correo = Correo;
}
void ns__Usuario::setPass(const char *pass){
  this->Pass = Pass;
}
void ns__Usuario::setId(const int id){
  this->Id = id;
}
const char * ns__Usuario::getNombre(){
  return Nombre;
}
const char *ns__Usuario::getApellido(){
  return Apellido;
}
const char *ns__Usuario::getCorreo(){
  return Correo;
}
const char * ns__Usuario::getPass(){
  return Pass;
}
const int *ns__Usuario::getId(){
  return Id;
}
