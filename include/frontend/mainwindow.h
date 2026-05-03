#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

/*Region de importacion de la UI*/
#include "pantallagestion.h"
#include "pantallasistema.h"



QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    /*Punteros de pantallas en la UI*/
    PantallaSistema *pantallaInicio = nullptr;

    PantallaGestion *pantallaGestion = nullptr;


    /*Metodos para navegar por la UI*/
    void mostrarInicio();
    void mostrarGestion(Sucursal * _sucursal, Grafo * redGrafo);

    /*Metodos signals que permiten dar ordenes a las pantallas hijas para que hagan acciones*/

public slots:
    void abrirSucursal(Sucursal * _sucursal, Grafo * redGrafo);
    void regresarPantalla();

signals:
    void regresoInicio();


};
#endif // MAINWINDOW_H
