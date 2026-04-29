#include "pantallacompararbusqueda.h"
#include "ui_pantallacompararbusqueda.h"

PantallaCompararBusqueda::PantallaCompararBusqueda(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaCompararBusqueda)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_StyledBackground, true);

    //Se aplica el estilo al contenedor padre
    this->setStyleSheet("QWidget#PantallaCompararBusqueda { "
                        "border-image: url(:/assets/fondo/fondooverlay.png) 0 0 0 0 stretch stretch; "
                        "} ");
}

PantallaCompararBusqueda::~PantallaCompararBusqueda()
{
    delete ui;
}
