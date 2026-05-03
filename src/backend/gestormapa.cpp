#include "gestormapa.h"
/*Clase delegada para poder implementar la comunicacion con las estructuras de datos y las sucursales*/
GestorMapa::GestorMapa()
    : grafoSucursales(new Grafo()),
    listaErroresSucursales(new ListaEnlazada<ErroresLectura>()),
    listaErroresEnvios(new ListaEnlazada<ErroresLectura>()),
    listaErroresProductos(new ListaEnlazada<ErroresLectura>())

{}

/*Destructor*/
GestorMapa::~GestorMapa(){

    this->limpiarEstrucuturas();
}

/*Metodo que permite reiniciar totalmente todas las estrucuturas*/
void GestorMapa::limpiarEstrucuturas(){

    if(this->grafoSucursales != nullptr){
        delete this->grafoSucursales;
    }

    if(this->listaErroresSucursales != nullptr){
        delete this->listaErroresSucursales;
        this->listaErroresSucursales = nullptr;
    }

    if(this->listaErroresEnvios != nullptr){
        delete this->listaErroresEnvios;
        this->listaErroresEnvios = nullptr;
    }

    if(this->listaErroresProductos != nullptr){
        delete this->listaErroresProductos;
        this->listaErroresProductos = nullptr;
    }
}

/*Metodo que permite reiniciar los registros de todo el gestor*/
void GestorMapa::limpiarRegistros(){

    this->limpiarEstrucuturas();

    this->grafoSucursales = new Grafo();
    this->listaErroresSucursales= new ListaEnlazada<ErroresLectura>();
    this->listaErroresEnvios=new ListaEnlazada<ErroresLectura>();
    this->listaErroresProductos= new ListaEnlazada<ErroresLectura>();
}

/*Metodo que permite obtener la referencia del grafo*/
Grafo * GestorMapa::getGrafo() const{
    return this->grafoSucursales;
}

/*Metodo que permite insertar una nueva sucursal*/
void GestorMapa::insertarSucursal(const std::string &id, const std::string &nombre, const std::string &ubicacion,
                      double _ingreso, double _preparacion, double _despacho){

    this->grafoSucursales->insertarSucursal(new Sucursal(id,nombre,ubicacion,_ingreso,_preparacion,_despacho));
}

/*Metodo que permite insertar una nueva sucursal*/
void GestorMapa::insertarConexion(const std::string& _origen, const std::string& _destino, double _tiempo, double _costo){

    this->grafoSucursales->agregarConexion(_origen,_destino,_tiempo,_costo);
}

/*Metodo que permite editar una sucursal*/
void GestorMapa::editarSucursal(const std::string &id, const std::string &nombre, const std::string &ubicacion,
                                  double _ingreso, double _preparacion, double _despacho){

    this->grafoSucursales->modificarSucursal(id,nombre,ubicacion,_ingreso,_preparacion,_despacho);
}

/*Metodo que permite eliminar una sucursal*/
void GestorMapa::eliminarSucursal(const std::string &id){

    this->grafoSucursales->eliminarSucursal(id);
}

/*Metodo que permite buscar una sucursal*/
Sucursal* GestorMapa::buscarSucursal(const std::string &id){

    return this->grafoSucursales->buscarSucursal(id);
}

/*Metodo que permite obtener el graphviz del grafo*/
std::string GestorMapa::obtenerGraphvizGrafo(){
    return this->grafoSucursales->generarGraphviz();
}

/*Metodo que permite hallar la ruta mas cotra de envio de produtos*/
std::vector<Sucursal*> GestorMapa::hallarRutaCorta(const std::string& origen, const std::string& destino, bool porTiempo) {
    return this->grafoSucursales->obtenerRutaOptima(origen,destino,porTiempo);
}

/*Metodo quxiliar que permite validar la fila del csvSucursal*/
bool GestorMapa::validarFilaCsvSucursal(const std::vector<QString>& fila, double& tIng, double& tTras, double& tDesp, QString& error) {
    if (fila.size() != 6) {
        error = "Formato inválido: Se esperaban 6 columnas, se recibieron " + QString::number(fila.size());
        return false;
    }

    if (fila[0].trimmed().isEmpty() || fila[1].trimmed().isEmpty() || fila[2].trimmed().isEmpty()) {
        error = "ID, Nombre o Ubicación no pueden estar vacíos.";
        return false;
    }

    bool ok1, ok2, ok3;
    tIng = fila[3].trimmed().toDouble(&ok1);
    tTras = fila[4].trimmed().toDouble(&ok2);
    tDesp = fila[5].trimmed().toDouble(&ok3);

    if (!ok1 || !ok2 || !ok3) {
        error = "Los tiempos de operacion deben ser valores numericos.";
        return false;
    }

    if (tIng < 0 || tTras < 0 || tDesp < 0) {
        error = "Los tiempos de operacion no pueden ser negativos.";
        return false;
    }

    return true;
}

/*Metodo que permite validar el formato csv de las conexiones*/
bool GestorMapa::validarFilaCsvConexion(const std::vector<QString>& fila, double& tiempo, double& costo, QString& error) {

    if (fila.size() != 4) {
        error = "Formato invalido: Se esperaban 4 columnas, se recibieron " + QString::number(fila.size());
        return false;
    }

    if (fila[0].trimmed().isEmpty() || fila[1].trimmed().isEmpty()) {
        error = "El ID de origen y destino no pueden estar vacios.";
        return false;
    }

    if (fila[0].trimmed() == fila[1].trimmed()) {
        error = "Una sucursal no puede conectarse consigo misma.";
        return false;
    }

    bool okTiempo, okCosto;
    tiempo = fila[2].trimmed().toDouble(&okTiempo);
    costo = fila[3].trimmed().toDouble(&okCosto);

    if (!okTiempo || !okCosto) {
        error = "El tiempo y el costo deben ser valores numericos.";
        return false;
    }

    if (tiempo < 0 || costo < 0) {
        error = "El tiempo y el costo no pueden ser negativos.";
        return false;
    }

    return true;
}



/*Metodo que permite registrar errores en las listas*/
/*
* 1 -> sucursales
* 2 -> envios
* 3 -> productos
*/
void GestorMapa::agregarError(std::string error, int fila, int caso){

    switch (caso) {
    case 1:
        this->listaErroresSucursales->insertarAtras(ErroresLectura(error,fila));
        break;
    case 2:
        this->listaErroresEnvios->insertarAtras(ErroresLectura(error,fila));
        break;
    case 3:
        this->listaErroresProductos->insertarAtras(ErroresLectura(error,fila));
        break;
    }
}

/*Metodo que permite armar el log de errores*/
/*
* 1 -> sucursales
* 2 -> envios
* 3 -> productos
*/
QString GestorMapa::generarContenidoLog(int caso) {

    QString log;
    QDateTime current = QDateTime::currentDateTime();
    QString fechaStr = current.toString("yyyy-MM-dd hh:mm:ss");

    log += "--------------------------------------------------\n";
    log += "LOG DE ERRORES --- PROCESAMIENTO CSV ---\n";
    log += "Fecha: " + fechaStr + "\n";
    log += "--------------------------------------------------\n\n";

    ListaEnlazada<ErroresLectura>* listaAProcesar = nullptr;
    QString tituloSistema;

    switch (caso) {
    case 1:
        listaAProcesar = this->listaErroresSucursales;
        tituloSistema = "SISTEMA DE GESTION DE SUCURSALES";
        break;
    case 2:
        listaAProcesar = this->listaErroresEnvios;
        tituloSistema = "SISTEMA DE GESTION DE ENVIOS";
        break;
    case 3:
        listaAProcesar = this->listaErroresProductos;
        tituloSistema = "SISTEMA DE GESTION DE PRODUCTOS";
        break;
    default:
        return "Error: Caso de log no definido.";
    }

    log += "--------------------------------------------------\n";
    log += "--- " + tituloSistema + " --- \n";
    log += "--------------------------------------------------\n\n";

    if (listaAProcesar && listaAProcesar->getLongitud() > 0) {
        for (int i = 0; i < listaAProcesar->getLongitud(); ++i) {
            ErroresLectura err = listaAProcesar->getValor(i);
            log += "[" + fechaStr + "] [ERROR] ";
            log += "Fila " + QString::number(err.getLinea()) + ": ";
            log += QString::fromStdString(err.getMensaje()) + "\n";
        }
    } else {
        log += "No se reportaron errores en la ultima carga.\n";
    }

    return log;
}

/*Metodo para saber si tiene errores la lista*/
/*
* 1 -> sucursales
* 2 -> envios
* 3 -> productos
*/
bool GestorMapa::tieneErrores(int parametro) const {

    switch (parametro) {
    case 1:
        return !this->listaErroresSucursales->esVacia();
    case 2:
        return !this->listaErroresEnvios->esVacia();
    case 3:
        return !this->listaErroresProductos->esVacia();
    default:
        return false;
    }

}

