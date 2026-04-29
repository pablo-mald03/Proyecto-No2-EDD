#include "eliminarproducto.h"
#include "ui_pantallaeliminarproducto.h"

EliminarProducto::EliminarProducto(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::EliminarProducto)
{
    ui->setupUi(this);
}

EliminarProducto::~EliminarProducto()
{
    delete ui;
}
