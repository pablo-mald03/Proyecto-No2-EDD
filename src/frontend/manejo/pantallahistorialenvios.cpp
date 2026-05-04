#include "pantallahistorialenvios.h"
#include "ui_pantallahistorialenvios.h"

PantallaHistorialEnvios::PantallaHistorialEnvios(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaHistorialEnvios)
{
    ui->setupUi(this);
}

PantallaHistorialEnvios::~PantallaHistorialEnvios()
{
    delete ui;
}
