#include "pantallaeliminarsucursal.h"
#include "ui_pantallaeliminarsucursal.h"

PantallaEliminarSucursal::PantallaEliminarSucursal(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaEliminarSucursal)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_StyledBackground, true);

    //Se aplica el estilo al contenedor padre
    this->setStyleSheet("QWidget#PantallaEliminarSucursal { "
                        "border-image: url(:/assets/fondo/GrafosBackground.png) 0 0 0 0 stretch stretch; "
                        "} ");
}

/*Destructor*/
PantallaEliminarSucursal::~PantallaEliminarSucursal()
{
    delete ui;
}
