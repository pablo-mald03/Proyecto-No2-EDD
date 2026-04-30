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

    /*Metodo que permite ir cambiando el titulo dinamicamente del centro*/
    void solicitarTitulo(QString titulo);

signals:
    /*Signal que permite ir cambiando el label de titulos*/
    void cambiarTitulo(QString _titulo);
};

#endif // PANTALLASUCURSAL_H
