#ifndef ELIMINARPRODUCTO_H
#define ELIMINARPRODUCTO_H

#include <QWidget>

namespace Ui {
class EliminarProducto;
}

class EliminarProducto : public QWidget
{
    Q_OBJECT

public:
    explicit EliminarProducto(QWidget *parent = nullptr);
    ~EliminarProducto();

private:
    Ui::EliminarProducto *ui;
};

#endif // ELIMINARPRODUCTO_H
