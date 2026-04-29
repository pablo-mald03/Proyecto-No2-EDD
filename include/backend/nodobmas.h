#ifndef NODOBMAS_H
#define NODOBMAS_H

/*Includes de la clase*/
#include"listaenlazada.h"
#include"producto.h"

class NodoBMas
{

private:
    bool esHoja;
    ListaEnlazada<Producto> claves;
    ListaEnlazada<NodoBMas*> hijos;

    /*Nodo que representa el apuntado hacia su nivel inferior*/
    NodoBMas* siguiente;

public:
    NodoBMas(bool _esHoja);
    ~NodoBMas();

    /*Metodos getter del nodo*/
    ListaEnlazada<Producto>& getClaves();
    ListaEnlazada<NodoBMas*>& getHijos();
    bool getEsHoja();

    /*Metodos getter y setter del arbol para los datos*/
    NodoBMas * getSiguiente();
    void setSiguiente(NodoBMas* _siguiente);

};

#endif // NODOBMAS_H
