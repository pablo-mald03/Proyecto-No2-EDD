#include "pantallalistaenlazada.h"
#include "ui_pantallalistaenlazada.h"

PantallaListaEnlazada::PantallaListaEnlazada(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaListaEnlazada)
{
    ui->setupUi(this);
}

PantallaListaEnlazada::~PantallaListaEnlazada()
{
    delete ui;
}
