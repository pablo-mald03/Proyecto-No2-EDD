#ifndef NODOGRAFICO_H
#define NODOGRAFICO_H

#include <QGraphicsObject>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QColor>
#include <QCursor>

class NodoGrafico : public QGraphicsObject {
    Q_OBJECT
public:
    // Agregamos color y modoVista con valores por defecto
    NodoGrafico(QString id, QString nombre, QColor color = QColor(0x3d5afe), bool modoVista = false, QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

signals:
    void seleccionado(QString id);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QString idSucursal;
    QString nombreSucursal;
    QColor colorFondo;
    bool esModoVista;
};

#endif // NODOGRAFICO_H
