#include "pantallaverestadoenvios.h"
#include "ui_pantallaverestadoenvios.h"

PantallaVerEstadoEnvios::PantallaVerEstadoEnvios(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaVerEstadoEnvios)
{
    ui->setupUi(this);
}

PantallaVerEstadoEnvios::~PantallaVerEstadoEnvios()
{
    delete ui;
}
