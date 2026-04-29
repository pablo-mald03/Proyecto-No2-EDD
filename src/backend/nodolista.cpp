#include "nodolista.h"

/*Includes de la clase*/
#include "erroreslectura.h"
#include "nodob.h"
#include "nodobmas.h"
#include"producto.h"


template class NodoLista<Producto>;
template class NodoLista<ErroresLectura>;
template class NodoLista<NodoB*>;
template class NodoLista<NodoBMas*>;

template<typename T>
NodoLista<T>::NodoLista(const T &producto):dato(producto), siguiente(nullptr), anterior(nullptr)
{

}

template<typename T>
NodoLista<T>::NodoLista()
    : dato(T()), siguiente(nullptr), anterior(nullptr)
{
}

/*Destructor*/
template<typename T>
NodoLista<T>::~NodoLista(){

}

/*Metodos getter y setter*/
template<typename T>
T& NodoLista<T>::getDato(){
    return dato;
}


/*Metodos getters y setters para reutilizar nodo*/
template<typename T>
NodoLista<T>* NodoLista<T>::getSiguiente() const{
    return this->siguiente;
}

template<typename T>
NodoLista<T>* NodoLista<T>::getAnterior() const{
    return this->anterior;
}

template<typename T>
void NodoLista<T>::setSiguiente(NodoLista<T>* _siguiente){
    this->siguiente = _siguiente;
}

template<typename T>
void NodoLista<T>::setAnterior(NodoLista<T>* _anterior){
    this->anterior = _anterior;
}

/*Metodo que permite modificar el valor el valor dentro del nodo*/
template<typename T>
void NodoLista<T>::setValor(const T& nuevoValor){
    this->dato = nuevoValor;
}

