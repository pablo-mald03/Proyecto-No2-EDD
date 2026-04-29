#include "nodobmas.h"

/*Constructor del nodo B mas*/
NodoBMas::NodoBMas(bool _esHoja):
    esHoja(_esHoja),
    siguiente(nullptr)
{

}

/*Destructor*/
NodoBMas::~NodoBMas(){

    while (!hijos.esVacia()) {
        NodoBMas* temp = hijos.obtenerFrente();
        delete temp;
        hijos.removerFrente();
    }
    this->claves.limpiar();
}

/*Getters del nodo*/
ListaEnlazada<Producto>& NodoBMas::getClaves(){
    return this->claves;
}


ListaEnlazada<NodoBMas*>& NodoBMas::getHijos(){
    return this->hijos;
}

bool NodoBMas::getEsHoja(){
    return this->esHoja;
}

/*Metodos getter y setter del arbol para los datos*/
NodoBMas * NodoBMas::getSiguiente(){
    return this->siguiente;
}

void NodoBMas::setSiguiente(NodoBMas* _siguiente){
    this->siguiente = _siguiente;
}
