#ifndef NODOAVL_H
#define NODOAVL_H

/*Includes de la clase*/
#include"producto.h"

class NodoAvl
{
private:
    Producto producto;
    NodoAvl* izquierdo;
    NodoAvl* derecho;
    int altura;

public:
    NodoAvl(const Producto &_producto);


    /*Metodos getter para el nodo*/
    NodoAvl * getIzquierda() const;
    NodoAvl * getDerecha() const;

    void setIzquierda(NodoAvl* _izquierda);
    void setDerecha(NodoAvl* _derecha);

    int getAltura() const;
    void setAltura(int _altura);

    Producto& getDato();

    /*Version constante para obtenerlo en modo lectura*/
    const Producto& getDato() const;
};

#endif // NODOAVL_H
