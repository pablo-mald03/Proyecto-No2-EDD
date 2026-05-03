#ifndef PANTALLAMODIFICARSUCURSAL_H
#define PANTALLAMODIFICARSUCURSAL_H

#include <QWidget>

/*STRUCT TEMPORAL PENDIENTE REMOVER*/
struct Sucursal1 {
    QString id;
    QString nombre;
    QString ubicacion;
};

namespace Ui {
class PantallaModificarSucursal;
}

class PantallaModificarSucursal : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaModificarSucursal(QWidget *parent = nullptr);
    ~PantallaModificarSucursal();

    void limpiarPantalla();

    void inicializarCombo();

private:
    Ui::PantallaModificarSucursal *ui;

    /*Metodo para validar los campos*/
    bool validarCampos();
    void limpiarDatos();
    void limpiarLogs();

    Sucursal1 buscarEnHashHardcoded(QString id);

public slots:
    void appendGrafoLog(QString mensaje, QString color);

    void mostrarTiempo(double milisegundos);

signals:
    /*Metodo que permite insertar sucursal*/
    void modificarSucursal(const std::string &_id,const std::string &_nombre, const std::string &_ubicacion, double _ingreso, double _despacho, double _preparacion);
    /*Metodo que permite viajar a mostrar los arboles*/
    void verSucursales();
private slots:
    void on_btnModificar_clicked();
    void on_btnQuitar_clicked();
    void on_comboBox_currentIndexChanged(int index);
    void on_btnSucursales_clicked();
    void on_btnLimpiar_clicked();
};

#endif // PANTALLAMODIFICARSUCURSAL_H
