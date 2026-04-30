#ifndef PANTALLAGESTION_H
#define PANTALLAGESTION_H

#include "pantallamain.h"
#include "pantallasucursal.h"
#include <QWidget>

namespace Ui {
class PantallaGestion;
}

class PantallaGestion : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaGestion(QWidget *parent = nullptr);
    ~PantallaGestion();


private:
    Ui::PantallaGestion *ui;

    /*Atributos para poder cambiar las pantallas*/
    PantallaSucursal * pantallaSucursal = nullptr;
    PantallaMain * pantallaMain = nullptr;


    /*Metodos de control de ventanas*/
    void mostrarSucursal();
    void mostrarProductos();

public slots:
    void cambiarLabel(QString _titulo);
private slots:
    void on_btnHome_clicked();
};

#endif // PANTALLAGESTION_H
