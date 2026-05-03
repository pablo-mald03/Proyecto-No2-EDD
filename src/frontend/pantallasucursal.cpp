#include "pantallasucursal.h"
#include "ui_pantallasucursal.h"

PantallaSucursal::PantallaSucursal(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaSucursal)
{
    ui->setupUi(this);

    this->controlador = new ControladorSucursal();

}

/*Metodo que permite agregar los recursos que se utilizaran en el backend*/
void PantallaSucursal::setRecursos(Sucursal * _sucursal, Grafo * _redGrafo){
    this->controlador->setRecursosActuales(_sucursal,_redGrafo);
}

/*Destructor*/
PantallaSucursal::~PantallaSucursal()
{
    delete ui;
}
