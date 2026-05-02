#ifndef PANTALLACARGASUCURSALES_H
#define PANTALLACARGASUCURSALES_H

#include <QWidget>

namespace Ui {
class PantallaCargaSucursales;
}

class PantallaCargaSucursales : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaCargaSucursales(QWidget *parent = nullptr);
    ~PantallaCargaSucursales();

private slots:
    void on_btnCargaSucursales_clicked();

    void on_btnCargaConexiones_clicked();

    void on_btnCargar_clicked();

    void on_btnErrores_clicked();

private:
    Ui::PantallaCargaSucursales *ui;

    bool cargarSucursales;

    void setCargaSucursales(bool carga, QString placeHolder);

    void limpiarLogs();

    std::vector<std::vector<QString>> parsearCSV(const QString &contenido);

    /*Metodo para descargar el log de errores*/
    void descargarLogErrores(const QString &contenido);

public slots:
    void appendLogCarga(QString mensaje, QString color);
    void appendGrafoLog(QString mensaje, QString color);
    void mostrarTiempo(int estructura, double milisegundos);

    /*Metodo que permite verificar si hay errores para habilitar la descarga del log*/
    void evaluarErrores(bool evaluacion);

    /*Metodo que permite solicitar la lista de errores para poder armar el errors.log*/
    void logListoParaDescargar(const QString &contenido);

signals:
    void csvSucursalesCargado(const std::vector<std::vector<QString>> & data);
    void csvConexionesCargado(const std::vector<std::vector<QString>> &data);

    /*Metodo para solicitar el log de errores*/
    void solicitarLogErrores(bool modoSucursal);
};

#endif // PANTALLACARGASUCURSALES_H
