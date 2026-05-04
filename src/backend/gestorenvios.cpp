#include "gestorenvios.h"
#include <chrono>

GestorEnvios::GestorEnvios(Grafo* _grafo) {
    this->redGrafo = _grafo;
}

/*Destructor que mata a todos los hilos para evitar que sigan funcionando*/
GestorEnvios::~GestorEnvios() {
    for (std::thread& hilo : hilosActivos) {
        if (hilo.joinable()) {
            hilo.join();
        }
    }
}

/*Metodo qu permite iniciar un envio (Inicio del hilo)*/
void GestorEnvios::iniciarEnvio(Producto* paquete, const std::vector<Sucursal*>& ruta,bool porTiempo) {
    if (ruta.empty() || paquete == nullptr) {
        return;
    }

    hilosActivos.emplace_back(&GestorEnvios::procesarViaje, this, paquete, ruta, porTiempo);
}

/*Metodo que permite llevar el proceso del viaje especifico*/
void GestorEnvios::procesarViaje(Producto* paquete, std::vector<Sucursal*> ruta,bool porTiempo) {

    int factorTiempo = 1000;

    for (size_t i = 0; i < ruta.size(); ++i) {
        Sucursal* sucursalActual = ruta[i];

        // Tomamos el almacén (GestorEstructuras) de la sucursal
        GestorEstructuras* almacen = sucursalActual->getAlmacen();

        // --- Salida y entrada a la cola de salida---
        if (i == 0) {
            almacen->getColaSalida()->encolar(paquete);
            std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(sucursalActual->getTiempoDespacho() * factorTiempo)));
            almacen->getColaSalida()->desencolar();
        }

        // --- Movimiento entre las sucursales---
        else if (i > 0 && i < ruta.size() - 1) {
            almacen->getColaTraspaso()->encolar(paquete);
            std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(sucursalActual->getTiempoPreparacion() * factorTiempo)));
            almacen->getColaTraspaso()->desencolar();
        }

        // --- Encolamiento en la cola de ingreso de la sucursal---
        else if (i == ruta.size() - 1) {
            almacen->getColaIngreso()->encolar(paquete);
            std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(sucursalActual->getTiempoIngreso() * factorTiempo)));
            almacen->getColaIngreso()->desencolar();
        }

        // --- Tiempo segun el peso de la arista ---
        if (i < ruta.size() - 1) {
            Sucursal* sucursalSiguiente = ruta[i + 1];

            double tiempoViaje = redGrafo->obtenerTiempoArista(sucursalActual->getId(), sucursalSiguiente->getId(),porTiempo);
            std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(tiempoViaje * factorTiempo)));
        }
    }

    //Si el viaje termino se guarda en el historial
    HistorialEnvio nuevoRegistro;

    nuevoRegistro.setProducto(paquete->getNombre(), paquete->getCodigoBarra());
    nuevoRegistro.setIdOrigen(ruta.front()->getId());
    nuevoRegistro.setIdDestino(ruta.back()->getId());

    for (Sucursal* suc : ruta) {
        nuevoRegistro.getTrayectoria().push_back(suc->getId());
    }

    std::lock_guard<std::mutex> lock(mutexHistorial);
    historial.push_back(nuevoRegistro);
}

/*Metodo que permite obtener el historial de envios que se van haciendo*/
std::vector<HistorialEnvio> GestorEnvios::getHistorial() {
    std::lock_guard<std::mutex> lock(mutexHistorial);
    return historial;
}

/*Metodo que permite generar el set de la red del grafo*/
void GestorEnvios::setRedGrafo( Grafo* _redGrafo){
    this->redGrafo = _redGrafo;
}
