#ifndef HISTORIALENVIO_H
#define HISTORIALENVIO_H

#include <string>
#include <vector>

class HistorialEnvio
{
public:
    HistorialEnvio();
    HistorialEnvio(std::string _idOrigen,
                   std::string _idDestino,
                   std::vector<std::string> _trayectoria,
                   std::string _nombreProd,
                   std::string _idProd);

private:
    std::string idOrigen;
    std::string idDestino;
    std::vector<std::string> trayectoria;
    std::string nombreProducto;
    std::string idProducto;
public:
    std::string getIdOrigen() const;
    std::string getIdDestino() const;
    std::vector<std::string>& getTrayectoria();
    std::string getNombreProducto() const;
    std::string getIdProducto() const;

    // Setters
    void setIdOrigen(const std::string& id);
    void setIdDestino(const std::string& id);
    void setTrayectoria(const std::vector<std::string>& tray);
    void setProducto(const std::string& nombre, const std::string& id);

};

#endif // HISTORIALENVIO_H
