#include "gestormapa.h"
/*Clase delegada para poder implementar la comunicacion con las estructuras de datos y las sucursales*/
GestorMapa::GestorMapa():
    grafoSucursales(new Grafo())
{

}

/*Destructor*/
GestorMapa::~GestorMapa(){

    if(this->grafoSucursales != nullptr){
        delete this->grafoSucursales;
    }
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
