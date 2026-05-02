#ifndef PANTALLAELIMINARSUCURSAL_H
#define PANTALLAELIMINARSUCURSAL_H

#include <QWidget>

namespace Ui {
class PantallaEliminarSucursal;
}

class PantallaEliminarSucursal : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaEliminarSucursal(QWidget *parent = nullptr);
    ~PantallaEliminarSucursal();

    void limpiarPantalla();

public slots:
    void appendGrafoLog(QString mensaje, QString color);

    void mostrarTiempo(double milisegundos);

private:
    Ui::PantallaEliminarSucursal *ui;

    /*Metodo para validar los campos*/
    bool validarCampos();
    void limpiarDatos();
    void limpiarLogs();

signals:
    /*Metodo que permite insertar sucursal*/
    void eliminarSucursal(const std::string &_id);
    /*Metodo que permite viajar a mostrar los arboles*/
    void verSucursales();
private slots:
    void on_btnEliminar_clicked();
    void on_btnLimpiar_clicked();
    void on_btnSucursales_clicked();
};

#endif // PANTALLAELIMINARSUCURSAL_H
