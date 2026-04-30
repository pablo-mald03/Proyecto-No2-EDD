#include "pantallaagregarsucursal.h"
#include "ui_pantallaagregarsucursal.h"

PantallaAgregarSucursal::PantallaAgregarSucursal(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaAgregarSucursal)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_StyledBackground, true);

    //Se aplica el estilo al contenedor padre
    this->setStyleSheet("QWidget#PantallaAgregarSucursal { "
                        "border-image: url(:/assets/fondo/GrafosBackground.png) 0 0 0 0 stretch stretch; "
                        "} ");
}

/*Destructor*/
PantallaAgregarSucursal::~PantallaAgregarSucursal()
{
    delete ui;
}
