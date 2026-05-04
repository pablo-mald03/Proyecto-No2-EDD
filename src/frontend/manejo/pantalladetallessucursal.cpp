#include "pantalladetallessucursal.h"
#include "ui_pantalladetallessucursal.h"

PantallaDetallesSucursal::PantallaDetallesSucursal(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaDetallesSucursal)
{
    ui->setupUi(this);
}

PantallaDetallesSucursal::~PantallaDetallesSucursal()
{
    delete ui;
}
