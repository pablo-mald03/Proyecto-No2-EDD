#include "pantallabuscarcodigo.h"
#include "ui_pantallabuscarcodigo.h"

PantallaBuscarCodigo::PantallaBuscarCodigo(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaBuscarCodigo)
{
    ui->setupUi(this);
}

PantallaBuscarCodigo::~PantallaBuscarCodigo()
{
    delete ui;
}
