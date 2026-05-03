#include "sucursal.h"

Sucursal::Sucursal(const std::string &id, const std::string &nombre, const std::string &ubicacion,
                   double t_ingreso, double t_preparacion, double t_despacho) {
    this->id = id;
    this->nombre = nombre;
    this->ubicacion = ubicacion;
    this->tiempoIngreso = t_ingreso;
    this->tiempoPreparacion = t_preparacion;
    this->tiempoDespacho = t_despacho;
    this->almacen = new GestorEstructuras();
}

Sucursal::~Sucursal() {
    delete this->almacen;
}

std::string Sucursal::getId() const {
    return id;
}

std::string Sucursal::getNombre() const {
    return nombre;
}
std::string Sucursal::getUbicacion() const{
    return this->ubicacion;
}
double Sucursal::getTiempoIngreso() const{
    return this->tiempoIngreso;
}
double Sucursal::getTiempoPreparacion() const{
    return this->tiempoPreparacion;
}
double Sucursal::getTiempoDespacho() const{
    return this->tiempoDespacho;
}

GestorEstructuras * Sucursal::getAlmacen(){
    return this->almacen;
}

void Sucursal::setNombre(const std::string& n) {
    this->nombre = n;
}
void Sucursal::setUbicacion(const std::string& u) {
    this->ubicacion = u;
}
void Sucursal::setTiempoIngreso(double t) {
    this->tiempoIngreso = t;
}
void Sucursal::setTiempoPreparacion(double t) {
    this->tiempoPreparacion = t;
}
void Sucursal::setTiempoDespacho(double t) {
    this->tiempoDespacho = t;
}
