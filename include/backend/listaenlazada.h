#ifndef LISTAENLAZADA_H
#define LISTAENLAZADA_H

/*Includes de la clase*/
#include"nodolista.h"

template<typename T>
class ListaEnlazada
{

private:
    NodoLista<T> * cabeza;
    NodoLista<T> * cola;
    int longitud;

    //Metodo especial para hallar los nodos
    NodoLista<T> * getNodo(int pos) const;

public:
    ListaEnlazada();
    ~ListaEnlazada();

    //Metodos para usar la lista
    void insertarAtras(const T&valor);
    void insertarFrente (const T&valor);

    void removerAtras();
    void removerFrente();

    bool esVacia() const;
    int getLongitud()const;

    void limpiar();

    //METODOS ESPECIALES QUE PERMITEN MOVERSE POR LA LISTA COMO SE DESEE
    void insertar(int pos, const T& valor);
    void eliminar(int pos);

    T& getValor(int pos);

    void setValor(int posicion, const T& nuevoValor);

    //Metodo para obtener la cabeza
    NodoLista<T>* getCabeza() const;

    T obtenerFrente() const;


};

#endif // LISTAENLAZADA_H
