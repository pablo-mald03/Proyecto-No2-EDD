#include "listaenlazada.h"
#include <stdexcept>

/*Includes de la clase*/
#include "erroreslectura.h"
#include "nodob.h"
#include"nodobmas.h"
#include"producto.h"


//instancia posible de lista
template class ListaEnlazada<Producto>;
template class ListaEnlazada<ErroresLectura>;
template class ListaEnlazada<NodoB*>;
template class ListaEnlazada<NodoBMas*>;

/*Constructor de la lista enlazada*/
template<typename T>
ListaEnlazada<T>::ListaEnlazada(): cabeza(nullptr),cola(nullptr), longitud(0)
{

}

/*Destructor*/
template<typename T>
ListaEnlazada<T>::~ListaEnlazada()
{
    limpiar();
}

//Metodo que obtiene la cabeza de la lista enlazada para poder recorrerla sin mayor complejidad
template<typename T>
NodoLista<T>* ListaEnlazada<T>::getCabeza() const {
    return this->cabeza;
}

//Metodo que retorna si la lista esta vacia
template<typename T>
bool ListaEnlazada<T>::esVacia() const{
    return this->cabeza == nullptr;
}

//Metodo que retorna la longitud de la lista
template<typename T>
int ListaEnlazada<T>::getLongitud() const
{
    return this->longitud;
}


//Metodo que agrega al frente de la lista
template<typename T>
void ListaEnlazada<T>::insertarAtras(const T& valor)
{
    NodoLista<T>* nuevo = new NodoLista<T>(valor);
    nuevo->setSiguiente(nullptr);

    if (esVacia())
    {
        this->cabeza = cola = nuevo;
        nuevo->setAnterior(nullptr);
    }
    else
    {
        this->cola->setSiguiente(nuevo);
        nuevo->setAnterior(cola);
        this->cola = nuevo;
    }

    this->longitud++;
}

//Metodo para insertar al frente de la lista
template<typename T>
void ListaEnlazada<T>::insertarFrente(const T& valor){

    NodoLista<T>* nuevo = new NodoLista<T>(valor);
    nuevo->setAnterior(nullptr);

    if (esVacia())
    {
        this->cabeza = cola = nuevo;
        nuevo->setSiguiente(nullptr);
    }
    else
    {
        nuevo->setSiguiente(cabeza);
        this->cabeza->setAnterior(nuevo);
        this->cabeza = nuevo;
    }

    this->longitud++;
}


//Metodo para remover atras de la lista
template<typename T>
void ListaEnlazada<T>::removerAtras()
{
    if (esVacia()){
        return;
    }

    NodoLista<T>* temporal = this->cola;

    if (this->cabeza == this->cola)
    {
        this->cabeza = this->cola = nullptr;
    }
    else
    {
        this->cola = this->cola->getAnterior();
        this->cola->setSiguiente(nullptr);
    }

    delete temporal;
    this->longitud--;
}


//Metodo para remover al frente
template<typename T>
void ListaEnlazada<T>::removerFrente()
{
    if (esVacia()) return;

    NodoLista<T>* temporal = this->cabeza;

    if (this->cabeza == cola)
    {
        this->cabeza = cola = nullptr;
    }
    else
    {
        this->cabeza = this->cabeza->getSiguiente();
        this->cabeza->setAnterior(nullptr);
    }

    delete temporal;
    this->longitud--;
}

//====================REGION DE METODOS ESPECIALES DE LA LISTA=================================

//Metodo privado de la clase (Busca nodos) por busqueda secuencial con modificacion O(n)
template<typename T>
NodoLista<T>* ListaEnlazada<T>::getNodo(int indice) const{

    if(indice>=longitud){
        throw std::out_of_range("Indice fuera de rango de la lista enlazada");
    }

    NodoLista<T>* actual;

    if (indice < this->longitud / 2)
    {
        actual = this->cabeza;
        for (int i = 0; i < indice; i++)
        {
            actual = actual->getSiguiente();
        }
    }
    else
    {
        actual = cola;
        for (int i = this->longitud - 1; i > indice; i--){
            actual = actual->getAnterior();
        }
    }
    return actual;
}

//Metodo que sirve para insertar en cualquier indice
template<typename T>
void ListaEnlazada<T>::insertar(int indice, const T& valor)
{
    if (indice > this->longitud){
        throw std::out_of_range("Indice fuera de rango de la lista enlazada");
    }

    if (indice == 0)
    {
        insertarFrente(valor);
        return;
    }

    if (indice == this->longitud)
    {
        insertarAtras(valor);
        return;
    }

    NodoLista<T>* actual = getNodo(indice);
    NodoLista<T>* anterior = actual->getAnterior();

    NodoLista<T>* nuevo = new NodoLista<T>(valor);

    nuevo->setSiguiente(actual);
    nuevo->setAnterior(anterior);

    anterior->setSiguiente(nuevo);
    actual->setAnterior(nuevo);

    this->longitud++;
}

//Metodo que sirve para eliminar un dato EN CUALQUIER POSICION
template<typename T>
void ListaEnlazada<T>::eliminar(int indice)
{
    if (indice < 0 || indice >= this->longitud){
        throw std::out_of_range("Indice fuera de rango de la lista enlazada");
    }

    if (indice == 0)
    {
        removerFrente();
        return;
    }

    if (indice == this->longitud - 1)
    {
        removerAtras();
        return;
    }

    NodoLista<T>* actual = getNodo(indice);
    NodoLista<T>* anterior = actual->getAnterior();
    NodoLista<T>* siguiente = actual->getSiguiente();

    anterior->setSiguiente(siguiente);
    siguiente->setAnterior(anterior);

    delete actual;
    this->longitud--;
}

/*Metodo que permite editar el valor en una posicion*/
template<typename T>
void  ListaEnlazada<T>::setValor(int posicion, const T& nuevoValor){

    if (posicion < 0 || posicion >= this->longitud) {
        throw std::out_of_range("Indice fuera de rango de la lista enlazada");
    }

    NodoLista<T>* nodoDestino = getNodo(posicion);
    nodoDestino->setValor(nuevoValor);
}


/*Metodo que permite obtener el frente de la lista*/
template<typename T>
T ListaEnlazada<T>::obtenerFrente() const {
    if (esVacia()) {
        if (esVacia()) {
            throw std::runtime_error("Intento de obtener frente de una lista vacia");
        }
    }
    return cabeza->getDato();
}

//Metodo que permite obtener un valor por posicion
template<typename T>
T& ListaEnlazada<T>::getValor(int indice)
{
    return getNodo(indice)->getDato();
}

//====================FIN DE LA REGION DE METODOS ESPECIALES DE LA LISTA=================================

/*Metodo que permite limpiar la lista por completo*/
template<typename T>
void ListaEnlazada<T>::limpiar()
{
    while (!esVacia())
        removerFrente();
}
