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
    void modificarSucursal(const std::string &id, const std::string &nuevoNombre);
    void eliminarSucursal(const std::string &id);

    // Metodos principales para el Crud en las aristas del grafo
    void agregarConexion(const std::string &origen, const std::string &destino,
                         double tiempo, double costo);
};

#endif // GRAFO_H
