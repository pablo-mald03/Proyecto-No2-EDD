#include "pantallagestion.h"
#include "ui_pantallagestion.h"

PantallaGestion::PantallaGestion(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaGestion)
{
    ui->setupUi(this);

    this->pantallaSucursal = new PantallaSucursal(this);

    this->ui->stackedWidget->addWidget(this->pantallaSucursal);

    connect(this->pantallaSucursal, &PantallaSucursal::cambiarTitulo, this, &PantallaGestion::cambiarLabel);
}

/*Metodo que permite tomar la referencia que traen de la sucursal y setearla a los controladores*/
void PantallaGestion::setSucursal(GestorEstructuras * _estructuras, std::string _idSucursal){


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

    this->ui->stackedWidget->setCurrentWidget(this->pantallaSucursal);
    /*pendientes las acciones*/
}

/*Metodo que permite mostrar la ventana de productos de la UI*/
void PantallaGestion::mostrarProductos(){

    if (!this->pantallaMain) {

        this->pantallaMain = new PantallaMain(this);

        this->ui->stackedWidget->addWidget(this->pantallaMain);

        //Se conectan las signals para poder interactuar con la pantalla
        connect(this->pantallaMain, &PantallaMain::cambiarTitulo, this, &PantallaGestion::cambiarLabel);

        /*connect(this->controladorCrud, &Controlador::logInsertArbolB,this->pantallaAgregar, &PantallaAgregar::appendBLog);

        connect(this->controladorCrud, &Controlador::logInsertArbolBMas,this->pantallaAgregar, &PantallaAgregar::appendBMasLog);

        connect(this->controladorCrud, &Controlador::logInsertListaOrdenada,this->pantallaAgregar, &PantallaAgregar::appendListOrdenadaLog);

        connect(this->controladorCrud, &Controlador::logInsertListaNoOrdenada,this->pantallaAgregar, &PantallaAgregar::appendListNoOrdenadaLog);

        connect(this->controladorCrud, &Controlador::tiempoProcesoInsert, this->pantallaAgregar, &PantallaAgregar::mostrarTiempo);

        connect(this->pantallaAgregar, &PantallaAgregar::insertarProducto, this->controladorCrud, &Controlador::insercionProducto);

        connect(this->pantallaAgregar, &PantallaAgregar::verArboles, this, &PantallaMain::mostrarVerArboles);

        connect(this->controladorCrud, &Controlador::tiempoProcesoInsert, this->pantallaAgregar, &PantallaAgregar::mostrarTiempo);

        connect(this, &PantallaMain::limpiarAgregar, this->pantallaAgregar, &PantallaAgregar::limpiarPantalla);*/
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

