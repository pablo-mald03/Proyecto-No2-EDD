#include "pantallagestion.h"
#include "ui_pantallagestion.h"

PantallaGestion::PantallaGestion(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaGestion)
{
    ui->setupUi(this);
}

PantallaGestion::~PantallaGestion()
{
    delete ui;
}
