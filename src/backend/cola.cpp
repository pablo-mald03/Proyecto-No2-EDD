#include "cola.h"

Cola::Cola(): frente(nullptr), final(nullptr) {}

Cola::~Cola() {
    while (frente != nullptr) {
        desencolar();
    }
}

/*Metodo que permite meter un valor hacia la cola
*
* lock ayuda a que los estados no se desincronicen
*
*/
void Cola::encolar(Producto* prod) {
    NodoCola* nuevo = new NodoCola(prod);

    candado.lock();

    if (frente == nullptr) {
        frente = nuevo;
        final = nuevo;
    } else {
        final->setSiguiente(nuevo);
        final = nuevo;
    }

    candado.unlock();
}

/*Metodo que permite desencolar (con la restriccion de integridad respecto a los hilos mutables*/
Producto* Cola::desencolar() {
    candado.lock();

    if (frente == nullptr) {
        candado.unlock();
        return nullptr;
    }

    NodoCola* temp = frente;
    Producto* prod = temp->getProducto();
    frente = frente->getSiguiente();

    if (frente == nullptr) {
        final = nullptr;
    }

    delete temp;

    candado.unlock();
    return prod;
}

/*Metodo que permite obtener la copia modular de los productos en la cola */
std::vector<Producto*> Cola::obtenerCopiaElementos() const {
    std::vector<Producto*> copia;

    candado.lock(); //Bloqueo de encolado
    NodoCola* actual = frente;
    while (actual != nullptr) {
        copia.push_back(actual->getProducto());
        actual = actual->getSiguiente();
    }
    candado.unlock();

    return copia;
}
