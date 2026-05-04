#include "tablahash.h"
#include "deleteexception.h"
#include "insertexception.h"
#include "notfoundexception.h"
#include <sstream>

/*Clase delegada para poder generar la implementacion de la tabla hash*/
TablaHash::TablaHash(int capacidadInicial):
    capacidad(capacidadInicial),
    elementos(0){

    this->tabla = new ListaEnlazada<Producto>*[capacidad];

    this->inicializarTabla();
}

/*Metodo delegado para poder inicializar la tabla hash*/
void TablaHash::inicializarTabla(){

    for (int i = 0; i < this->capacidad; i++) {
        this->tabla[i] = new ListaEnlazada<Producto>();
    }
}

/*Destructor*/
TablaHash::~TablaHash() {
    for (int i = 0; i < this->capacidad; i++) {
        delete this->tabla[i];
    }
    delete[] this->tabla;
}

/*Metodo principal de hasheo implementado conocido como MumurHash
*
* Es una version simplificada caracterizado pro mezclar bits para evitar colisiones
*
*/
unsigned int TablaHash::calcularIndice(const std::string& clave) {
    //Semilla de hasheo codigo HEX grande
    unsigned int hash = 0x811C9DC5;

    //Constante a multiplicar
    const unsigned int multiplicador = 0x01000193;

    for (int i = 0; i < clave.length(); i++) {
        //La negacion inyecta bits por acarreo
        hash = hash ^ (unsigned int)clave[i];

        //Dispersion de bits resultantes
        hash *= multiplicador;

        // Desplazamiento circular (Bit-Shifting):
        hash = (hash << 13) | (hash >> 19);
    }

    //Amplia mas la distribucion para evitar colisiones con los bits ya acarreados
    hash ^= hash >> 16;
    hash *= 0x85ebca6b;
    hash ^= hash >> 13;
    hash *= 0xc2b2ae35;
    hash ^= hash >> 16;

    return hash % this->capacidad;
}

/*Metodo que permite obtener la referencia hacia el arreglo de la tabla hash para poderla agraficar*/
ListaEnlazada<Producto>** TablaHash::getTabla(){
    return this->tabla;
}

/*Metodo que permite obtener la referencia hacia la capacidad de la tabla hash para poderla agraficar*/
int TablaHash::getCapacidad(){
    return this->capacidad;
}

/*Metodo que permite insertar un producto en la tabla hash*/
void TablaHash::insertar(const Producto& nuevoProducto) {

    Producto * productoRegistrado = this->buscarProducto(nuevoProducto.getCodigoBarra());

    if(productoRegistrado != nullptr){
        throw InsertException("El producto con el codigo {" + productoRegistrado->getCodigoBarra() +
                                "} ya existe.");
    }

    float factorCarga = (float)elementos / this->capacidad;

    if(factorCarga> 0.75){
        this->redimensionarHash();
    }

    unsigned int indice = calcularIndice(nuevoProducto.getCodigoBarra());
    tabla[indice]->insertarAtras(nuevoProducto);
    this->elementos++;

}

/*Metodo auxiliar que permite buscar un producto por codigo de barra*/
Producto* TablaHash::buscarProducto(const std::string& codigoBarra) {
    unsigned int indice = calcularIndice(codigoBarra);

    ListaEnlazada<Producto>* almacen = tabla[indice];

    for (int i = 0; i < almacen->getLongitud(); i++) {
        Producto& productoRef = almacen->getValor(i);

        if (productoRef.getCodigoBarra() == codigoBarra) {

            return &productoRef;
        }
    }

    return nullptr;
}

/*Metodo que permite generar la busqueda en la tabla hash O(1)*/
Producto* TablaHash::buscar(const std::string& codigoBarra) {

    Producto * productoEncontrado = buscarProducto(codigoBarra);

    if(productoEncontrado == nullptr){
        throw NotFoundException("El producto con el codigo {"+codigoBarra+"} no esta registrado.");
    }
    return productoEncontrado;
}

/*Metodo que permite eliminar un producto de una tabla basandose en el codigo de barra*/

bool TablaHash::eliminar(const std::string& codigoBarra) {

    unsigned int indice = calcularIndice(codigoBarra);
    ListaEnlazada<Producto>* almacen = tabla[indice];

    for (int i = 0; i < almacen->getLongitud(); i++) {

        if (almacen->getValor(i).getCodigoBarra() == codigoBarra) {

            almacen->eliminar(i);
            this->elementos--;
            return true;
        }
    }
    throw DeleteException("El producto con el codigo {" + codigoBarra +
                          "} no existe.");
}

/*Metodo que permite redimensionar la tabla hash cuando se desborda*/
void TablaHash::redimensionarHash() {

    int capacidadAntigua = this->capacidad;
    ListaEnlazada<Producto>** tablaAntigua = tabla;

    this->capacidad = capacidadAntigua * 2;

    tabla = new ListaEnlazada<Producto>*[this->capacidad];
    for (int i = 0; i < this->capacidad; i++) {
        tabla[i] = new ListaEnlazada<Producto>();
    }

    /*Fragmento donde se llena otra vez el arreglo*/
    int elementosTemporales = 0;
    for (int i = 0; i < capacidadAntigua; i++) {
        ListaEnlazada<Producto>* listaVieja = tablaAntigua[i];

        for (int j = 0; j < listaVieja->getLongitud(); j++) {
            Producto& producto = listaVieja->getValor(j);

            //Se rehashean todos los indices para poderlos insertar en la nueva tabla
            unsigned int nuevoIndice = calcularIndice(producto.getCodigoBarra());
            tabla[nuevoIndice]->insertarAtras(producto);
            elementosTemporales++;
        }

        delete listaVieja;
    }

    this->elementos = elementosTemporales;
    delete[] tablaAntigua;
}

/*Metodo que permite generar el graphviz de la tabla hash incluyendo colisiones*/
std::string TablaHash::generarDot() {
    std::stringstream dot;

    dot << "digraph G {\n";
    dot << "  nodesep=.05;\n";
    dot << "  rankdir=LR;\n";
    dot << "  node [shape=record, width=.1, height=.1];\n\n";

    dot << "  tabla [label = \"";
    for (int i = 0; i < this->capacidad; i++) {
        dot << "<f" << i << "> " << i;
        if (i < this->capacidad - 1) dot << " | ";
    }
    dot << "\", height=2.5];\n\n";

    dot << "  node [shape=box, style=filled, fillcolor=white];\n";

    for (int i = 0; i < this->capacidad; i++) {
        ListaEnlazada<Producto>* lista = tabla[i];

        if (lista->getLongitud() > 0) {
            std::string colorNodo = (lista->getLongitud() > 1) ? "lightcoral" : "lightblue";

            for (int j = 0; j < lista->getLongitud(); j++) {
                Producto& producto = lista->getValor(j);


                dot << "  nodo_" << i << "_" << j << " [label=\"ID: " << producto.getCodigoBarra()
                    << "\\n" << producto.getNombre() << "\", fillcolor=\"" << colorNodo << "\"];\n";

                if (j == 0) {
                    dot << "  tabla:f" << i << " -> nodo_" << i << "_" << j << ";\n";
                } else {
                    dot << "  nodo_" << i << "_" << j-1 << " -> nodo_" << i << "_" << j << ";\n";
                }
            }
        }
    }

    dot << "}\n";
    return dot.str();
}
