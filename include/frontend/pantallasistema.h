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
    void csvSucursalesCargado(const std::vector<std::vector<QString>> & data);
    void csvConexionesCargado(const std::vector<std::vector<QString>> &data);

    void agregarLogGrafoSucursal(QString mensaje, QString color);
    void agregarLogCargaSucursal(QString mensaje, QString color);
    void agregarTiempoSucursal(int estructura, double milisegundos);

    /*Signals de carga de envios*/
    void csvEnviosCargado(const std::vector<std::vector<QString>> &data);

    void agregarLogGrafoEnvios(QString mensaje, QString color);
    void agregarLogCargaEnvios(QString mensaje, QString color);
    void agregarTiempoEnvios(int estructura, double milisegundos);


};

#endif // PANTALLASISTEMA_H
