#ifndef PANTALLAGESTION_H
#define PANTALLAGESTION_H

#include "controladorsucursal.h"
#include "grafo.h"
#include "pantallamain.h"
#include "pantallasucursal.h"
#include <QWidget>

namespace Ui {
class PantallaGestion;
}

class PantallaGestion : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaGestion(QWidget *parent = nullptr);
    ~PantallaGestion();

    /*Metodo que permite setear la sucursal que se va a mostrar*/
    void setSucursal(Sucursal* _sucursal, Grafo* _redGrafo, GestorEnvios* _gestor) ;

    void setPantallaInicio();

private:
    Ui::PantallaGestion *ui;

    /*Atributos para poder cambiar las pantallas*/
    PantallaSucursal * pantallaSucursal = nullptr;
    PantallaMain * pantallaMain = nullptr;

    ControladorSucursal * controladorGestion = nullptr;

    /*Atrbutos seteables que permiten tener el control total sobre los punteros que vienen del grafo y sucursales*/
    Sucursal * sucursal = nullptr;
    Grafo * redGrafo = nullptr;
    GestorEnvios* gestorEnvios = nullptr;

    /*Metodos de control de ventanas*/
    void mostrarSucursal();
    void mostrarProductos();

public slots:
    void cambiarLabel(QString _titulo);
private slots:
    void on_btnHome_clicked();

    void on_btnTienda_clicked();

    void on_btnProductos_clicked();

signals:
    void solicitarRegreso();

};

#endif // PANTALLAGESTION_H
