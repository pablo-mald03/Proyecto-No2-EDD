#include "readercsvexception.h"

/*Clase que representa la excepcion de lectura de una excepcion*/
ReaderCsvException::ReaderCsvException(const std::string& msg) : mensaje(msg)
{

}

/*Metodo que permite obtener los datos de la excepcion reportada*/
const char* ReaderCsvException::what() const noexcept {
    return mensaje.c_str();
}
