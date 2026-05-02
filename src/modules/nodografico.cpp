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

/*Metodo que permite actualizar el color del nodo*/
void NodoGrafico::actualizarColor(QColor nuevoColor) {
    this->colorFondo = nuevoColor;
    this->update();
}

/*Metodo que permite dibujar el circulo en pantalla*/
void NodoGrafico::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setRenderHint(QPainter::Antialiasing);

    painter->setBrush(colorFondo);
    painter->setPen(QPen(Qt::white, 2));
    painter->drawEllipse(-30, -30, 60, 60);

    painter->setPen(Qt::black);

    painter->setFont(QFont("Arial", 10, QFont::Bold));
    QRectF rectId(-30, -20, 60, 25);
    painter->drawText(rectId, Qt::AlignCenter, idSucursal);

    painter->setFont(QFont("Arial", 7));
    QRectF rectNombre(-25, 2, 50, 20);

    QString nombreCorto = painter->fontMetrics().elidedText(nombreSucursal, Qt::ElideRight, rectNombre.width());
    painter->drawText(rectNombre, Qt::AlignCenter, nombreCorto);
}

/*Metodo que detecta cuando se hizo click sobre el nodo*/
void NodoGrafico::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (!esModoVista) {
        emit seleccionado(idSucursal);
    }
    QGraphicsObject::mousePressEvent(event);
}
