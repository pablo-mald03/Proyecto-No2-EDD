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

void ControladorNegocio::procesarCsvProductos(const std::vector<std::vector<QString>> & data){

}


/*--------Metodos que permiten dar informacion en los logs de la carga de csv de sucursales---------*/


/*Metodo que permite obtener los datos para poder descargar el Log de errores de sucursales*/
void ControladorNegocio::prepararLogParaDescargaSucursales(){
   // QString contenido = this->gestorBackend->generarContenidoLog();

    emit logDescargarSucursales("contenido");
}

/*Metodo que permite obtener los datos para poder descargar el Log de errores de envios*/
void ControladorNegocio::prepararLogParaDescargaEnvios(){
   // QString contenido = this->gestorBackend->generarContenidoLog();

    emit logDescargarEnvios("contenido");
}

/*Metodo que permite obtener los datos para poder descargar el Log de errores de productos*/
void ControladorNegocio::prepararLogParaDescargaProductos(){
    // QString contenido = this->gestorBackend->generarContenidoLog();

    emit logDescargarEnvios("contenido");
}


/*--------Fin del Metodos que permiten dar informacion en los logs de la carga de csv de sucursales---------*/
