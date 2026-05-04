#ifndef PANTALLADETALLESSUCURSAL_H
#define PANTALLADETALLESSUCURSAL_H

#include <QWidget>

namespace Ui {
class PantallaDetallesSucursal;
}

class PantallaDetallesSucursal : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaDetallesSucursal(QWidget *parent = nullptr);
    ~PantallaDetallesSucursal();

private:
    Ui::PantallaDetallesSucursal *ui;
};

#endif // PANTALLADETALLESSUCURSAL_H
