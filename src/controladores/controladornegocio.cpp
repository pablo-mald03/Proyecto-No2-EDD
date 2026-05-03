#include "controladornegocio.h"
#include <QElapsedTimer>
#include <exception>

ControladorNegocio::ControladorNegocio(QObject *parent)
    : QObject{parent},
    gestorMapeo(new GestorMapa())
{
}

/*Destructor*/
ControladorNegocio::~ControladorNegocio(){

    if(this->gestorMapeo != nullptr){
        delete this->gestorMapeo;
    }

}


/*--------Metodos que permiten dar informacion en los logs de la carga de csv de sucursales---------*/

void ControladorNegocio::procesarCsvSucursal(const std::vector<std::vector<QString>> & data){
    emit logCargaCsvSucursales("--- INICIANDO CARGA DE SUCURSALES ---", "blue");

    QElapsedTimer timer;
    timer.start();

    int insertadas = 0;
    int errores = 0;

    for (size_t i = 0; i < data.size(); ++i) {
        const auto& fila = data[i];

        if (i == 0 && fila.size() > 0 && fila[0].trimmed().toUpper() == "ID") {
            continue;
        }

        double tIngreso, tTraspaso, tDespacho;
        QString msjError;

        if (!this->gestorMapeo->validarFilaCsvSucursal(fila, tIngreso, tTraspaso, tDespacho, msjError)) {
            emit logCargaCsvSucursales("Fila " + QString::number(i + 1) + " rechazada: " + msjError, "red");
            errores++;
            continue;
        }

        std::string idStr = fila[0].trimmed().toStdString();
        std::string nombreStr = fila[1].trimmed().toStdString();
        std::string ubicacionStr = fila[2].trimmed().toStdString();

        try {
            this->gestorMapeo->insertarSucursal(idStr, nombreStr, ubicacionStr, tIngreso, tTraspaso, tDespacho);

            emit logCargaCsvSucursales("Sucursal { " + fila[0].trimmed() + " } agregada.", "green");
            insertadas++;

        } catch (const std::exception& e) {
            emit logCargaCsvSucursales("Error en fila " + QString::number(i + 1) + ": " + QString::fromStdString(e.what()), "orange");
            errores++;
        }
    }

    double tiempoTotalMs = timer.elapsed();

    emit tiempoProcesoSucursales(1, tiempoTotalMs);

    QString colorResumen = (errores == 0) ? "green" : (insertadas == 0 ? "red" : "orange");
    emit logCargaCsvSucursales("--- CARGA FINALIZADA | Exitos: " + QString::number(insertadas) + " | Errores: " + QString::number(errores) + " ---", colorResumen);
}

/*Metodo que permite procesar el csv de conexiones entre sucursales*/
void ControladorNegocio::procesarCsvConexion(const std::vector<std::vector<QString>> & data){
    emit logCargaCsvSucursales("--- INICIANDO CARGA DE CONEXIONES ---", "blue");

    QElapsedTimer timer;
    timer.start();

    int insertadas = 0;
    int errores = 0;

    for (size_t i = 0; i < data.size(); ++i) {
        const auto& fila = data[i];

        if (i == 0 && fila.size() > 0 && fila[0].trimmed().toUpper() == "ORIGENID") {
            continue;
        }

        double tiempo, costo;
        QString msjError;

        if (!this->gestorMapeo->validarFilaCsvConexion(fila, tiempo, costo, msjError)) {
            emit logCargaCsvSucursales("Fila " + QString::number(i + 1) + " rechazada: " + msjError, "red");
            errores++;
            continue;
        }

        std::string idOrigen = fila[0].trimmed().toStdString();
        std::string idDestino = fila[1].trimmed().toStdString();

        try {
            this->gestorMapeo->insertarConexion(idOrigen, idDestino, tiempo, costo);

            emit logCargaCsvSucursales("Conexion { " + fila[0].trimmed() + " -> " + fila[1].trimmed() + " } agregada.", "green");
            insertadas++;

        } catch (const std::exception& e) {
            emit logCargaCsvSucursales("Error en fila " + QString::number(i + 1) + ": " + QString::fromStdString(e.what()), "orange");
            errores++;
        }
    }

    double tiempoTotalMs = timer.elapsed();

    emit tiempoProcesoSucursales(1, tiempoTotalMs);

    QString colorResumen = (errores == 0) ? "green" : (insertadas == 0 ? "red" : "orange");
    emit logCargaCsvSucursales("--- CARGA FINALIZADA | Exitos: " + QString::number(insertadas) + " | Errores: " + QString::number(errores) + " ---", colorResumen);
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


