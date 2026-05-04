#ifndef NODOCOLA_H
#define NODOCOLA_H

#include "producto.h"
class NodoCola
{
private:
    Producto* producto;
    NodoCola* siguiente;
public:
    NodoCola(Producto* prod);

    Producto* getProducto();

    NodoCola*  getSiguiente() const;

    void setSiguiente(NodoCola*  _siguiente);
};

#endif // NODOCOLA_H
