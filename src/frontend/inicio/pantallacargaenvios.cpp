#include "pantallacargaenvios.h"
#include "ui_pantallacargaenvios.h"

PantallaCargaEnvios::PantallaCargaEnvios(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaCargaEnvios)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_StyledBackground, true);

    //Se aplica el estilo al contenedor padre
    this->setStyleSheet("QWidget#PantallaCargaEnvios { "
                        "border-image: url(:/assets/fondo/GrafosBackground.png) 0 0 0 0 stretch stretch; "
                        "} ");
}

/*Destructor*/
PantallaCargaEnvios::~PantallaCargaEnvios()
{
    delete ui;
}
