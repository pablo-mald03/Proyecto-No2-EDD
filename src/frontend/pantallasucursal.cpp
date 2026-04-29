#include "pantallasucursal.h"
#include "ui_pantallasucursal.h"

PantallaSucursal::PantallaSucursal(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaSucursal)
{
    ui->setupUi(this);
}

PantallaSucursal::~PantallaSucursal()
{
    delete ui;
}
