#ifndef NODOLISTA_H
#define NODOLISTA_H

template<typename T>
class NodoLista
{

private:
    T dato;
    NodoLista<T> * siguiente;
    NodoLista<T> * anterior;


public:
    NodoLista(const T &producto);
    NodoLista();
    ~NodoLista();

    /*Metodos getters y setters*/
    T& getDato();

    NodoLista<T>* getSiguiente() const;
    NodoLista<T>* getAnterior() const;

    void setSiguiente(NodoLista<T>* _siguiente);
    void setAnterior(NodoLista<T>* _anterior);

    /*Metodo que permite setear el valor dentro del nodo*/
    void setValor(const T& nuevoValor);

};

#endif // NODOLISTA_H
