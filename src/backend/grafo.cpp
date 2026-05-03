#include "grafo.h"
#include "insertexception.h"
#include "notfoundexception.h"

Grafo::Grafo() {

}

Grafo::~Grafo() {
    for (size_t i = 0; i < nodos.size(); ++i) {
        delete nodos[i];
    }
    nodos.clear();

    for (size_t i = 0; i < matriz.size(); ++i) {
        for (size_t j = 0; j < matriz[i].size(); ++j) {
            delete matriz[i][j];
        }
        matriz[i].clear();
    }
    matriz.clear();
}

/*Metodo que permite obtener el indice de un nodo almacenado en el grafo*/
int Grafo::obtenerIndice(const std::string& id) const {
    for (size_t i = 0; i < nodos.size(); ++i) {
        if (nodos[i]->getId() == id) {
            return i;
        }
    }
    return -1;
}

/*Metodo que permite insertar una nueva sucursal en el grafo*/
void Grafo::insertarSucursal(Sucursal* nueva) {

    /*Validacion de integridad*/
    if (obtenerIndice(nueva->getId()) != -1) {
        throw InsertException("La sucursal con el codigo { " +
                              nueva->getId() + " } ya existe en el sistema");
    }

    nodos.push_back(nueva);
    int nuevoTam = nodos.size();

    for (int i = 0; i < nuevoTam - 1; ++i) {
        matriz[i].push_back(new Conexion());
    }

    std::vector<Conexion*> nuevaFila;
    for (int i = 0; i < nuevoTam; ++i) {
        nuevaFila.push_back(new Conexion());
    }

    matriz.push_back(nuevaFila);
}

/*Metodo que permite agregar una nueva conexion entre sucursales*/
void Grafo::agregarConexion(const std::string& origen, const std::string& destino, double tiempo, double costo) {

    int i = obtenerIndice(origen);
    int j = obtenerIndice(destino);

    if (i != -1 && j != -1) {
        matriz[i][j]->setTiempo(tiempo);
        matriz[i][j]->setCosto(costo);
        matriz[i][j]->setExiste(true);
    } else {

        throw NotFoundException("El origen o destino no existen en la red.");
    }
}


