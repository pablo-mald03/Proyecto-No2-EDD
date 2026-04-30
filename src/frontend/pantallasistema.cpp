#include "pantallasistema.h"
#include "ui_pantallasistema.h"

/*Pantalla que aparece para mostrar el funcionamiento principal del sistema*/
PantallaSistema::PantallaSistema(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaSistema)
{
    ui->setupUi(this);
}

/*Metodos para poder comunicarse desde fuera con la pantalla*/
void PantallaSistema::setPantallanInicio(){

}

/*Destructor*/
PantallaSistema::~PantallaSistema()
{
    delete ui;
}
