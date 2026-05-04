#ifndef GESTORENVIOS_H
#define GESTORENVIOS_H

#include <vector>
#include <thread>
#include <mutex>
#include "historialenvio.h"
#include "sucursal.h"

class GestorEnvios
{
private:
    std::vector<std::thread> hilosActivos;

    //Historial de envios
    std::vector<HistorialEnvio> historial;
    std::mutex mutexHistorial;

    // Metodo que permite ejecutarse en cada hilo
    void procesarViaje(std::string idProducto, std::string nombreProducto, std::vector<Sucursal*> ruta);

public:
    GestorEnvios();
    ~GestorEnvios();

    // Metodo que permite iniciar un nuevo envio
    void iniciarEnvio(const std::string& idProducto, const std::string& nombreProducto, const std::vector<Sucursal*>& ruta);

    //Getter para que se pueda ver el Historial de envios en todo momento
    std::vector<HistorialEnvio> getHistorial();
};

#endif // GESTORENVIOS_H
