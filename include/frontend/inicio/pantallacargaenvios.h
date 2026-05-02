#ifndef PANTALLACARGAENVIOS_H
#define PANTALLACARGAENVIOS_H

#include <QWidget>

namespace Ui {
class PantallaCargaEnvios;
}

class PantallaCargaEnvios : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaCargaEnvios(QWidget *parent = nullptr);
    ~PantallaCargaEnvios();

private:
    Ui::PantallaCargaEnvios *ui;

    void limpiarLogs();

    std::vector<std::vector<QString>> parsearCSV(const QString &contenido);

    /*Metodo para descargar el log de errores*/
    void descargarLogErrores(const QString &contenido);

public slots:
    /*slots de la carga de sucursales*/
    void appendLogCarga(QString mensaje, QString color);
    void appendGrafoLog(QString mensaje, QString color);
    void mostrarTiempo(int estructura, double milisegundos);

    /*Metodo que permite verificar si hay errores para habilitar la descarga del log*/
    void evaluarErrores(bool evaluacion);

    /*Metodo que permite solicitar la lista de errores para poder armar el errors.log*/
    void logListoParaDescargar(const QString &contenido);

signals:
    void csvEnviosCargado(const std::vector<std::vector<QString>> & data);

    /*Metodo para solicitar el log de errores*/
    void solicitarLogErrores();

private slots:
    void on_btnCargar_clicked();
    void on_btnErrores_clicked();
};

#endif // PANTALLACARGAENVIOS_H
