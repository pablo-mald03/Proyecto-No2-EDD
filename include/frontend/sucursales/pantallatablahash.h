#ifndef PANTALLATABLAHASH_H
#define PANTALLATABLAHASH_H

#include "listaenlazada.h"
#include "producto.h"
#include <QWidget>
#include "graphicsviewzoom.h"
#include<QGraphicsView>
#include <QWheelEvent>
#include <QGraphicsTextItem>

namespace Ui {
class PantallaTablaHash;
}

class PantallaTablaHash : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaTablaHash(QWidget *parent = nullptr);
    ~PantallaTablaHash();
    void setTabla(ListaEnlazada<Producto>**  _tabla, int capacidad);

    /*Metodo que permite generar el graphviz del arbol B*/
    void generarGraphviz(std::string graph);

private:
    Ui::PantallaTablaHash *ui;

    QGraphicsScene * scene = nullptr;

    GraphicsViewZoom *zoomView = nullptr;

    /*Referencia de la tabla*/
    ListaEnlazada<Producto>** tabla = nullptr;

    int capacidadTabla = 0;

    /*Metodo que permite dibujar a la tabla hash*/
    void dibujarTablaHash();

    /*Metodo que actualiza la vista*/
    void actualizarVista();

signals:
    void solicitarTablaHash();
    void solicitarGraphvizHash();
private slots:
    void on_btnExportar_clicked();
};

#endif // PANTALLATABLAHASH_H
