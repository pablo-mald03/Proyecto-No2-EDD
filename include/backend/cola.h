#ifndef COLA_H
#define COLA_H

#include <string>
#include <vector>
#include <mutex>
#include "nodocola.h"
#include "producto.h"

class Cola
{
private:
    NodoCola* frente;
    NodoCola* final;

    //Atributo que representa el estado mutable para los datos
    mutable std::mutex candado;

public:
    Cola();
    ~Cola();

    /*Metodos basicos de la cola*/
    void encolar(Producto* prod);
    Producto* desencolar();

    // Metodo que permite saber que hay en la cola sin sacarlo
    std::vector<Producto*> obtenerCopiaElementos() const;
};

#endif // COLA_H
