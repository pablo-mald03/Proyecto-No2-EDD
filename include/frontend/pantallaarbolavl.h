#ifndef PANTALLAARBOLAVL_H
#define PANTALLAARBOLAVL_H

#include <QWidget>


class NodoAvl;
class QGraphicsScene;

namespace Ui {
class PantallaArbolAvl;
}

class PantallaArbolAvl : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaArbolAvl(QWidget *parent = nullptr);
    ~PantallaArbolAvl();

    void setArbol(NodoAvl *_arbol);

    /*Metodo que permite generar el graphviz del arbol*/
    void generarGraphviz(std::string graph);

signals:
    void solicitarArbolAvl();
    void solicitarGraphvizAvl();

private slots:
    void on_btnExportar_clicked();

private:
    Ui::PantallaArbolAvl *ui;

    QGraphicsScene * scene = nullptr;

    /*Referencia del arbol*/
    NodoAvl * arbol = nullptr;

    /*Metodo que actualiza la vista*/
    void actualizarVista();

    /*Metodos utilizador para poder dibujar el arbol avl*/
    QRectF dibujarNodo(int x, int y, QString texto, int altura);

    /*Metodo que permite dibujar las lineas de trazo*/
    void dibujarLinea(int x1, int y1, int x2, int y2);

    /*Pendiente cambiar*/
    void dibujarArbol(NodoAvl* nodo, int x, int y, int offset) ;

};
#endif // PANTALLAARBOLAVL_H
