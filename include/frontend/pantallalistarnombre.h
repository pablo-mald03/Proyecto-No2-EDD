#ifndef PANTALLALISTARNOMBRE_H
#define PANTALLALISTARNOMBRE_H

#include <QWidget>

namespace Ui {
class PantallaListarNombre;
}

class PantallaListarNombre : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaListarNombre(QWidget *parent = nullptr);
    ~PantallaListarNombre();

signals:
    /*Metodo que permite listar los produtos por nombres*/
    void listarPorNombres();
    /*Metodo que permite viajar a mostrar los arboles*/
    void verArboles();

private:
    Ui::PantallaListarNombre *ui;
    void limpiarLogs();

public slots:
    void appendAvlLog(QString mensaje, QString color);
    void appendListOrdenadaLog(QString mensaje, QString color);
    void appendListNoOrdenadaLog(QString mensaje, QString color);

    void mostrarTiempo(int estructura, double milisegundos);

    void limpiarPantalla();

private slots:
    void on_btnBuscar_clicked();
    void on_btnLimpiar_clicked();
    void on_btnVerArboles_clicked();
};

#endif // PANTALLALISTARNOMBRE_H
