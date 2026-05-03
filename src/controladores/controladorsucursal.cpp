#include "controladorsucursal.h"

ControladorSucursal::ControladorSucursal(QObject *parent)
    : QObject{parent}
{
}

/*Destructor*/
ControladorSucursal::~ControladorSucursal(){

}

/*Metodo que permite setear los recursos que necesita usar el controlador para manejar una sucursal*/
void ControladorSucursal::setRecursosActuales(Sucursal * _sucursal, Grafo * _redGrafo){
    this->redGrafo = _redGrafo;
    this->sucursalAcutal = _sucursal;
}



