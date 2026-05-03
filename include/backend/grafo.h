#ifndef GRAFO_H
#define GRAFO_H

#include <vector>
#include <string>
#include "sucursal.h"
#include "conexion.h"

class Grafo
{

private:
    std::vector<Sucursal*> nodos;
    std::vector<std::vector<Conexion*>> matriz;

    int obtenerIndice(const std::string& id) const;

public:
    Grafo();
    ~Grafo();

    // Metodos principales para poder gestionar el crud en el Grafo
    void insertarSucursal(Sucursal *nueva);
    void modificarSucursal(const std::string &_id,const std::string &_nombre, const std::string &_ubicacion, double _ingreso, double _despacho, double _preparacion);
    void eliminarSucursal(const std::string &id);

    /*Metodo que permite buscar una sucursa por su id*/
    Sucursal* buscarSucursal(const std::string& id) const;

    // Metodos principales para el Crud en las aristas del grafo
    void agregarConexion(const std::string &origen, const std::string &destino,
                         double tiempo, double costo);

    const std::vector<Sucursal*>& getNodos() const;
    const std::vector<std::vector<Conexion*>>& getMatriz() const;

    std::string generarGraphviz() const;
};

#endif // GRAFO_H
