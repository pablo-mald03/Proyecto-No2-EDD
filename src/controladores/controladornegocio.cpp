#include "controladornegocio.h"

ControladorNegocio::ControladorNegocio(QObject *parent)
    : QObject{parent}
{
}

/*Destructor*/
ControladorNegocio::~ControladorNegocio(){

}


/*--------Metodos que permiten dar informacion en los logs de la carga de csv de sucursales---------*/

void ControladorNegocio::procesarCsvSucursal(const std::vector<std::vector<QString>> & data){

}

void ControladorNegocio::procesarCsvConexion(const std::vector<std::vector<QString>> & data){

}


void ControladorNegocio::procesarCsvEnvios(const std::vector<std::vector<QString>> & data){

}

/*--------Fin del Metodos que permiten dar informacion en los logs de la carga de csv de sucursales---------*/
