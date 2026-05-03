#ifndef CONTROLADORSUCURSAL_H
#define CONTROLADORSUCURSAL_H

#include "grafo.h"
#include <QObject>

/*Controlador que permite llevar toda la logica para el manejo principal de cada sucursal*/
class ControladorSucursal: public QObject
{
    Q_OBJECT
public:
    explicit ControladorSucursal(QObject *parent = nullptr);
    ~ControladorSucursal();

    void setRecursosActuales(Sucursal * _sucursal, Grafo * _redGrafo);

private:
    Sucursal * sucursalAcutal = nullptr;
    Grafo * redGrafo = nullptr;
};

#endif // CONTROLADORSUCURSAL_H
