#include "pantallaenviarproductos.h"
#include "ui_pantallaenviarproductos.h"

PantallaEnviarProductos::PantallaEnviarProductos(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaEnviarProductos)
{
    ui->setupUi(this);
}

PantallaEnviarProductos::~PantallaEnviarProductos()
{
    delete ui;
}
