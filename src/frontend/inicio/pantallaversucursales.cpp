#include "pantallaversucursales.h"
#include "ui_pantallaversucursales.h"

PantallaVerSucursales::PantallaVerSucursales(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaVerSucursales)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_StyledBackground, true);

    //Se aplica el estilo al contenedor padre
    this->setStyleSheet("QWidget#PantallaVerSucursales { "
                        "border-image: url(:/assets/fondo/GrafosBackground.png) 0 0 0 0 stretch stretch; "
                        "} ");
}

/*Destructor*/
PantallaVerSucursales::~PantallaVerSucursales()
{
    delete ui;
}
