#ifndef PANTALLAAGREGARSUCURSAL_H
#define PANTALLAAGREGARSUCURSAL_H

#include <QWidget>

namespace Ui {
class PantallaAgregarSucursal;
}

class PantallaAgregarSucursal : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaAgregarSucursal(QWidget *parent = nullptr);
    ~PantallaAgregarSucursal();

private:
    Ui::PantallaAgregarSucursal *ui;
};

#endif // PANTALLAAGREGARSUCURSAL_H
