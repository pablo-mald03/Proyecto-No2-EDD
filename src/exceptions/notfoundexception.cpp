#include "notfoundexception.h"

NotFoundException::NotFoundException(const std::string& msg) : mensaje(msg)
{

}

/*Metodo que permite obtener los datos de la excepcion reportada*/
const char* NotFoundException::what() const noexcept {
    return mensaje.c_str();
}
