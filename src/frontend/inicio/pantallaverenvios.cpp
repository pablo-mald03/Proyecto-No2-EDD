#include "pantallaverenvios.h"
#include "ui_pantallaverenvios.h"

PantallaVerEnvios::PantallaVerEnvios(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaVerEnvios)
{
    ui->setupUi(this);
}

PantallaVerEnvios::~PantallaVerEnvios()
{
    delete ui;
}
