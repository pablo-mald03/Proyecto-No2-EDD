#ifndef GESTORMAPA_H
#define GESTORMAPA_H

#include "grafo.h"
class GestorMapa
{
public:
    GestorMapa();
    ~GestorMapa();

    /*Metodo que permite insertar una nueva sucursal*/
    void insertarSucursal(const std::string &id, const std::string &nombre, const std::string &ubicacion,
                          double _ingreso, double _preparacion, double _despacho);

    /*Metodo que permite insertar conexiones entre sucursales*/
    void insertarConexion(const std::string& _origen, const std::string& _destino, double _tiempo, double _costo);

    /*Metodo que permite editar una sucursal*/
    void editarSucursal(const std::string &id, const std::string &nombre,
                        const std::string &ubicacion, double _ingreso,
                        double _preparacion, double _despacho);

    /*Metodo que permite eliminar una sucursal*/
    void eliminarSucursal(const std::string &id);

    /*Metodo que permite buscar una sucursal*/
    Sucursal* buscarSucursal(const std::string &id);

    /*Metodo que permite obtener el graphviz del grafo*/
    std::string obtenerGraphvizGrafo();

    /*Metodo que permite hallar la ruta mas cotra de envio de produtos*/
    std::vector<Sucursal*> hallarRutaCorta(const std::string& origen, const std::string& destino, bool porTiempo);

    /*Metodo que permite validar las filas del csv de sucursales*/
    bool validarFilaCsvSucursal(const std::vector<QString>& fila, double& tIng, double& tTras, double& tDesp, QString& error);

    /*Metodo que permite validar las filas del csv de conexiones de las sucursales*/
    bool validarFilaCsvConexion(const std::vector<QString>& fila, double& tiempo, double& costo, QString& error);

private:
    Grafo * grafoSucursales = nullptr;


};

#endif // GESTORMAPA_H
