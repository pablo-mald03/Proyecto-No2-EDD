#ifndef INSERTEXCEPTION_H
#define INSERTEXCEPTION_H

/*Includes de la clase*/
#include <exception>
#include <string>

class InsertException : public std::exception
{
private:
    std::string mensaje;

public:
    explicit InsertException(const std::string& msg);

    virtual const char* what() const noexcept override;
};

#endif // INSERTEXCEPTION_H
