#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

/*Region de importacion de la UI*/
#include"pantallaprincipal.h"
#include"controlador.h"
#include"pantallaagregar.h"
#include"pantallabuscarpornombre.h"
#include"pantallabuscarporcategoria.h"
#include"pantallaagregar.h"
#include"pantallabuscarrango.h"
#include"pantallaeliminarproducto.h"
#include"pantallaverarboles.h"
#include"pantallalistarnombre.h"


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

private slots:
    void on_btnCsv_clicked();

    void on_btnAgregar_clicked();

    void on_btnBuscarNombre_clicked();

    void on_btnBuscarCategoria_clicked();

    void on_btnBuscarCaducidad_clicked();

    void on_btnEliminar_clicked();

    void on_btnListarNombre_clicked();

    void on_btnArboles_clicked();

private:
    Ui::MainWindow *ui;

    /*Punteros de pantallas en la UI*/
    PantallaPrincipal *inicio = nullptr;

    PantallaAgregar * pantallaAgregar = nullptr;

    PantallaBuscarPorNombre * pantallaBusquedaNombre = nullptr;

    PantallaBuscarPorCategoria * pantallaBusquedaCategoria = nullptr;

    PantallaBuscarRango * pantallaBusquedaRango = nullptr;

    PantallaEliminarProducto * pantallaEliminar = nullptr;

    PantallaVerArboles * pantallaVerArboles = nullptr;

    PantallaListarNombre * pantallaListarNombre = nullptr;

    /*Punteros de pantallas en la UI*/

    /*Controlador*/
    Controlador * controladorCrud;


    /*Metodos para navegar por la UI*/
    void mostrarInicio();
    void mostrarAgregar();
    void mostrarBuscarNombre();
    void mostrarBuscarCategoria();
    void mostrarBuscarRango();
    void mostrarEliminar();
    void mostrarListarNombre();
    void mostrarCompararBusqueda();
    void mostrarVerArboles();

    /*Metodos para navegar por la UI*/

    /*Metodos signals que permiten dar ordenes a las pantallas hijas para que hagan acciones*/
signals:
    void limpiarAgregar();
    void limpiarBuscarNombre();
    void limpiarBuscarCategoria();
    void limpiarBuscarRango();
    void limpiarEliminar();
    void limpiarListar();

};
#endif // MAINWINDOW_H
