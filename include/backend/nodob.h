#ifndef NODOB_H
#define NODOB_H

#include "listaenlazada.h"
#include "producto.h"
class NodoB
{
private:
    bool esHoja;
    ListaEnlazada<Producto> claves;
    ListaEnlazada<NodoB*> hijos;

public:
    NodoB(bool _hoja);
    ~NodoB();

    /*Metodos getter de la clase*/
    ListaEnlazada<Producto>& getClaves();

    ListaEnlazada<NodoB*>& getHijos();

    bool getEsHoja();

};

#endif // NODOB_H
