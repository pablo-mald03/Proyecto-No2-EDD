#ifndef TABLAHASH_H
#define TABLAHASH_H

#include "listaenlazada.h"
#include "producto.h"

class TablaHash
{

private:
    ListaEnlazada<Producto>** tabla;
    int capacidad;
    int elementos;

    /*Metodo de hasheo de la tabla*/
    unsigned int calcularIndice(const std::string& clave);

    /*Metodo que permite que la tabla vaya creciendo dinamicamente*/
    void redimensionarHash();

    /*Metodo delegado para poder inicializar la tabla hash*/
    void inicializarTabla();

    /*Metodo auxiliar que permite buscar un producto en la tabla hash*/
    Producto* buscarProducto(const std::string& codigoBarra);

public:
    TablaHash(int capacidadInicial);
    ~TablaHash();

    /*Metodo que permite insertar un producto en la tabla hash*/
    void insertar(const Producto& nuevoProducto);

    /*Metodo que permite buscar un producto en la tabl hash*/
    Producto* buscar(const std::string& codigoBarra);

    /*Metodo que permite eliminar un producto en la tabla hash por codigo*/
    bool eliminar(const std::string& codigoBarra);

    /*Metodo que permite generar el graphviz de la tabla hash*/
    std::string generarGraphviz();

    /*Metodo que permite obtener la referencia hacia el arreglo de la tabla hash para poderl agraficar*/
    ListaEnlazada<Producto>** getTabla();
};

#endif // TABLAHASH_H
