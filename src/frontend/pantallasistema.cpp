#include "pantallasistema.h"
#include "ui_pantallasistema.h"

/*Pantalla que aparece para mostrar el funcionamiento principal del sistema*/
PantallaSistema::PantallaSistema(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaSistema)
{
    ui->setupUi(this);

    this->pantallaCargadoSucursales = new PantallaCargaSucursales();
    this->ui->stackedWidget->addWidget(this->pantallaCargadoSucursales);


}

/*Metodos para poder comunicarse desde fuera con la pantalla*/
void PantallaSistema::setPantallanInicio(){
    this->mostrarCargaSucursales();
}

/*Metodos que permiten irse comunicando con la UI*/

/*Metodo que permite mostrar la pantalla de carga de csv de sucursales*/
void PantallaSistema::mostrarCargaSucursales(){

    this->ui->stackedWidget->setCurrentWidget(this->pantallaCargadoSucursales);
    this->ui->labelTasks->setText("Cargar Sucursales");
}

/*Metodo que permite mostrar la pantalla de carga de csv de envios*/
void PantallaSistema::mostrarCargaEnvios(){

    this->ui->labelTasks->setText("Cargar Envios");
}

/*Metodo que permite mostrar la pantalla de carga de csv de productos*/
void PantallaSistema::mostrarCargaProductos(){

    this->ui->labelTasks->setText("Cargar Productos");
}

/*Metodo que permite mostrar la pantalla de agregar sucursales*/
void PantallaSistema::mostrarAgregarSucursal(){

    this->ui->labelTasks->setText("Agregar Sucursal");
}

/*Metodo que permite mostrar la pantalla de modificar sucursales*/
void PantallaSistema::mostrarModificarSucursal(){

    this->ui->labelTasks->setText("Modificar Sucursal");
}

/*Metodo que permite mostrar la pantalla de eliminar sucursales*/
void PantallaSistema::mostrarEliminarSucursal(){

    this->ui->labelTasks->setText("Eliminar Sucursal");
}

/*Metodo que permite mostrar la pantalla de ver sucursales*/
void PantallaSistema::mostrarVerSucursales(){

    this->ui->labelTasks->setText("Ver Sucursales");
}

/*Metodo que permite mostrar la pantalla de ver envios*/
void PantallaSistema::mostrarVerEnvios(){

    this->ui->labelTasks->setText("Ver Envios");
}


/*Destructor*/
PantallaSistema::~PantallaSistema()
{
    delete ui;
}

/*Metodo para poder cargar el csv de las sucursales*/
void PantallaSistema::on_btnCargaSucursales_clicked()
{
    this->mostrarCargaSucursales();
}


void PantallaSistema::on_btnCargaEnvios_clicked()
{

}


void PantallaSistema::on_btnCargarProductos_clicked()
{

}


void PantallaSistema::on_btnAgregarSucursal_clicked()
{

}


void PantallaSistema::on_btnModificarSucursal_clicked()
{

}


void PantallaSistema::on_btnEliminarSucursal_clicked()
{

}


void PantallaSistema::on_btnVerSucursales_clicked()
{

}


void PantallaSistema::on_btnVerEnvios_clicked()
{

}

