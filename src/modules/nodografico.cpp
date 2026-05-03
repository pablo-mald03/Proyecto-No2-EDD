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


/*Metodo que permite actualizar el color del nodo*/
void NodoGrafico::actualizarColor(QColor nuevoColor) {
    this->colorFondo = nuevoColor;
    this->update();
}

/*Metodo que permite dibujar el circulo del nodo*/
QRectF NodoGrafico::boundingRect() const {
    return QRectF(-60, -60, 120, 120);
}

/*Metodo que permite dibujar los nodos del grafo*/
void NodoGrafico::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setRenderHint(QPainter::Antialiasing);

    painter->setBrush(colorFondo);
    painter->setPen(QPen(Qt::white, 3));
    painter->drawEllipse(-55, -55, 110, 110);

    painter->setPen(Qt::black);

    painter->setFont(QFont("Arial", 12, QFont::Bold));
    QRectF rectId(-50, -35, 100, 30);
    painter->drawText(rectId, Qt::AlignCenter, idSucursal);

    painter->setFont(QFont("Arial", 9));

    QRectF rectNombre(-50, 5, 100, 35);

    QString nombreCorto = painter->fontMetrics().elidedText(nombreSucursal, Qt::ElideRight, rectNombre.width());

    painter->drawText(rectNombre, Qt::AlignCenter | Qt::TextWordWrap, nombreCorto);
}

/*Metodo que detecta cuando se hizo click sobre el nodo*/
void NodoGrafico::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (!esModoVista) {
        emit seleccionado(idSucursal);
    }
    QGraphicsObject::mousePressEvent(event);
}
