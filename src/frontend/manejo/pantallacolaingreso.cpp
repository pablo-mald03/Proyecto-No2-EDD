#include "pantallacolaingreso.h"
#include "ui_pantallacolaingreso.h"

PantallaColaIngreso::PantallaColaIngreso(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaColaIngreso)
{
    ui->setupUi(this);
}

PantallaColaIngreso::~PantallaColaIngreso()
{
    delete ui;
}
