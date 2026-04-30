#include "pantallaeliminarsucursal.h"
#include "ui_pantallaeliminarsucursal.h"

PantallaEliminarSucursal::PantallaEliminarSucursal(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaEliminarSucursal)
{
    ui->setupUi(this);
}

PantallaEliminarSucursal::~PantallaEliminarSucursal()
{
    delete ui;
}
