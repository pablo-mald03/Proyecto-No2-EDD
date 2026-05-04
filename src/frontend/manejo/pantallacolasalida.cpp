#include "pantallacolasalida.h"
#include "ui_pantallacolasalida.h"

PantallaColaSalida::PantallaColaSalida(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaColaSalida)
{
    ui->setupUi(this);
}

PantallaColaSalida::~PantallaColaSalida()
{
    delete ui;
}
