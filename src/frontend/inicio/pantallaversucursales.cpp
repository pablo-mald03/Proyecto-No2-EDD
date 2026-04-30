#include "pantallaversucursales.h"
#include "ui_pantallaversucursales.h"

PantallaVerSucursales::PantallaVerSucursales(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaVerSucursales)
{
    ui->setupUi(this);
}

PantallaVerSucursales::~PantallaVerSucursales()
{
    delete ui;
}
