#include "nodoavl.h"

/*Clase que representa a los nodos del arbol AVL*/
NodoAvl::NodoAvl(const Producto &_producto): producto(_producto),
    izquierdo(nullptr),
    derecho(nullptr),
    altura(1)
{

}

/*Metodos getter y setter*/
NodoAvl * NodoAvl::getIzquierda() const{
    return this->izquierdo;
}
NodoAvl * NodoAvl::getDerecha() const{
    return this->derecho;
}

void NodoAvl::setIzquierda(NodoAvl* _izquierda){
    this->izquierdo = _izquierda;
}
void NodoAvl::setDerecha(NodoAvl* _derecha){
    this->derecho = _derecha;
}

Producto& NodoAvl::getDato(){
    return this->producto;
}

int NodoAvl::getAltura() const {
    return this->altura;
}

void NodoAvl::setAltura(int _altura) {
    this->altura = _altura;
}

const Producto& NodoAvl::getDato() const
{
    return this->producto;
}
