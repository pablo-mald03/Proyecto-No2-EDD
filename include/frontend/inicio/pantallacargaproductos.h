#ifndef PANTALLACARGAPRODUCTOS_H
#define PANTALLACARGAPRODUCTOS_H

#include <QWidget>

namespace Ui {
class PantallaCargaProductos;
}

class PantallaCargaProductos : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaCargaProductos(QWidget *parent = nullptr);
    ~PantallaCargaProductos();

private:
    Ui::PantallaCargaProductos *ui;
};

#endif // PANTALLACARGAPRODUCTOS_H
