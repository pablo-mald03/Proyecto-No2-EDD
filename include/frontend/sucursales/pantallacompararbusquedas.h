#ifndef PANTALLACOMPARARBUSQUEDAS_H
#define PANTALLACOMPARARBUSQUEDAS_H

#include <QWidget>

namespace Ui {
class PantallaCompararBusquedas;
}

class PantallaCompararBusquedas : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaCompararBusquedas(QWidget *parent = nullptr);
    ~PantallaCompararBusquedas();

private:
    Ui::PantallaCompararBusquedas *ui;

    void limpiarDatos();
    void limpiarLogs();

    /*Metodo que permite validar los campos de entrada*/
    bool validarPruebas(int &consultas, int &veces);

public slots:
    void appendHashLog(QString mensaje, QString color);
    void appendAvlLog(QString mensaje, QString color);
    void appendListOrdenadaLog(QString mensaje, QString color);
    void appendListNoOrdenadaLog(QString mensaje, QString color);

    void mostrarTiempo(int estructura, double milisegundos);

    void limpiarPantalla();

signals:
    /*Metodo que permite viajar a mostrar los arboles*/
    void verArboles();

    /*Metodo que permite generar las consultas aleatorias*/
    void pruebaAleatoria(int consultas,int veces);

private slots:
    void on_btnVerArboles_clicked();
    void on_btnAleatorio_clicked();
};

#endif // PANTALLACOMPARARBUSQUEDAS_H
