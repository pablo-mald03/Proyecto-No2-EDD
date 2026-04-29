#include "graphicsviewzoom.h"

GraphicsViewZoom::GraphicsViewZoom(QWidget *parent)
    : QGraphicsView(parent)
{

    this->setStyleSheet("background-color: #1a1a1a; border: none;");
    setDragMode(QGraphicsView::ScrollHandDrag);

    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setResizeAnchor(QGraphicsView::AnchorUnderMouse);

    setRenderHint(QPainter::Antialiasing);
    setInteractive(true);
}

/*Metodo que permite generar el drag*/
void GraphicsViewZoom::wheelEvent(QWheelEvent *event)
{
    if (event->angleDelta().y() > 0)
        scale(1.15, 1.15);
    else
        scale(0.85, 0.85);
}
