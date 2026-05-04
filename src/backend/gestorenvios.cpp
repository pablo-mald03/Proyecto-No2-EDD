#include "gestorenvios.h"

GestorEnvios::GestorEnvios() {

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
void GestorEnvios::iniciarEnvio(const std::string& idProducto, const std::string& nombreProducto, const std::vector<Sucursal*>& ruta) {
    if (ruta.empty()) {
        return;
    }

    hilosActivos.emplace_back(&GestorEnvios::procesarViaje, this, idProducto, nombreProducto, ruta);
}

/*Metodo que permite llevar el proceso del viaje especifico*/
void GestorEnvios::procesarViaje(std::string idProducto, std::string nombreProducto, std::vector<Sucursal*> ruta) {
    // --- ESTE CÓDIGO SE EJECUTA EN UN HILO INDEPENDIENTE ---

    // 1. Aquí irá la lógica de dormir el hilo (sleep) y mover el producto
    // entre las colas de las sucursales de la 'ruta'.
    // ... (Lo implementaremos en el siguiente paso) ...


    // 2. Cuando el viaje termine, guardamos en el historial.
    HistorialEnvio nuevoRegistro;
    nuevoRegistro.setProducto(nombreProducto,idProducto);
    nuevoRegistro.setIdOrigen(ruta.front()->getId());
    nuevoRegistro.setIdDestino(ruta.back()->getId());

    for (Sucursal* suc : ruta) {
        nuevoRegistro.getTrayectoria().push_back(suc->getId());
    }

    //Bloqueo para colocar la trayectoria pasada
    mutexHistorial.lock();
    historial.push_back(nuevoRegistro);
    mutexHistorial.unlock();
}

/*Metodo que permite obtener el historial de envios que se van haciendo*/
std::vector<HistorialEnvio> GestorEnvios::getHistorial() {

    std::lock_guard<std::mutex> lock(mutexHistorial);
    return historial;
}
