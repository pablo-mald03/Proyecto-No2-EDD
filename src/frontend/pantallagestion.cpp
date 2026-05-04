#include "pantallagestion.h"
#include "ui_pantallagestion.h"

PantallaGestion::PantallaGestion(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaGestion)
{
    ui->setupUi(this);

    this->setStyleSheet("PantallaGestion { background-color: #1a1a1a; } ");


    this->pantallaMain = new PantallaMain(this);

    this->ui->stackedWidget->addWidget(this->pantallaMain);

    connect(this->pantallaMain, &PantallaMain::cambiarTitulo, this, &PantallaGestion::cambiarLabel);

}

/*Metodo que permite tomar la referencia que traen de la sucursal y setearla a los controladores*/
void PantallaGestion::setSucursal(Sucursal* _sucursal, Grafo* _redGrafo, GestorEnvios* _gestor) {

    this->sucursal = _sucursal;
    this->redGrafo = _redGrafo;
    this->gestorEnvios = _gestor;

    this->ui->labelAdmin->setText(QString::fromStdString(_sucursal->getNombre()));
    this->pantallaMain->setGestorSucursal(this->sucursal->getAlmacen());
}

/*Metodo que permite mostar la primera pantalla de inicio*/
void PantallaGestion::setPantallaInicio(){
    this->mostrarSucursal();
}

/*Metodo que permite cambiar el label en la pantalla*/
void PantallaGestion::cambiarLabel(QString _titulo){
    this->ui->labelTasks->setText(_titulo);
}
/*Region de metodos para poder mostrar las diferentes vistas*/
void PantallaGestion::mostrarSucursal(){

    if (!this->pantallaSucursal) {

        this->pantallaSucursal = new PantallaSucursal(this);
        this->ui->stackedWidget->addWidget(this->pantallaSucursal);

        this->pantallaSucursal->setRecursos(this->sucursal, this->redGrafo,
                                            this->gestorEnvios);

        connect(this->pantallaSucursal, &PantallaSucursal::cambiarTitulo, this, &PantallaGestion::cambiarLabel);
    }


    this->ui->stackedWidget->setCurrentWidget(this->pantallaSucursal);
    this->pantallaSucursal->setRecursos(this->sucursal,this->redGrafo,this->gestorEnvios);
    this->pantallaSucursal->mostrarEstadoEnvios();

}

/*Metodo que permite mostrar la ventana de productos de la UI*/
void PantallaGestion::mostrarProductos(){

    if(!this->pantallaMain){
        return;
    }

    this->ui->stackedWidget->setCurrentWidget(this->pantallaMain);
    this->pantallaMain->mostrarInicio();
}

PantallaGestion::~PantallaGestion()
{
    delete ui;
}

/*Boton que permite regresar al menu principal*/
void PantallaGestion::on_btnHome_clicked()
{
    emit solicitarRegreso();
}

/*Metodo que permite viajar a la sucursal*/
void PantallaGestion::on_btnTienda_clicked()
{
    this->mostrarSucursal();
}

/*Metodo que permite viajar a los productos de la sucursal*/
void PantallaGestion::on_btnProductos_clicked()
{
    this->mostrarProductos();
}

