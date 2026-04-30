#include "pantallamodificarsucursal.h"
#include "ui_pantallamodificarsucursal.h"

PantallaModificarSucursal::PantallaModificarSucursal(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaModificarSucursal)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_StyledBackground, true);

    //Se aplica el estilo al contenedor padre
    this->setStyleSheet("QWidget#PantallaModificarSucursal { "
                        "border-image: url(:/assets/fondo/GrafosBackground.png) 0 0 0 0 stretch stretch; "
                        "} ");
}

/*Destructor*/
PantallaModificarSucursal::~PantallaModificarSucursal()
{
    delete ui;
}
