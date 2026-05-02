#include "nodografico.h"

NodoGrafico::NodoGrafico(QString id, QString nombre, QColor color, bool modoVista, QGraphicsItem *parent)
    : QGraphicsObject(parent), idSucursal(id), nombreSucursal(nombre), colorFondo(color), esModoVista(modoVista)
{
    if (!esModoVista) {
        setAcceptedMouseButtons(Qt::LeftButton);
        setCursor(Qt::PointingHandCursor);
    }


    setZValue(1);
}

/*Metodo que permite dibujar el circulo del nodo*/
QRectF NodoGrafico::boundingRect() const {
    return QRectF(-30, -30, 60, 60);
}

/*Metodo que permite dibujar el circulo en pantalla*/
void NodoGrafico::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setBrush(colorFondo);
    painter->setPen(QPen(Qt::white, 2));
    painter->drawEllipse(-30, -30, 60, 60);

    painter->setPen(Qt::white);
    painter->setFont(QFont("Arial", 10, QFont::Bold));
    painter->drawText(boundingRect(), Qt::AlignCenter, idSucursal);
}

/*Metodo que detecta cuando se hizo click sobre el nodo*/
void NodoGrafico::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (!esModoVista) {
        emit seleccionado(idSucursal);
    }
    QGraphicsObject::mousePressEvent(event);
}
