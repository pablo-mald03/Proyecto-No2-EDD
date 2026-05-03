#ifndef SUCURSAL_H
#define SUCURSAL_H

#include <string>
#include"gestorestructuras.h"
class Sucursal
{

private:
    std::string id;
    std::string nombre;
    std::string ubicacion;
    double tiempoIngreso;
    double tiempoPreparacion;
    double tiempoDespacho;
    GestorEstructuras * almacen;

public:
    Sucursal(std::string id, std::string nombre, std::string ubicacion,
             double t_ingreso, double t_preparacion, double t_despacho);

    ~Sucursal();

    std::string getId() const;
    std::string getNombre() const;
    std::string getUbicacion() const;
    double getTiempoIngreso() const;
    double getTiempoPreparacion() const;
    double getTiempoDespacho() const;

    GestorEstructuras * getAlmacen();

    void setNombre(const std::string& n);
    void setUbicacion(const std::string& u);
    void setTiempoIngreso(double t);
    void setTiempoPreparacion(double t);
    void setTiempoDespacho(double t);
};

#endif // SUCURSAL_H
