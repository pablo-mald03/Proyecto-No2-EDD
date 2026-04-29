#ifndef ERRORESLECTURA_H
#define ERRORESLECTURA_H

#include <string>
class ErroresLectura
{
public:
    ErroresLectura(const std::string &_mensaje,int _linea);
    ErroresLectura();

    std::string getMensaje();
    int getLinea();

private:
    std::string mensaje;
    int linea;


};

#endif // ERRORESLECTURA_H
