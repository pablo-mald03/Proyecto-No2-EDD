#include "pantallamodificarsucursal.h"
#include "ui_pantallamodificarsucursal.h"

PantallaModificarSucursal::PantallaModificarSucursal(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaModificarSucursal)
{
    ui->setupUi(this);
}

PantallaModificarSucursal::~PantallaModificarSucursal()
{
    delete ui;
}
