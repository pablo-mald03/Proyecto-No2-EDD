#include "pantallacolapreparacion.h"
#include "ui_pantallacolapreparacion.h"

PantallaColaPreparacion::PantallaColaPreparacion(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaColaPreparacion)
{
    ui->setupUi(this);
}

PantallaColaPreparacion::~PantallaColaPreparacion()
{
    delete ui;
}
