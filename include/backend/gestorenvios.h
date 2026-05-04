#ifndef GESTORENVIOS_H
#define GESTORENVIOS_H

#include <vector>
#include <thread>
#include <mutex>
#include "grafo.h"
#include "historialenvio.h"
#include "sucursal.h"

class GestorEnvios
{
private:
    Grafo* redGrafo;

    std::vector<std::thread> hilosActivos;

    //Historial de envios
    std::vector<HistorialEnvio> historial;
    std::mutex mutexHistorial;

    // Metodo que permite ejecutarse en cada hilo
    void procesarViaje(Producto* paquete, std::vector<Sucursal*> ruta,bool porTiempo);

public:
    GestorEnvios(Grafo* _grafo);
    ~GestorEnvios();

    // Metodo que permite iniciar un nuevo envio (Corregido a Producto*)
    void iniciarEnvio(Producto* paquete, const std::vector<Sucursal*>& ruta,bool porTiempo);

    // Metodo que permite que se pueda ver el Historial de envios en todo momento
    std::vector<HistorialEnvio> getHistorial();

    /*Metodo que permite generar el set de la red del grafo*/
    void setRedGrafo( Grafo* _redGrafo);
};

#endif // GESTORENVIOS_H
