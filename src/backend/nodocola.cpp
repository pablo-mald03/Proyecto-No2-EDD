#include "nodocola.h"

NodoCola::NodoCola(Producto* prod) : producto(prod), siguiente(nullptr)
{

}

/*Metodos para poder utilizar el nodo*/
Producto* NodoCola::getProducto(){
    return this->producto;
}

NodoCola*  NodoCola::getSiguiente() const{
    return this->siguiente;
}

void NodoCola::setSiguiente(NodoCola*  _siguiente){
    this->siguiente = _siguiente;
}
