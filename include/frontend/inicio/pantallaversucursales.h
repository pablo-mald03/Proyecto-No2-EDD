#ifndef PANTALLAVERSUCURSALES_H
#define PANTALLAVERSUCURSALES_H

#include <QWidget>

namespace Ui {
class PantallaVerSucursales;
}

class PantallaVerSucursales : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaVerSucursales(QWidget *parent = nullptr);
    ~PantallaVerSucursales();

private:
    Ui::PantallaVerSucursales *ui;
};

#endif // PANTALLAVERSUCURSALES_H
