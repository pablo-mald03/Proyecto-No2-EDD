#include "pantallacargasucursales.h"
#include "ui_pantallacargasucursales.h"

PantallaCargaSucursales::PantallaCargaSucursales(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaCargaSucursales)
{
    ui->setupUi(this);
}

PantallaCargaSucursales::~PantallaCargaSucursales()
{
    delete ui;
}
