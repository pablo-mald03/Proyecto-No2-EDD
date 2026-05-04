#ifndef PANTALLAENVIARPRODUCTOS_H
#define PANTALLAENVIARPRODUCTOS_H

#include <QWidget>

namespace Ui {
class PantallaEnviarProductos;
}

class PantallaEnviarProductos : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaEnviarProductos(QWidget *parent = nullptr);
    ~PantallaEnviarProductos();

private:
    Ui::PantallaEnviarProductos *ui;
};

#endif // PANTALLAENVIARPRODUCTOS_H
