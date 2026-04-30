#ifndef CONTROLADORSUCURSAL_H
#define CONTROLADORSUCURSAL_H

#include <QObject>

/*Controlador que permite llevar toda la logica para el manejo principal de cada sucursal*/
class ControladorSucursal: public QObject
{
    Q_OBJECT
public:
    explicit ControladorSucursal(QObject *parent = nullptr);
    ~ControladorSucursal();
};

#endif // CONTROLADORSUCURSAL_H
