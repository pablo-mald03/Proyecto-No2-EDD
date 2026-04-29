#ifndef ARBOLAVL_H
#define ARBOLAVL_H

/*includes del arbol*/
#include "listaenlazada.h"
#include"producto.h"
#include"nodoavl.h"
#include <sstream>
#include <string>

class ArbolAvl
{

private:
    NodoAvl* raiz;

    int obtenerAltura(NodoAvl* nodo);
    int obtenerFactorBalance(NodoAvl* nodo);

    /*Rotaciones del arbol*/
    NodoAvl* rotacionDerecha(NodoAvl* y);
    NodoAvl* rotacionIzquierda(NodoAvl* x);

    // Metodo recursivo de insercion (devuelve el nuevo nodo raiz del subarbol)
    NodoAvl* insertarRecursivo(NodoAvl* nodo, Producto producto);

    /*Metodo que permite evaluar si un producto ya existe con la misma llave primaria*/
    bool existeCodigoBarra(NodoAvl* nodo, const std::string& codigo);

    /*Metodo utilizado para poder buscar por codigo de barra un producto (UTIL PARA ELIMINACION)*/
    Producto * buscarPorCodigobarra(NodoAvl* nodo, const std::string &codigo);

    /*Metodo utilizado para encontrar el nodo de mas bajo nivel de un subarbol para poder borrar un nodo (METODO AUXILIAR)*/
    NodoAvl* nodoMinimo(NodoAvl* nodo);

    /*Metodo recursivo para poder eliminar los nodos del arbol*/
    NodoAvl* eliminarRecursivo(NodoAvl* nodo, const std::string &nombre, const std::string& codigo);

    /*Metodo que permite generar el .dot recursivo para el arbol y que se pueda graficar*/
    void generarDotRecursivo(NodoAvl* nodo, std::stringstream& sStream);

    /*Metodo que permite generar la busqueda binaria completa en el arbol AVL*/
    void buscarProductoRecursivo(NodoAvl* nodo, const std::string& nombre, ListaEnlazada<Producto>& lista);

    /*Metodo que permite listar en orden alfabetico el arbol*/
    void listarProductosInOrden(NodoAvl* nodo, ListaEnlazada<Producto>& lista);

public:
    ArbolAvl();
    ~ArbolAvl();

    /*Metodo que permite insertar un producto al arbol*/
    void insertar(Producto producto);

    /*Metodo que permite retornar la lista de los productos en orden alfabetico*/
    ListaEnlazada<Producto> obtenerProductosOrdenados();

    /*Metodo que permite generar la busqueda del producto por nombre*/
    ListaEnlazada<Producto> buscarProducto(const std::string& nombre);

    /*Metodo que permite vaciar el arbol por completo*/
    void vaciarArbol(NodoAvl* nodo);

    /*Metodo que permite eliminar por codigo*/
    void eliminarPorCodigo(const std::string &codigo);

    /*Metodo que permite retornar la referencia a la raiz*/
    NodoAvl* getRaiz();

    /*Metodo que retorna el .dot generado por el arbol*/
    std::string generarDot();
};

#endif // ARBOLAVL_H
