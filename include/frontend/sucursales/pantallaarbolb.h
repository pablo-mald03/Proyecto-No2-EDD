#ifndef PANTALLAARBOLB_H
#define PANTALLAARBOLB_H

#include "graphicsviewzoom.h"
#include <QWidget>
#include<QGraphicsView>
#include <QWheelEvent>
#include <QGraphicsTextItem>

class NodoB;
class QGraphicsScene;


namespace Ui {
class PantallaArbolB;
}

class PantallaArbolB : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaArbolB(QWidget *parent = nullptr);
    ~PantallaArbolB();
    void setArbol(NodoB * _arbol);

    /*Metodo que permite generar el graphviz del arbol B*/
    void generarGraphviz(std::string graph);

signals:
    void solicitarArbolB();
    void solicitarGraphvizB();

private slots:
    void on_btnExportar_clicked();

private:
    Ui::PantallaArbolB *ui;

    QGraphicsScene * scene = nullptr;

    GraphicsViewZoom *zoomView = nullptr;

    /*Referencia del arbol*/
    NodoB * raiz = nullptr;

    /*Metodo que permite dibujar a los nodos*/
    int dibujarNodoB(int x, int y, NodoB* nodo);

    /*Metodo que permite dibujar a las lineas que unen a los nodos*/
    void dibujarLineaB(int x1, int y1, int x2, int y2);

    /*Pendiente reemplazar PENDIENTE LA INTEGRACION REAL*/
    void dibujarArbolB(NodoB* nodo, int x, int y);

    /*Metodo que actualiza la vista*/
    void actualizarVista();

    /*Metodo que permite obtener el ancho total de la lista para poder generar una mejor distribucion*/
    int getAnchoTotal(NodoB* nodo);

    /*Metodo que permite calcular el ancho del nodo real*/
    int getAnchoNodoReal(NodoB* nodo);
};

#endif // PANTALLAARBOLB_H
