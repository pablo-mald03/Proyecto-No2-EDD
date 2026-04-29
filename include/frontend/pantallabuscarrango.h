#ifndef PANTALLABUSCARRANGO_H
#define PANTALLABUSCARRANGO_H

#include <QWidget>

namespace Ui {
class PantallaBuscarRango;
}

class PantallaBuscarRango : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaBuscarRango(QWidget *parent = nullptr);
    ~PantallaBuscarRango();

private:
    Ui::PantallaBuscarRango *ui;
    void limpiarDatos();
    void limpiarLogs();

    /*Metodo que permite validar los campos de entrada*/
    bool validarPruebas(int &consultas, int &veces);

signals:

    void buscarPorFechas(std::string limiteInferior, std::string limiteSuperior);

    /*Metodo que permite viajar a mostrar los arboles*/
    void verArboles();

    /*Metodo que permite generar las consultas aleatorias*/
    void pruebaAleatoria(int consultas,int veces, const std::string &limiteInferior, const std::string &limiteSuperior);

    /*Metodo que permite generar las consultas en extremos*/
    void pruebaExtremos(int consultas,int veces);


public slots:
    void appendBLog(QString mensaje, QString color);
    void appendListOrdenadaLog(QString mensaje, QString color);
    void appendListNoOrdenadaLog(QString mensaje, QString color);

    void mostrarTiempo(int estructura, double milisegundos);

    /*Metodo que permite mostrar el tiempo que tomo hacer las pruebas*/
    void mostrarTiempoPruebas(double milisegundos);

    void limpiarPantalla();

private slots:
    void on_btnLimpiar_clicked();
    void on_btnBuscar_clicked();
    void on_btnVerArboles_clicked();
    void on_btnAleatorio_clicked();
    void on_btnExtremos_clicked();
};

#endif // PANTALLABUSCARRANGO_H
