#ifndef DELETEEXCEPTION_H
#define DELETEEXCEPTION_H

/*Includes de la clase*/
#include <exception>
#include <string>

class DeleteException : public std::exception
{

private:
    std::string mensaje;

public:
    explicit DeleteException(const std::string& msg);

    virtual const char* what() const noexcept override;
};

#endif // DELETEEXCEPTION_H
