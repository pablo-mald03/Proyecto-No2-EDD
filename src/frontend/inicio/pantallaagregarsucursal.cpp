#include "pantallaagregarsucursal.h"
#include "ui_pantallaagregarsucursal.h"

PantallaAgregarSucursal::PantallaAgregarSucursal(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaAgregarSucursal)
{
    ui->setupUi(this);
}

PantallaAgregarSucursal::~PantallaAgregarSucursal()
{
    delete ui;
}
