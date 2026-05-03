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

    /*Metodo que permite llenar los combos*/
    void inicializarCombos();

private slots:
    void on_btnAgregar_clicked();

    void on_btnLimpiar_clicked();

    void on_btnSucursales_clicked();

    void on_btnAsociar_clicked();

public slots:
    void appendGrafoLog(QString mensaje, QString color);

    void mostrarTiempo(double milisegundos);

    /*Metodo que permite dar el mensaje de exito o de error*/
    void confirmarAsociacion(QString mensaje, bool estado);

private:
    Ui::PantallaAgregarSucursal *ui;

    /*Metodo para validar los campos*/
    bool validarCampos();
    void limpiarDatos();
    void limpiarLogs();

    bool validarConexiones();

signals:
    /*Metodo que permite insertar sucursal*/
    void insertarSucursal(const std::string &_id,const std::string &_nombre, const std::string &_ubicacion, double _ingreso, double _despacho, double _preparacion);

    void asociarConexion(const std::string &_Origen, const std::string &_Destino,double _tiempo,double _costo);
    /*Metodo que permite viajar a mostrar los arboles*/
    void verSucursales();
};

#endif // PANTALLAAGREGARSUCURSAL_H
