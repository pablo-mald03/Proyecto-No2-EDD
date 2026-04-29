#include "erroreslectura.h"

ErroresLectura::ErroresLectura(const std::string &_mensaje,int _linea):mensaje(_mensaje),linea(_linea)
{

}

ErroresLectura::ErroresLectura() : mensaje(""), linea(0)
{

}

/*Metodos getter para poder obtener la informacion para armar el log*/
std::string ErroresLectura::getMensaje(){
    return this->mensaje;
}

int ErroresLectura::getLinea(){
    return this->linea;
}
