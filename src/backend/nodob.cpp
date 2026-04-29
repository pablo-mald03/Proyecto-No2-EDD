#include "nodob.h"

/*Nodo del arbol B*/
NodoB::NodoB(bool _hoja): esHoja(_hoja)
{

}

/*Destructor*/
NodoB::~NodoB(){

    while (!hijos.esVacia()) {
        NodoB* temp = hijos.obtenerFrente();
        delete temp;
        hijos.removerFrente();
    }
}

/*Metodos getter del nodo B*/
ListaEnlazada<Producto>& NodoB::getClaves(){
    return this->claves;
}

ListaEnlazada<NodoB*>& NodoB::getHijos(){
    return this->hijos;
}

bool NodoB::getEsHoja(){
    return this->esHoja;
}
