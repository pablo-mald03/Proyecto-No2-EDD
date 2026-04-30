#ifndef PANTALLASISTEMA_H
#define PANTALLASISTEMA_H

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

    /*Metodos que permiten irse comunicando con la UI*/
    void mostrarCargaSucursales();
    void mostrarCargaEnvios();
    void mostrarCargaProductos();
    void mostrarAgregarSucursal();
    void mostrarModificarSucursal();
    void mostrarEliminarSucursal();
    void mostrarVerSucursales();
    void mostrarVerEnvios();
};

#endif // PANTALLASISTEMA_H
