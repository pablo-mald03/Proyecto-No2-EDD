#include "deleteexception.h"

/*Excepcion que representa el error cuando no se puede eliminar un objeto*/
DeleteException::DeleteException(const std::string& msg) : mensaje(msg)
{

}

/*Metodo que permite obtener los datos de la excepcion reportada*/
const char* DeleteException::what() const noexcept {
    return mensaje.c_str();
}
