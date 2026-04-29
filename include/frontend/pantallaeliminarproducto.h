#ifndef PANTALLAELIMINARPRODUCTO_H
#define PANTALLAELIMINARPRODUCTO_H

#include <QWidget>

namespace Ui {
class PantallaEliminarProducto;
}

class PantallaEliminarProducto : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaEliminarProducto(QWidget *parent = nullptr);
    ~PantallaEliminarProducto();

public slots:
    /*Metodos que permiten comunicar las lineas leidas por los arboles o listas enlazadas*/
    void appendAvlLog(QString mensaje, QString color);
    void appendBLog(QString mensaje, QString color);
    void appendBMasLog(QString mensaje, QString color);
    void appendListOrdenadaLog(QString mensaje, QString color);
    void appendListNoOrdenadaLog(QString mensaje, QString color);

    void mostrarTiempo(int estructura, double milisegundos);

    void limpiarPantalla();

signals:
    /*Metodo que permite eliminar un producto*/
    void eliminarProducto(std::string codigo);
    /*Metodo que permite viajar a mostrar los arboles*/
    void verArboles();


private slots:
    void on_btnEliminar_clicked();

    void on_btnLimpiar_clicked();

    void on_btnVerArboles_clicked();

private:
    Ui::PantallaEliminarProducto *ui;

    void limpiarDatos();
    void limpiarLogs();
};

#endif // PANTALLAELIMINARPRODUCTO_H
