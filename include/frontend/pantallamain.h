#ifndef PANTALLAMAIN_H
#define PANTALLAMAIN_H

#include <QWidget>

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


namespace Ui {
class PantallaMain;
}

class PantallaMain : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaMain(QWidget *parent = nullptr);
    ~PantallaMain();

    /*Metodo para reestablecer la Ui al inicio*/
    void mostrarInicio();

private slots:
    void on_btnCsv_clicked();

    void on_btnAgregar_clicked();

    void on_btnBuscarNombre_clicked();

    void on_btnBuscarBarra_clicked();

    void on_btnBuscarCategoria_clicked();

    void on_btnBuscarCaducidad_clicked();

    void on_btnEliminar_clicked();

    void on_btnListarNombre_clicked();

    void on_btnEstructuras_clicked();

    void on_btnCompararBusqueda_clicked();

private:
    Ui::PantallaMain *ui;

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
    void mostrarAgregar();
    void mostrarBuscarNombre();
    void mostrarBuscarCategoria();
    void mostrarBuscarRango();
    void mostrarEliminar();
    void mostrarListarNombre();
    void mostrarCompararBusqueda();
    void mostrarVerArboles();

    /*Metodo que permite ir cambiando el titulo dinamicamente del centro*/
    void solicitarTitulo(QString titulo);
signals:
    void limpiarAgregar();
    void limpiarBuscarNombre();
    void limpiarBuscarCategoria();
    void limpiarBuscarRango();
    void limpiarEliminar();
    void limpiarListar();

    /*Signal que permite ir cambiando el label de titulos*/
    void cambiarTitulo(QString _titulo);
};

#endif // PANTALLAMAIN_H
