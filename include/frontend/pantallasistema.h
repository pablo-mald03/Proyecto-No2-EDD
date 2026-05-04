#ifndef PANTALLASISTEMA_H
#define PANTALLASISTEMA_H

#include "controladornegocio.h"
#include "pantallaagregarsucursal.h"
#include "pantallacargaenvios.h"
#include "pantallacargaproductos.h"
#include "pantallacargasucursales.h"
#include "pantallaeliminarsucursal.h"
#include "pantallamodificarsucursal.h"
#include "pantallaverenvios.h"
#include "pantallaversucursales.h"
#include <QWidget>

namespace Ui {
class PantallaSistema;
}

class PantallaSistema : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaSistema(QWidget *parent = nullptr);
    ~PantallaSistema();


    /*Metodos para poder comunicarse desde fuera con la pantalla*/
    void setPantallanInicio();

public slots:
    void mostrarVistaSucursales();

    void cargarSucursal(Sucursal* _sucursal, Grafo* _redGrafo, GestorEnvios* _gestor);

private slots:
    void on_btnCargaSucursales_clicked();

    void on_btnCargaEnvios_clicked();

    void on_btnCargarProductos_clicked();

    void on_btnAgregarSucursal_clicked();

    void on_btnModificarSucursal_clicked();

    void on_btnEliminarSucursal_clicked();

    void on_btnVerSucursales_clicked();

    void on_btnVerEnvios_clicked();

private:
    Ui::PantallaSistema *ui;

    /*Controlador*/
    ControladorNegocio * controladorGeneral;

    /*Referencias a las diferentes pantallas de la aplicacion*/
    PantallaCargaEnvios * pantallaCargadoEnvios = nullptr;
    PantallaCargaSucursales * pantallaCargadoSucursales = nullptr;
    PantallaCargaProductos * pantallaCargadoProductos = nullptr;

    PantallaAgregarSucursal * pantallaAgregadoSucursal = nullptr;
    PantallaModificarSucursal * pantallaModificadoSucursal = nullptr;
    PantallaEliminarSucursal * pantallaEliminadoSucursal = nullptr;
    PantallaVerSucursales * pantallaVistaSucursales = nullptr;
    PantallaVerEnvios * pantallaEnvios = nullptr;


    /*Metodos que permiten irse comunicando con la UI*/
    void mostrarCargaSucursales();
    void mostrarCargaEnvios();
    void mostrarCargaProductos();
    void mostrarAgregarSucursal();
    void mostrarModificarSucursal();
    void mostrarEliminarSucursal();
    void mostrarVerSucursales();
    void mostrarVerEnvios();


signals:

    /*Metodo que permite solicitar la apertura al padre*/
    void solicitarApertura(Sucursal* _sucursal, Grafo* _redGrafo, GestorEnvios* _gestor);

};

#endif // PANTALLASISTEMA_H
