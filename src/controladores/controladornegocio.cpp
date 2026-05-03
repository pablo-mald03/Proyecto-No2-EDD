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

/*Metodo que permite obtener la referencia del grafo*/
Grafo * ControladorNegocio::obtenerGrafo() const{
    return this->gestorMapeo->getGrafo();
}

/*Metodo que verifica si hay errores en la carga de sucursales*/
/*
* 1 -> sucursales
* 2 -> envios
* 3 -> productos
*/
void ControladorNegocio::verificarErroresSucursales(int parametro){

    switch (parametro) {
    case 1:
        emit evaluarErroresSucursalesLog(this->gestorMapeo->tieneErrores(parametro));
    case 2:
        emit evaluarErroresEnviosLog(this->gestorMapeo->tieneErrores(parametro));
    case 3:
        emit evaluarErroresProductosLog(this->gestorMapeo->tieneErrores(parametro));
    }
}


/*--------Metodos que permiten dar informacion en los logs de la carga de csv de sucursales---------*/

void ControladorNegocio::procesarCsvSucursal(const std::vector<std::vector<QString>> & data){
    emit logGrafoSucursales("--- INICIANDO CARGA DE SUCURSALES ---", "orange");

    QElapsedTimer timer;
    timer.start();

    int insertadas = 0;
    int errores = 0;

    for (size_t i = 0; i < data.size(); ++i) {
        const auto& fila = data[i];

        QStringList listaFila;
        for(const QString& campo : fila) {
            listaFila << campo.trimmed();
        }
        QString lineaPorComas = listaFila.join(", ");

        emit logCargaCsvSucursales(lineaPorComas, "yellow");

        if (i == 0 && fila.size() > 0 && fila[0].trimmed().toUpper() == "ID") {
            continue;
        }

        double tIngreso, tTraspaso, tDespacho;
        QString msjError;

        if (!this->gestorMapeo->validarFilaCsvSucursal(fila, tIngreso, tTraspaso, tDespacho, msjError)) {
            emit logGrafoSucursales("Fila " + QString::number(i + 1) + " rechazada: " + msjError, "red");
            this->gestorMapeo->agregarError(msjError.toStdString(), (i + 1) , 1);
            errores++;
            continue;
        }

        std::string idStr = fila[0].trimmed().toStdString();
        std::string nombreStr = fila[1].trimmed().toStdString();
        std::string ubicacionStr = fila[2].trimmed().toStdString();


        try {
            this->gestorMapeo->insertarSucursal(idStr, nombreStr, ubicacionStr, tIngreso, tTraspaso, tDespacho);

            emit logGrafoSucursales("Sucursal { " + fila[0].trimmed() + " } agregada.", "green");
            insertadas++;

        } catch (const std::exception& e) {
            emit logGrafoSucursales("Error en fila " + QString::number(i + 1) + ": " + QString::fromStdString(e.what()), "red");
            this->gestorMapeo->agregarError(QString::fromStdString(e.what()).toStdString(), (i + 1) , 1);
            errores++;
        }
    }

    double tiempoTotalMs = timer.elapsed();

    emit tiempoProcesoSucursales(1, tiempoTotalMs);

    QString colorResumen = (errores == 0) ? "orange" : (insertadas == 0 ? "red" : "yellow");
    emit logGrafoSucursales("--- CARGA FINALIZADA | Exitos: " + QString::number(insertadas) + " | Errores: " + QString::number(errores) + " ---", colorResumen);
    this->verificarErroresSucursales(1);
}

/*Metodo que permite procesar el csv de conexiones entre sucursales*/
void ControladorNegocio::procesarCsvConexion(const std::vector<std::vector<QString>> & data){
    emit logGrafoSucursales("--- INICIANDO CARGA DE CONEXIONES ---", "orange");

    QElapsedTimer timer;
    timer.start();

    int insertadas = 0;
    int errores = 0;

    for (size_t i = 0; i < data.size(); ++i) {
        const auto& fila = data[i];

        QStringList listaFila;
        for(const QString& campo : fila) {
            listaFila << campo.trimmed();
        }
        QString lineaPorComas = listaFila.join(", ");

        emit logCargaCsvSucursales(lineaPorComas, "white");

        if (i == 0 && fila.size() > 0 && fila[0].trimmed().toUpper() == "ORIGENID") {
            continue;
        }

        double tiempo, costo;
        QString msjError;

        if (!this->gestorMapeo->validarFilaCsvConexion(fila, tiempo, costo, msjError)) {
            emit logGrafoSucursales("Fila " + QString::number(i + 1) + " rechazada: " + msjError, "red");
            this->gestorMapeo->agregarError(msjError.toStdString(), (i + 1) , 1);
            errores++;
            continue;
        }

        std::string idOrigen = fila[0].trimmed().toStdString();
        std::string idDestino = fila[1].trimmed().toStdString();

        try {
            this->gestorMapeo->insertarConexion(idOrigen, idDestino, tiempo, costo);

            emit logGrafoSucursales("Conexion { " + fila[0].trimmed() + " -> " + fila[1].trimmed() + " } agregada.", "green");
            insertadas++;

        } catch (const std::exception& e) {
            emit logGrafoSucursales("Error en fila " + QString::number(i + 1) + ": " + QString::fromStdString(e.what()), "red");
            this->gestorMapeo->agregarError(QString::fromStdString(e.what()).toStdString(), (i + 1) , 1);
            errores++;
        }
    }

    double tiempoTotalMs = timer.elapsed();

    emit tiempoProcesoSucursales(1, tiempoTotalMs);

    QString colorResumen = (errores == 0) ? "orange" : (insertadas == 0 ? "red" : "yellow");
    emit logGrafoSucursales("--- CARGA FINALIZADA | Exitos: " + QString::number(insertadas) + " | Errores: " + QString::number(errores) + " ---", colorResumen);
}

/*Metodo que permite procesar el csv de envios entre sucursales*/
void ControladorNegocio::procesarCsvEnvios(const std::vector<std::vector<QString>> & data){
    this->verificarErroresSucursales(2);
}

/*Metodo que permite procesar csv*/
void ControladorNegocio::procesarCsvProductos(const std::vector<std::vector<QString>> & data){

    this->verificarErroresSucursales(3);
}

/*--------Metodos que permiten dar informacion en los logs de la carga de csv de sucursales---------*/


/*Metodo que permite obtener los datos para poder descargar el Log de errores de sucursales*/
void ControladorNegocio::prepararLogParaDescargaSucursales(){
    QString contenido = this->gestorMapeo->generarContenidoLog(1);
    emit logDescargarSucursales(contenido);
}

/*Metodo que permite obtener los datos para poder descargar el Log de errores de envios*/
void ControladorNegocio::prepararLogParaDescargaEnvios(){
    QString contenido = this->gestorMapeo->generarContenidoLog(2);
    emit logDescargarEnvios(contenido);
}

/*Metodo que permite obtener los datos para poder descargar el Log de errores de productos*/
void ControladorNegocio::prepararLogParaDescargaProductos(){
    QString contenido = this->gestorMapeo->generarContenidoLog(3);
    emit logDescargarEnvios(contenido);
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


