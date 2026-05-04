#include "historialenvio.h"

HistorialEnvio::HistorialEnvio()
    : idOrigen(""), idDestino(""), nombreProducto(""), idProducto("")
{

}

HistorialEnvio::HistorialEnvio(std::string _idOrigen,
                               std::string _idDestino,
                               std::vector<std::string> _trayectoria,
                               std::string _nombreProd,
                               std::string _idProd)
    : idOrigen(_idOrigen),
    idDestino(_idDestino),
    trayectoria(_trayectoria),
    nombreProducto(_nombreProd),
    idProducto(_idProd)
{

}

std::string HistorialEnvio::getIdOrigen() const {
    return this->idOrigen;
}

std::string HistorialEnvio::getIdDestino() const {
    return this->idDestino;
}

std::vector<std::string>& HistorialEnvio::getTrayectoria() {
    return this->trayectoria;
}

std::string HistorialEnvio::getNombreProducto() const {
    return this->nombreProducto;
}

std::string HistorialEnvio::getIdProducto() const {
    return this->idProducto;
}

//Setters

void HistorialEnvio::setIdOrigen(const std::string& id) {
    this->idOrigen = id;
}

void HistorialEnvio::setIdDestino(const std::string& id) {
    this->idDestino = id;
}


void HistorialEnvio::setTrayectoria(const std::vector<std::string>& tray) {
    this->trayectoria = tray;
}

void HistorialEnvio::setProducto(const std::string& nombre, const std::string& id) {
    this->nombreProducto = nombre;
    this->idProducto = id;
}
