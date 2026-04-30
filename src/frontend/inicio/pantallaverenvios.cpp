#include "pantallaverenvios.h"
#include "ui_pantallaverenvios.h"

PantallaVerEnvios::PantallaVerEnvios(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaVerEnvios)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_StyledBackground, true);

    //Se aplica el estilo al contenedor padre
    this->setStyleSheet("QWidget#PantallaVerEnvios { "
                        "border-image: url(:/assets/fondo/GrafosBackground.png) 0 0 0 0 stretch stretch; "
                        "} ");
}

/*Destructor*/
PantallaVerEnvios::~PantallaVerEnvios()
{
    delete ui;
}
