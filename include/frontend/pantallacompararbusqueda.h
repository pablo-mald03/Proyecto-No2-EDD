#ifndef PANTALLACOMPARARBUSQUEDA_H
#define PANTALLACOMPARARBUSQUEDA_H

#include <QWidget>

namespace Ui {
class PantallaCompararBusqueda;
}

class PantallaCompararBusqueda : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaCompararBusqueda(QWidget *parent = nullptr);
    ~PantallaCompararBusqueda();

private:
    Ui::PantallaCompararBusqueda *ui;
};

#endif // PANTALLACOMPARARBUSQUEDA_H
