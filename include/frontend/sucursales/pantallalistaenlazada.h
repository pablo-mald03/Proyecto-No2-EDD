#ifndef PANTALLALISTAENLAZADA_H
#define PANTALLALISTAENLAZADA_H

#include "nodolista.h"
#include "producto.h"
#include <QWidget>
#include <QWidget>
#include "graphicsviewzoom.h"
#include<QGraphicsView>
#include <QWheelEvent>
#include <QGraphicsTextItem>

namespace Ui {
class PantallaListaEnlazada;
}

class PantallaListaEnlazada : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaListaEnlazada(QWidget *parent = nullptr);
    ~PantallaListaEnlazada();
    void setCabeza(NodoLista<Producto> * _cabeza, int parametro);

    /*Metodo que permite generar el graphviz de la lista enlazada ordenada*/
    void generarGraphviz(std::string graph);

private:
    Ui::PantallaListaEnlazada *ui;

    QGraphicsScene * scene = nullptr;

    GraphicsViewZoom *zoomView = nullptr;

    /*Referencia de la cabeza de la lista*/
    NodoLista<Producto> * cabeza = nullptr;

    int parametroOrden = 0;

    /*Metodo que permite dibujar a la lista enlazada*/
    void dibujarListaEnlazada();

    /*Metodo que actualiza la vista*/
    void actualizarVista();

    /*Metodo para ilustrar la lista acorde al parametro de orden*/
    QString obtenerTexto(Producto & product);

signals:
    void solicitarGraphvizListaOrdenada();
private slots:
    void on_btnExportar_clicked();
};

#endif // PANTALLALISTAENLAZADA_H
