#ifndef PANTALLASUCURSAL_H
#define PANTALLASUCURSAL_H

#include <QWidget>

namespace Ui {
class PantallaSucursal;
}

class PantallaSucursal : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaSucursal(QWidget *parent = nullptr);
    ~PantallaSucursal();

private:
    Ui::PantallaSucursal *ui;
};

#endif // PANTALLASUCURSAL_H
