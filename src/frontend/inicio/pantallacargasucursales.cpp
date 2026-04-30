#include "pantallacargasucursales.h"
#include "ui_pantallacargasucursales.h"

PantallaCargaSucursales::PantallaCargaSucursales(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaCargaSucursales)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_StyledBackground, true);

    //Se aplica el estilo al contenedor padre
    this->setStyleSheet("QWidget#PantallaCargaSucursales { "
                        "border-image: url(:/assets/fondo/GrafosBackground.png) 0 0 0 0 stretch stretch; "
                        "} ");
}

/*Destructor*/
PantallaCargaSucursales::~PantallaCargaSucursales()
{
    delete ui;
}
