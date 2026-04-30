#ifndef PANTALLACARGASUCURSALES_H
#define PANTALLACARGASUCURSALES_H

#include <QWidget>

namespace Ui {
class PantallaCargaSucursales;
}

class PantallaCargaSucursales : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaCargaSucursales(QWidget *parent = nullptr);
    ~PantallaCargaSucursales();

private:
    Ui::PantallaCargaSucursales *ui;
};

#endif // PANTALLACARGASUCURSALES_H
