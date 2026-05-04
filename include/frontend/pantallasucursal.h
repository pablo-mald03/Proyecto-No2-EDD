#ifndef PANTALLASUCURSAL_H
#define PANTALLASUCURSAL_H

#include "controladorsucursal.h"
#include "grafo.h"
#include "pantallacolaingreso.h"
#include "pantallacolapreparacion.h"
#include "pantallacolasalida.h"
#include "pantalladetallessucursal.h"
#include "pantallaenviarproductos.h"
#include "pantallahistorialenvios.h"
#include "pantallaverestadoenvios.h"
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



    PantallaColaIngreso * pantallaColaIngreso = nullptr;
    PantallaColaPreparacion * pantallaColaPreparacion = nullptr;
    PantallaColaSalida * pantallaColaSalida = nullptr;
    PantallaVerEstadoEnvios * pantallaEstadoEnvios = nullptr;
    PantallaHistorialEnvios * pantallaHistorial = nullptr;
    PantallaEnviarProductos * pantallaEnviarProducto = nullptr;
    PantallaDetallesSucursal * pantallaDetalles = nullptr;

    /*Metodo que permite mostrar los envios*/
    void mostrarEstadoEnvios();

    /*Metodo que permite agregar los recursos que se utilizaran en el backend*/
    void setRecursos(Sucursal* _sucursal, Grafo* _redGrafo, GestorEnvios* _gestor);


private:
    Ui::PantallaSucursal *ui;

    /*Metodo que permite ir cambiando el titulo dinamicamente del centro*/
    void solicitarTitulo(QString titulo);

    ControladorSucursal * controladorGestion = nullptr;

    /*Metodos de apertura de pantallas*/

    void mostrarEnvioProductos();

signals:
    /*Signal que permite ir cambiando el label de titulos*/
    void cambiarTitulo(QString _titulo);
private slots:
    void on_btnVerEnvios_clicked();
    void on_btnEnvioProducto_clicked();
};

#endif // PANTALLASUCURSAL_H
