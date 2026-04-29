#include "insertexception.h"

/*Excepcion que se suelta al momento de existir algun fallo de insercion*/
InsertException::InsertException(const std::string& msg) : mensaje(msg)
{

}

/*Metodo que permite obtener los datos de la excepcion reportada*/
const char* InsertException::what() const noexcept {
    return mensaje.c_str();
}
