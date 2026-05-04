#include "controladorsucursal.h"

ControladorSucursal::ControladorSucursal(QObject *parent)
    : QObject{parent}
{
}

/*Destructor*/
ControladorSucursal::~ControladorSucursal(){

}

/*Metodo que permite setear los recursos que necesita usar el controlador para manejar una sucursal*/
void ControladorSucursal::setRecursosActuales(Sucursal* _sucursal, Grafo* _redGrafo, GestorEnvios* _gestor) {
    this->redGrafo = _redGrafo;
    this->sucursalActual = _sucursal;
    this->gestorEnvios = _gestor;
}

/*Metodo que permite realizar un envio desde una sucursal*/
void ControladorSucursal::enviarProducto(std::string idDestino, Producto* p,bool porTiempo) {

    std::vector<Sucursal*> ruta = redGrafo->obtenerRutaOptima(sucursalActual->getId(), idDestino,porTiempo);

    if(!ruta.empty()) {
        gestorEnvios->iniciarEnvio(p, ruta,porTiempo);
    }
}
/*Metodos getter de la clase*/
Grafo * ControladorSucursal::obtenerGrafo(){
    return this->redGrafo;
}

Sucursal * ControladorSucursal::obtenerSucursalActual(){
    return this->sucursalActual;
}



