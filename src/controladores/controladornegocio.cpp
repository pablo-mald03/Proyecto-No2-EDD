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

/*Metodo que permite limpiar el backend (sucursales almacenadas)*/
void ControladorNegocio::vaciarSucursales(){
    this->gestorMapeo->limpiarRegistros();
}

/*--------Metodos que permiten dar informacion en los logs de la carga de csv de sucursales---------*/

void ControladorNegocio::procesarCsvSucursal(const std::vector<std::vector<QString>> & data){

    this->vaciarSucursales();

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

    emit logCargaCsvProductos("--- INICIANDO CARGA DE PRODUCTOS ---", "orange");

    int insertadas = 0;
    int errores = 0;

    for (size_t i = 0; i < data.size(); ++i) {
        const auto& fila = data[i];

        QStringList listaFila;
        for(const QString& campo : fila) {
            listaFila << campo.trimmed();
        }
        QString lineaPorComas = listaFila.join(", ");
        emit logCargaCsvProductos(lineaPorComas, "white");

        if (i == 0 && fila.size() > 0 && fila[0].trimmed().toUpper() == "SUCURSALID") {
            continue;
        }

        double precio = 0.0;
        int stock = 0;
        QString msjError;

        if (!this->gestorMapeo->validarFilaCsvProducto(fila, precio, stock, msjError)) {
            emit logCargaCsvProductos("Fila " + QString::number(i + 1) + " rechazada: " + msjError, "red");
            this->gestorMapeo->agregarError(msjError.toStdString(), (i + 1) , 3);
            errores++;
            continue;
        }

        std::string sucursalId = fila[0].trimmed().toStdString();
        std::string nombre = fila[1].trimmed().toStdString();
        std::string codigoBarra = fila[2].trimmed().toStdString();
        std::string categoria = fila[3].trimmed().toStdString();
        std::string fechaExpiracion = fila[4].trimmed().toStdString();
        std::string marca = fila[5].trimmed().toStdString();

        Producto nuevoProducto(nombre, codigoBarra, categoria, fechaExpiracion, marca, precio, stock);

        try {

            this->insertarProductoSucursal(sucursalId, nuevoProducto);

            insertadas++;
        } catch (const std::exception& e) {
            emit logCargaCsvProductos("Error fila " + QString::number(i + 1) + ": " + QString::fromStdString(e.what()), "red");
            this->gestorMapeo->agregarError(QString::fromStdString(e.what()).toStdString(), (i + 1) , 3);
            errores++;
        }
    }

    QString colorResumen = (errores == 0) ? "orange" : (insertadas == 0 ? "red" : "yellow");
    emit logCargaCsvProductos("--- Lineas validas: " + QString::number(insertadas) + " | Lineas no validas: " + QString::number(errores) + " ---", colorResumen);

    this->verificarErroresSucursales(3);
}

/*Metodo que permite insertar el producto en la sucursal requerida*/

/*--------Metodos que permiten dar informacion en los logs de la carga de csv de sucursales---------*/
void ControladorNegocio::insertarProductoSucursal(const std::string idSucursal, const Producto &producto){
    try {

        Sucursal * sucursalEncontrada = this->gestorMapeo->buscarSucursal(idSucursal);

        GestorEstructuras * gestor = sucursalEncontrada->getAlmacen();

        this->darMensajeProductos(QString::fromStdString("Insertando en sucursal [ "+sucursalEncontrada->getId()+" ]:\n" +sucursalEncontrada->getNombre()) ,"orange");

        QElapsedTimer timerAvl;
        timerAvl.start();

        gestor->insertarArbolAvl(producto.getNombre(),producto.getCodigoBarra(),producto.getCategoria(),producto.getFechaExpiracion(),producto.getMarca(),producto.getPrecio(),producto.getStock());

        double tiempoPasadoAvl = timerAvl.nsecsElapsed() / 1000000.0;

        emit tiempoProcesoProductos(1,tiempoPasadoAvl);

        emit logArbolAvl("Producto con ID: {"+ QString::fromStdString(producto.getCodigoBarra()) +"} insertado", "green");

        QElapsedTimer timerB;
        timerB.start();

        gestor->insertarArbolB(producto.getNombre(),producto.getCodigoBarra(),producto.getCategoria(),producto.getFechaExpiracion(),producto.getMarca(),producto.getPrecio(),producto.getStock());

        double tiempoPasadoB = timerB.nsecsElapsed() / 1000000.0;

        emit tiempoProcesoProductos(2,tiempoPasadoB);

        emit logArbolB("Producto con ID: {"+ QString::fromStdString(producto.getCodigoBarra()) +"} insertado", "green");


        QElapsedTimer timerBMas;
        timerBMas.start();

        gestor->insertarArbolBMas(producto.getNombre(),producto.getCodigoBarra(),producto.getCategoria(),producto.getFechaExpiracion(),producto.getMarca(),producto.getPrecio(),producto.getStock());

        double tiempoPasadoBMas = timerBMas.nsecsElapsed() / 1000000.0;

        emit tiempoProcesoProductos(3,tiempoPasadoBMas);

        emit logArbolBMas("Producto con ID: {"+ QString::fromStdString(producto.getCodigoBarra()) +"} insertado", "green");

        QElapsedTimer timerLista;
        timerLista.start();

        gestor->insertarListaOrdenada(producto.getNombre(),producto.getCodigoBarra(),producto.getCategoria(),producto.getFechaExpiracion(),producto.getMarca(),producto.getPrecio(),producto.getStock());

        gestor->insertarListaNoOrdenada(producto.getNombre(),producto.getCodigoBarra(),producto.getCategoria(),producto.getFechaExpiracion(),producto.getMarca(),producto.getPrecio(),producto.getStock());

        double tiempoPasadoLista = timerLista.nsecsElapsed() / 1000000.0;

        emit tiempoProcesoProductos(4,tiempoPasadoLista);

        emit logLista("Producto con ID: {"+ QString::fromStdString(producto.getCodigoBarra()) +"} insertado", "green");

        QElapsedTimer timerHash;
        timerHash.start();

        gestor->insertarTablaHash(producto.getNombre(),producto.getCodigoBarra(),producto.getCategoria(),producto.getFechaExpiracion(),producto.getMarca(),producto.getPrecio(),producto.getStock());

        double tiempoPasadoHash = timerHash.nsecsElapsed() / 1000000.0;

        emit tiempoProcesoProductos(5,tiempoPasadoHash);

        emit logHash("Producto con ID: {"+ QString::fromStdString(producto.getCodigoBarra()) +"} insertado", "green");

    } catch (const std::exception& e) {

        this->darMensajeProductos(QString::fromStdString(e.what()) ,"red");
    }

}

/*Metodo auxiliar para poder dar mensajes mientras se estra leyendo el csv de carga de productos*/
void ControladorNegocio::darMensajeProductos(QString msj, QString color){

    QString mensaje = "==========================================\n" +
                      msj + "\n" +
                      "==========================================\n\n";

    emit logArbolAvl(mensaje.replace("\n", "<br>"), color);
    emit logArbolB(mensaje.replace("\n", "<br>"), color);
    emit logArbolBMas(mensaje.replace("\n", "<br>"), color);
    emit logLista(mensaje.replace("\n", "<br>"), color);
    emit logHash(mensaje.replace("\n", "<br>"), color);

}

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

    QElapsedTimer timer;
    timer.start();

    try {
        this->gestorMapeo->insertarSucursal(_id, _nombre, _ubicacion,
                                            _ingreso, _preparacion, _despacho);

        emit logInsertGrafo(
            QString::fromStdString("Sucursal [ " + _nombre + " ] agregada correctamente."), "green");

    } catch (const std::exception &e) {
        emit logInsertGrafo("Error al insertar: " +
                                    QString::fromStdString(e.what()),
                                "red");
    }

    double tiempoTotalMs = timer.elapsed();

    emit tiempoProcesoInsercionGrafo(tiempoTotalMs);
    emit actualizacionCombos(this->gestorMapeo->getGrafo()->getNodos());
}

/*Metodo que permite conectar una sucursal con otra*/
void  ControladorNegocio::conexionSucursal(const std::string &_Origen, const std::string &_Destino,double _tiempo,double _costo){

    try {
        this->gestorMapeo->insertarConexion(_Origen, _Destino, _tiempo, _costo);
        emit mensajeConfirmacionConexion(QString::fromStdString("Conexion entre sucursales { " + _Origen + " -> " + _Destino + " } agregada."), true);

    } catch (const std::exception& e) {
        emit mensajeConfirmacionConexion(QString::fromStdString(e.what()), false);
    }
}

/*Metodo que permite eliminar una sucursal*/
void ControladorNegocio::eliminacionSucursal(const std::string &_id){

    QElapsedTimer timer;
    timer.start();

    try {
        this->gestorMapeo->eliminarSucursal(_id);

        emit logEliminacionGrafo(
            QString::fromStdString("La sucursal con el ID: {"+_id+"} eliminada correctamente."), "green");

    } catch (const std::exception &e) {
        emit logEliminacionGrafo("Error al eliminar: " +
                                      QString::fromStdString(e.what()),
                                  "red");
    }

    double tiempoTotalMs = timer.elapsed();

    emit tiempoProcesoEliminacionGrafo(tiempoTotalMs);

}

/*Metodo que permite modificar una sucursal*/
void ControladorNegocio::modificacionSucursal(const std::string &_id,const std::string &_nombre, const std::string &_ubicacion, double _ingreso, double _despacho, double _preparacion){

    QElapsedTimer timer;
    timer.start();

    try {
        this->gestorMapeo->editarSucursal(_id, _nombre, _ubicacion,
                                            _ingreso, _preparacion, _despacho);

        emit logModificacionGrafo(
            QString::fromStdString("Sucursal [ " + _nombre + " ] con ID: {"+_id+"} modificada correctamente."), "green");

    } catch (const std::exception &e) {
        emit logModificacionGrafo("Error al modificar: " +
                                QString::fromStdString(e.what()),
                            "red");
    }

    double tiempoTotalMs = timer.elapsed();

    emit tiempoProcesoModificacionGrafo(tiempoTotalMs);
}

/*Metodo que permite buscar la informacion de la sucursal en bas al id*/
void ControladorNegocio::buscarSucursal(const std::string &_id){

    try {
        Sucursal * sucursalEncontrada = this->gestorMapeo->buscarSucursal(_id);
        emit enviarInformacion(sucursalEncontrada);
    } catch (const std::exception& e) {
        emit mensajeErrorModificar(QString::fromStdString(e.what()));
    }
}

/*Metodo que permite buscar en el grafo las sucursales registradas*/
void ControladorNegocio::cargarSucursal(const std::string &id){

    Sucursal * sucursalEncontrada = this->gestorMapeo->buscarSucursal(id);
    emit abrirSucursal(sucursalEncontrada, this->obtenerGrafo());
}


/*Metodo que permite generar el graphviz del grafo*/
void ControladorNegocio::generarGraphvizGrafo(){
    emit enviarGraphvizGrafo(this->gestorMapeo->obtenerGraphvizGrafo());
}

/*Metodo que permite retornar la sucursal en donde se puede visualizar los viajes*/
void ControladorNegocio::buscarEnvios(std::string id){

   // emit abrirSucursal(new GestorEstructuras(), id);
}


