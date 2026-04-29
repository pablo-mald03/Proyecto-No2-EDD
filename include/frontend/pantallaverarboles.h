#ifndef PANTALLAVERARBOLES_H
#define PANTALLAVERARBOLES_H

#include <QWidget>
#include "nodob.h"
#include"nodoavl.h"
#include"nodobmas.h"
#include"pantallaarbolavl.h"
#include"pantallaarbolb.h"
#include"pantallaarbolbmas.h"

namespace Ui {
class PantallaVerArboles;
}

class PantallaVerArboles : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaVerArboles(QWidget *parent = nullptr);
    ~PantallaVerArboles();

    /*Metodo que permite generar el reinicio y foco a la primera vista de los arboles*/
    void reestablecerVistas();

signals:

    /*Metodos para solicitar la grafica de los arboles*/
    void solicitarArbolAvl();
    void solicitarArbolB();
    void solicitarArbolBMas();

    /*Metodos que permiten solicitar el graphviz de los arboles*/
    void solicitarGraphArbolAvl();
    void solicitarGraphArbolB();
    void solicitarGraphArbolBMas();


public slots:
    /*Metodos que permiten generar la previsualizacion del estado actual de los arboles*/
    void recibirArbolAvl(NodoAvl * arbol);
    void recibirArbolB(NodoB * arbol);
    void recibirArbolBMas(NodoBMas * arbol);

    /*Metodos que permiten generar el graphviz del estado actual de los arboles*/
    void recibirGrapvizAvl(std::string dot);
    void recibirGrapvizB(std::string dot);
    void recibirGrapvizBMas(std::string dot);

private slots:
    void on_btnSiguiente_clicked();

    void on_btnAnterior_clicked();


    /*Metodos propios para solicitar estructuras de arboles*/
    void onSolicitarArbolAvl();
    void onSolicitarArbolB();
    void onSolicitarArbolBMas();

    /*Metodos para poder solicitar el graphviz de los arboles*/
    void onSolicitarGraphvizAvl();
    void onSolicitarGraphvizB();
    void onSolicitarGraphvizBMas();

private:
    Ui::PantallaVerArboles *ui;

    int contadorPantallas;

    /*Instancias de pantallas*/
    PantallaArbolAvl *pantallaAvl = nullptr;

    PantallaArbolB *pantallaB = nullptr;

    PantallaArbolBMas * pantallaBMas = nullptr;


    /*Metodos de carga entre pantallas*/
    void mostrarVistaAvl();
    void mostrarVistaB();
    void mostrarVistaBMas();
    void refrescarVista();

};

#endif // PANTALLAVERARBOLES_H
