#ifndef ARBOLBMAS_H
#define ARBOLBMAS_H

/*Includes de la clase*/
#include "nodobmas.h"
#include <sstream>
#include <string>

class ArbolBMas
{
private:
    NodoBMas* raiz;

    /*Orden seteable*/
    int orden;

    /*Metodo que permite insertar datos en un nodo del arbol*/
    void insertarEnNodo(NodoBMas* nodo, const Producto &producto);

    /*Metodo que permite generar la division de las hojas cuando se sobrepasa el limite*/
    void dividirHoja(NodoBMas* hoja, NodoBMas* padre, int indiceEnPadre);

    /*Metodo que permite dividir la lista cuando se genera el desbordamiento*/
    void dividirInterno(NodoBMas* interno, NodoBMas* padre, int indiceEnPadre);

    /*Metodo que permite generar la recursividad para poder insertar en el lugar correcto*/
    void insertarRecursivo(NodoBMas *nodo, NodoBMas *padre, Producto producto, int indiceEnPadre);

    /*Metodo que permite conservar la integridad del arbol buscando la primary key que es el codigo de barra*/
    bool yaExiste(NodoBMas* nodoRaiz, const Producto &producto);

    /*Metodo que permite generar el .dot recursivo*/
    void generarDotRecursivo(NodoBMas* nodo, std::stringstream& sStream);

    /*Metodo que permite recorrer el arbol y propagar el rabalanceo hacia arriba*/
    bool eliminarRecursivo(NodoBMas* nodo, NodoBMas* padre, int indiceEnPadre, const Producto& producto);

    /*Metodo que maneja la forma en prestar y fusiones cuando un nodo se queda sin el minimo de claves*/
    void balancearNodo(NodoBMas* padre, NodoBMas* hijo, int indiceHijo);

    /*Metodo que permite unir dos nodos hermanos y eliminar la clave separadora del padre*/
    void fusionarNodos(NodoBMas* padre, int indiceSeparador, NodoBMas* izquierdo, NodoBMas* derecho);

public:
    ArbolBMas(int _orden);
    ~ArbolBMas();

    /*Metodo que permite insertar un nuevo producto*/
    void insertar(const Producto &producto);

    /*Metodo que permite eliminar un producto del arbol*/
    void eliminar(const std::string& codigoBarra);

    /*Metodo que permite obtener la raiz del arbol*/
    NodoBMas* getRaiz();

    /*Metodo que permite buscar por categoria (lista de productos por categoria)*/
    ListaEnlazada<Producto> buscarPorCategoria(const std::string &categoriaBuscada);

    /*Metodo que permite generar el graphviz del arbol B+*/
    std::string generarDot();
};

#endif // ARBOLBMAS_H
