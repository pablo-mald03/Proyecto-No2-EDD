#ifndef PANTALLAAGREGARSUCURSAL_H
#define PANTALLAAGREGARSUCURSAL_H

#include <QWidget>

namespace Ui {
class PantallaAgregarSucursal;
}

class PantallaAgregarSucursal : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaAgregarSucursal(QWidget *parent = nullptr);
    ~PantallaAgregarSucursal();

    void limpiarPantalla();

private slots:
    void on_btnAgregar_clicked();

    void on_btnLimpiar_clicked();

    void on_btnSucursales_clicked();

public slots:
    void appendGrafoLog(QString mensaje, QString color);

    void mostrarTiempo(double milisegundos);

private:
    Ui::PantallaAgregarSucursal *ui;

    /*Metodo para validar los campos*/
    bool validarCampos();
    void limpiarDatos();
    void limpiarLogs();

signals:
    /*Metodo que permite insertar sucursal*/
    void insertarSucursal(int _id,const std::string &_nombre, const std::string &_ubicacion, double _ingreso, double _despacho, double _preparacion);
    /*Metodo que permite viajar a mostrar los arboles*/
    void verSucursales();
};

#endif // PANTALLAAGREGARSUCURSAL_H
