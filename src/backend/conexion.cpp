#include "conexion.h"

/*Clase que representa la conexion de una sucursal*/
Conexion::Conexion() {
    this->tiempo = std::numeric_limits<double>::infinity();
    this->costo = std::numeric_limits<double>::infinity();
    this->existe = false;
}

Conexion::Conexion(double t, double c) {
    this->tiempo = t;
    this->costo = c;
    this->existe = true;
}

double Conexion::getTiempo() const {
    return tiempo;
}
double Conexion::getCosto() const {
    return costo;
}
bool Conexion::getExiste() const {
    return existe;
}

void Conexion::setTiempo(double t) {
    this->tiempo = t;
}
void Conexion::setCosto(double c) {
    this->costo = c;
}
void Conexion::setExiste(bool e) {
    this->existe = e;
}
