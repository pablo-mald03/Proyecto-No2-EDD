#ifndef ARBOLB_H
#define ARBOLB_H

#include "nodob.h"
#include <sstream>
#include <string>
class ArbolB
{

private:
    NodoB * raiz;

    int t;

    /*Metodo que permite dividir al hijo*/
    void dividirHijo(NodoB* padre, int i, NodoB* lleno);

    /*Metodo que permite insertar un nodo que no esta lleno*/
    void insertarNoLleno(NodoB* nodo, const Producto &producto);

    /*Metodo general para poder insertar*/
    void insertarNuevo(const Producto &producto);

    /*Metodo que permite validar integridad*/
    bool existeCodigo(NodoB* nodo, const std::string &codigo);

    /*Metodo auxiliar para poder buscar por rango*/
    void buscarRangoAux(NodoB* nodo, const std::string& inicio, const std::string& fin, ListaEnlazada<Producto>& resultados);

    /*Metodo recursivo principal para poder ir recorriendo el arbol durante la eliminacion*/
    void eliminarAux(NodoB* nodo, const std::string& fecha, const std::string& codigo);

    /*Metodo que encuentra el indice de la clave en el nodo evaluado*/
    int buscarClave(NodoB* nodo, const std::string& fecha, const std::string& codigo);

    /*Metodo llamado cuando el hijo por el que se baja tiene t-1 claves y lo lleva a t*/
    void llenar(NodoB* nodo, int indice);

    /*Metodo que permite prestar desde el anterior al hermano de la par CASO 1*/
    void prestarDeAnterior(NodoB* nodo, int indice);

    /*Metodo que permite prestar desde el siguiente al hermano de la par CASO 2*/
    void prestarDeSiguiente(NodoB* nodo, int indice);

    /*Metodo CASO 3. Donde se desbordan las listas y se tiene que subir y subir haciendo merges*/
    void fusionar(NodoB* nodo, int indice);

    /*Metodo clave. ESTE PERMITE MANTENER EL BALANCE ES DE LOS MAS IMPORTANTES YA QUE MANEJA TODOS LOS CASOS*/
    void eliminarDeNodoInterno(NodoB* nodo, int idx);

    /*Metodo que permite ubicar al predecesor*/
    Producto getPredecesor(NodoB* nodo, int idx);

    /*Metodo que permite ubicar al sucesor*/
    Producto getSucesor(NodoB* nodo, int idx);

    /*Metodo que permite generar el .dot recursivo para el arbol y que se pueda graficar*/
    void generarDotRecursivo(NodoB* nodo, std::stringstream& sStream);

    /*Metodo que permite buscar en el arbol el producto con el codigo de barra*/
    Producto buscarPorCodigoExhaustivo(NodoB* nodo, const std::string& codigo, bool& encontrado);

public:
    ArbolB(int _t);
    ~ArbolB();


    /*Metodo que permite insertar un nuevo producto en un arbol. Maneja la integridad*/
    void insertar(const Producto &producto);

    /*Metodo que permite buscar por rango*/
    ListaEnlazada<Producto> buscarRango(const std::string& inicio, const std::string& fin);

    /*Metodo que permite eliminar por completo un nodo*/
    void eliminar(const std::string& codigo);

    /*Metodo que permite generar el graphviz del arbol B*/
    std::string generarDot();

    /*Metodo que permite retornar la raiz del arbol B*/
    NodoB * getRaiz();

};

#endif // ARBOLB_H
