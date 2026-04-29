#ifndef GRAPHICSVIEWZOOM_H
#define GRAPHICSVIEWZOOM_H
#include <QGraphicsView>
#include <QWheelEvent>

class GraphicsViewZoom : public QGraphicsView
{
    Q_OBJECT

public:
    explicit GraphicsViewZoom(QWidget *parent = nullptr);

protected:
    void wheelEvent(QWheelEvent *event) override;
};


#endif // GRAPHICSVIEWZOOM_H
