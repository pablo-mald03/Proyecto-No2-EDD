#ifndef CONTROLADORNEGOCIO_H
#define CONTROLADORNEGOCIO_H

#include <QObject>

/*Controlador que permite llevar toda la logica para el manejo principal de las redes de sucursales*/
class ControladorNegocio : public QObject
{
    Q_OBJECT
public:
    explicit ControladorNegocio(QObject *parent = nullptr);
    ~ControladorNegocio();
};

#endif // CONTROLADORNEGOCIO_H
