#ifndef PANTALLABUSCARPORNOMBRE_H
#define PANTALLABUSCARPORNOMBRE_H

#include <QWidget>

namespace Ui {
class PantallaBuscarPorNombre;
}

class PantallaBuscarPorNombre : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaBuscarPorNombre(QWidget *parent = nullptr);
    ~PantallaBuscarPorNombre();

signals:
    /*Metodo que permite buscar*/
    void buscarPorNombre(std::string nombre);
    /*Metodo que permite viajar a mostrar los arboles*/
    void verArboles();

    /*Metodo que permite generar las consultas aleatorias*/
    void pruebaAleatoria(int consultas,int veces);

    /*Metodo que permite generar las consultas en extremos*/
    void pruebaExtremos(int consultas,int veces);


public slots:
    void appendAvlLog(QString mensaje, QString color);
    void appendListOrdenadaLog(QString mensaje, QString color);
    void appendListNoOrdenadaLog(QString mensaje, QString color);

    void mostrarTiempo(int estructura, double milisegundos);

    /*Metodo que permite mostrar el tiempo que tomo hacer las pruebas*/
    void mostrarTiempoPruebas(double milisegundos);

    void limpiarPantalla();

private slots:
    void on_btnBuscar_clicked();

    void on_btnLimpiar_clicked();

    void on_btnVerArboles_clicked();

    void on_btnAleatorio_clicked();

    void on_btnExtremos_clicked();

private:
    Ui::PantallaBuscarPorNombre *ui;

    void limpiarDatos();
    void limpiarLogs();

    /*Metodo que permite validar los campos de entrada*/
    bool validarPruebas(int &consultas, int &veces);
};

#endif // PANTALLABUSCARPORNOMBRE_H
