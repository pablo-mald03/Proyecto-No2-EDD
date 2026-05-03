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

/*--------Apartado de Metodos que permite procesar la insercion de una sucursal---------*/

/*Metodo que permite insertar una sucursal*/
void ControladorNegocio::insercionSucursal(const std::string &_id,const std::string &_nombre, const std::string &_ubicacion, double _ingreso, double _despacho, double _preparacion){

}

/*Metodo que permite conectar una sucursal con otra*/
void  ControladorNegocio::conexionSucursal(const std::string &_Origen, const std::string &_Destino,double _tiempo,double _costo){

}

/*Metodo que permite eliminar una sucursal*/
void ControladorNegocio::eliminacionSucursal(const std::string &_id){

}

/*Metodo que permite modificar una sucursal*/
void ControladorNegocio::modificacionSucursal(const std::string &_id,const std::string &_nombre, const std::string &_ubicacion, double _ingreso, double _despacho, double _preparacion){

}

/*Metodo que permite buscar en el grafo las sucursales registradas*/
void ControladorNegocio::cargarSucursal(std::string id){

    emit abrirSucursal(new GestorEstructuras(), id);
}

/*Metodo que permite retornar la sucursal en donde se puede visualizar los viajes*/
void ControladorNegocio::buscarEnvios(std::string id){

   // emit abrirSucursal(new GestorEstructuras(), id);
}


