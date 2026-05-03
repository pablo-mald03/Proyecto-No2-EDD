#include "grafo.h"
#include "deleteexception.h"
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

/*Metodos getters para poder ilustar el grafo*/
const std::vector<Sucursal*>& Grafo::getNodos() const {
    return nodos;
}

const std::vector<std::vector<Conexion*>>& Grafo::getMatriz() const {
    return matriz;
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

/*Metodo que permite buscar una sucursal por su id*/
Sucursal* Grafo::buscarSucursal(const std::string& id) const {

    int indice = obtenerIndice(id);

    if (indice != -1) {
        return nodos[indice];
    }

    throw NotFoundException("La sucursal no existe en la red.");
}

/*Metodo que permite modificar una sucursal de la red del grafo*/
void Grafo::modificarSucursal(const std::string &_id, const std::string &_nombre, const std::string &_ubicacion, double _ingreso, double _despacho, double _preparacion) {
    int indice = obtenerIndice(_id);

    if (indice != -1) {
        nodos[indice]->setNombre(_nombre);
        nodos[indice]->setUbicacion(_ubicacion);
        nodos[indice]->setTiempoIngreso(_ingreso);
        nodos[indice]->setTiempoDespacho(_despacho);
        nodos[indice]->setTiempoPreparacion(_preparacion);
    } else {
        throw NotFoundException("La sucursal que se desea modificar no existe en la red.");
    }
}

/*Metodo que permite eliminar una sucursal de la red*/
/*
* Se borra la fila entera de la matriz en la que se encontraba conectada ese nodo
*/
void Grafo::eliminarSucursal(const std::string &id) {
    int indice = obtenerIndice(id);

    if (indice == -1) {
        throw DeleteException("La sucursal con el codigo { " +
                              id + " } no existe.");
    }

    delete nodos[indice];
    nodos.erase(nodos.begin() + indice);

    for (size_t j = 0; j < matriz[indice].size(); ++j) {
        delete matriz[indice][j];
    }

    matriz.erase(matriz.begin() + indice);

    for (size_t i = 0; i < matriz.size(); ++i) {
        delete matriz[i][indice];
        matriz[i].erase(matriz[i].begin() + indice);
    }
}

/*Metodo que permite generar el graphviz para poder exportar la representacion del grafo*/
std::string Grafo::generarGraphviz() const {
    std::ostringstream oss;

    oss << "digraph GrafoSucursales {\n";
    oss << "    node [shape=circle, style=filled, color=lightblue];\n";

    // 1. Declarar todos los nodos
    for (size_t i = 0; i < nodos.size(); ++i) {
        oss << "    \"" << nodos[i]->getId() << "\" [label=\""
            << nodos[i]->getId() << "\\n" << nodos[i]->getNombre() << "\"];\n";
    }

    for (size_t i = 0; i < matriz.size(); ++i) {
        for (size_t j = 0; j < matriz[i].size(); ++j) {
            if (matriz[i][j]->getExiste()) {
                oss << "    \"" << nodos[i]->getId() << "\" -> \"" << nodos[j]->getId() << "\" "
                    << "[label=\"T:" << matriz[i][j]->getTiempo()
                    << " C:" << matriz[i][j]->getCosto() << "\"];\n";
            }
        }
    }

    oss << "}\n";

    return oss.str();
}



