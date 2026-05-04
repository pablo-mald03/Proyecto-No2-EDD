#include "pantallacompararbusquedas.h"
#include "ui_pantallacompararbusquedas.h"

PantallaCompararBusquedas::PantallaCompararBusquedas(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaCompararBusquedas)
{
    ui->setupUi(this);
}

PantallaCompararBusquedas::~PantallaCompararBusquedas()
{
    delete ui;
}
