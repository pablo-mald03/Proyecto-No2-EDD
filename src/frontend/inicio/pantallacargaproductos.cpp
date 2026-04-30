#include "pantallacargaproductos.h"
#include "ui_pantallacargaproductos.h"

PantallaCargaProductos::PantallaCargaProductos(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaCargaProductos)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_StyledBackground, true);

    //Se aplica el estilo al contenedor padre
    this->setStyleSheet("QWidget#PantallaCargaProductos { "
                        "border-image: url(:/assets/fondo/GrafosBackground.png) 0 0 0 0 stretch stretch; "
                        "} ");
}

/*Destructor*/
PantallaCargaProductos::~PantallaCargaProductos()
{
    delete ui;
}
