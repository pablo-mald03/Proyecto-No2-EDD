#ifndef NOTFOUNDEXCEPTION_H
#define NOTFOUNDEXCEPTION_H

/*Includes de la clase*/
#include <exception>
#include <string>

class NotFoundException : public std::exception
{
private:
    std::string mensaje;

public:
    explicit NotFoundException(const std::string& msg);

    virtual const char* what() const noexcept override;
};

#endif // NOTFOUNDEXCEPTION_H
