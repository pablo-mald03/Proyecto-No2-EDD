#ifndef READERCSVEXCEPTION_H
#define READERCSVEXCEPTION_H

/*Includes de la clase*/
#include <exception>
#include <string>

/*Clase que representa las excepciones que se pueden reportar en la lectura del csv*/
class ReaderCsvException : public std::exception
{
private:
    std::string mensaje;

public:
    explicit ReaderCsvException(const std::string& msg);

    virtual const char* what() const noexcept override;

};

#endif // READERCSVEXCEPTION_H
