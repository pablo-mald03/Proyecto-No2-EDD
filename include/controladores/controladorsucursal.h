#ifndef CONTROLADORSUCURSAL_H
#define CONTROLADORSUCURSAL_H

#include "gestorenvios.h"
#include "grafo.h"
#include <QObject>

/*Controlador que permite llevar toda la logica para el manejo principal de cada sucursal*/
class ControladorSucursal: public QObject
{
    Q_OBJECT
public:
    explicit ControladorSucursal(QObject *parent = nullptr);
    ~ControladorSucursal();

    void setRecursosActuales(Sucursal* _sucursal, Grafo* _redGrafo, GestorEnvios* _gestor);

    Grafo * obtenerGrafo();
    Sucursal * obtenerSucursalActual();


private:
    Sucursal* sucursalActual = nullptr;
    Grafo* redGrafo = nullptr;
    GestorEnvios* gestorEnvios = nullptr;

    /*Metodo que permite realizar un envio desde una sucursal*/
    void enviarProducto(std::string idDestino, Producto* p,bool porTiempo);
};

#endif // CONTROLADORSUCURSAL_H
