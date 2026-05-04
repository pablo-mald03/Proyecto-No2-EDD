#ifndef PANTALLASUCURSAL_H
#define PANTALLASUCURSAL_H

#include "controladorsucursal.h"
#include "grafo.h"
#include <QWidget>

namespace Ui {
class PantallaSucursal;
}

class PantallaSucursal : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaSucursal(QWidget *parent = nullptr);
    ~PantallaSucursal();

    ControladorSucursal * controlador = nullptr;

    /*Metodo que permite agregar los recursos que se utilizaran en el backend*/
    void setRecursos(Sucursal* _sucursal, Grafo* _redGrafo, GestorEnvios* _gestor);


private:
    Ui::PantallaSucursal *ui;

    /*Metodo que permite ir cambiando el titulo dinamicamente del centro*/
    void solicitarTitulo(QString titulo);

signals:
    /*Signal que permite ir cambiando el label de titulos*/
    void cambiarTitulo(QString _titulo);
};

#endif // PANTALLASUCURSAL_H
