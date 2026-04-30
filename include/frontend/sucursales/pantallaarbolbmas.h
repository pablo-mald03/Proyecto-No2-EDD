#ifndef PANTALLAARBOLBMAS_H
#define PANTALLAARBOLBMAS_H

#include "graphicsviewzoom.h"
#include <QWidget>
#include<QGraphicsView>
#include <QWheelEvent>
#include <QGraphicsTextItem>

#include <unordered_map>


class NodoBMas;
class QGraphicsScene;


namespace Ui {
class PantallaArbolBMas;
}

class PantallaArbolBMas : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaArbolBMas(QWidget *parent = nullptr);
    ~PantallaArbolBMas();

    /*Metodo que permite obtener la raiz del arbol para poder graficarla*/
    void setArbol(NodoBMas * _arbol);

    /*Metodo que permite generar el graphviz del arbol B+*/
    void generarGraphviz(std::string graph);

signals:
    void solicitarArbolBMas();
    void solicitarGraphvizBMas();

private slots:
    void on_btnExportar_clicked();

private:
    Ui::PantallaArbolBMas *ui;

    QGraphicsScene * scene = nullptr;

    GraphicsViewZoom *zoomView = nullptr;

    /*Referencia del arbol*/
    NodoBMas * raiz = nullptr;

    std::unordered_map<NodoBMas*, int> posicionesX;
    std::unordered_map<NodoBMas*, int> posicionesY;

    /*Metodo que actualiza la vista*/
    void actualizarVista();

    /*Metodo que permite dibujar a los nodos*/
    int dibujarNodoBMas(int x, int y, NodoBMas* nodo);

    /*Metodo que permite dibujar a las lineas que unen a los nodos*/
    void dibujarLineaBMas(int x1, int y1, int x2, int y2);

    /*Metodo que permite dibujar el arbol B+*/
    void dibujarArbolBMas(NodoBMas* nodo, int x, int y);

    /*Metodo que permite recorrer la lista para poder dibujar una flecha verde*/
    void dibujarConexionesHojas(NodoBMas* nodoRaiz);

    /*Metodo que permite obtener el ancho real del nodo*/
    int getAnchoNodoReal(NodoBMas* nodo);

    /*Metodo que permite obtener el ancho total de la lista para poder generar una mejor distribucion*/
    int getAnchoTotal(NodoBMas* nodo);

};

#endif // PANTALLAARBOLBMAS_H
