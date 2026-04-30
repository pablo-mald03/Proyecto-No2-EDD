#include "pantallacargaenvios.h"
#include "ui_pantallacargaenvios.h"

PantallaCargaEnvios::PantallaCargaEnvios(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaCargaEnvios)
{
    ui->setupUi(this);
}

PantallaCargaEnvios::~PantallaCargaEnvios()
{
    delete ui;
}
