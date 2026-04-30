#include "pantallacargaproductos.h"
#include "ui_pantallacargaproductos.h"

PantallaCargaProductos::PantallaCargaProductos(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaCargaProductos)
{
    ui->setupUi(this);
}

PantallaCargaProductos::~PantallaCargaProductos()
{
    delete ui;
}
