#ifndef PANTALLAPRINCIPAL_H
#define PANTALLAPRINCIPAL_H

#include <QWidget>

namespace Ui {
class PantallaPrincipal;
}

class PantallaPrincipal : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaPrincipal(QWidget *parent = nullptr);
    ~PantallaPrincipal();

private slots:
    void on_btnCargar_clicked();

    void on_btnErrores_clicked();

    void on_btnExportar_clicked();

    void on_btnCerrar_clicked();

signals:
    void csvCargado(const std::vector<QString>& data);

    void solicitarLogErrores();

    void solicitarRefrescarDatos();

    void solicitarGuardarCsv();

    /*Metodo que permite borrar el estado completo de la carga del archivo de entrada tras cerrar */
    void solicitarLimpieza();

public slots:

    /*Metodo que permite guardar el csv*/
    void recibirGuardadoCsv(const QString &contenido);

    /*Metodo que permite refrescar la pantalla de carga de csv*/
    void refrescarPantallaCsv(bool estaCargado);

    /*Metodos que permiten comunicar las lineas leidas por los arboles o lista enlazada*/
    void appendAvlLog(QString mensaje, QString color);
    void appendBLog(QString mensaje, QString color);
    void appendBMasLog(QString mensaje, QString color);
    void appendListLog(QString mensaje, QString color);

    void appendLogCarga(QString mensaje, QString color);

    void mostrarTiempo(int estructura, double milisegundos);

    /*Metodo que permite verificar si hay errores para habilitar la descarga del log*/
    void evaluarErrores(bool evaluacion);

    /*Metodo que permite solicitar la lista de errores para poder armar el errors.log*/
    void logListoParaDescargar(const QString &contenido);

    /*Metodo utilizado para poder cerrar el csv cargado*/
    void evaluarCierreCsv(bool evaluacion);

private:
    Ui::PantallaPrincipal *ui;

    /*Atributo que permite saber si ya hay un csv Cargado*/
    bool hayCsv;

    /*Metodo para descargar el log de errores*/
    void descargarLogErrores(const QString &contenido);

    /*Metodo que permite limpiar los datos por cada vez que se vuelva a cargar un nuevo csv*/
    void limpiarLogs();

};

#endif // PANTALLAPRINCIPAL_H
