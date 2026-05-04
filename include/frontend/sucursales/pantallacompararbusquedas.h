#ifndef PANTALLACOMPARARBUSQUEDAS_H
#define PANTALLACOMPARARBUSQUEDAS_H

#include <QWidget>

namespace Ui {
class PantallaCompararBusquedas;
}

class PantallaCompararBusquedas : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaCompararBusquedas(QWidget *parent = nullptr);
    ~PantallaCompararBusquedas();

private:
    Ui::PantallaCompararBusquedas *ui;
};

#endif // PANTALLACOMPARARBUSQUEDAS_H
