#ifndef CONEXION_H
#define CONEXION_H

#include <limits>

class Conexion
{

private:
    double tiempo;
    double costo;
    bool existe;

public:
    // Constructores
    Conexion();
    Conexion(double t, double c);

    // Getters
    double getTiempo() const;
    double getCosto() const;
    bool getExiste() const;

    // Setters
    void setTiempo(double t);
    void setCosto(double c);
    void setExiste(bool e);
};

#endif // CONEXION_H
