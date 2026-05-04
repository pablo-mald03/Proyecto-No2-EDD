#ifndef PANTALLACARGAPRODUCTOS_H
#define PANTALLACARGAPRODUCTOS_H

#include <QWidget>

namespace Ui {
class PantallaCargaProductos;
}

class PantallaCargaProductos : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaCargaProductos(QWidget *parent = nullptr);
    ~PantallaCargaProductos();

private slots:
    void on_btnErrores_clicked();

    void on_btnCargar_clicked();

public slots:

    /*Metodos que permiten comunicar las lineas leidas por los arboles o lista enlazada*/
    void appendAvlLog(QString mensaje, QString color);
    void appendBLog(QString mensaje, QString color);
    void appendBMasLog(QString mensaje, QString color);
    void appendListLog(QString mensaje, QString color);
    void appendHashLog(QString mensaje, QString color);

    void mostrarTiempo(int estructura, double milisegundos);

    void appendLogCarga(QString mensaje, QString color);

    /*Metodo que permite verificar si hay errores para habilitar la descarga del log*/
    void evaluarErrores(bool evaluacion);

    /*Metodo que permite solicitar la lista de errores para poder armar el errors.log*/
    void logListoParaDescargar(const QString &contenido);

private:
    Ui::PantallaCargaProductos *ui;

    void limpiarLogs();

    std::vector<std::vector<QString>> parsearCSV(const QString &contenido);

    /*Metodo para descargar el log de errores*/
    void descargarLogErrores(const QString &contenido);

signals:
    void csvProductosCargado(const std::vector<std::vector<QString>> & data);

    void solicitarLogErrores();

};

#endif // PANTALLACARGAPRODUCTOS_H
