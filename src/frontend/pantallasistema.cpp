#include "pantallasistema.h"
#include "ui_pantallasistema.h"

/*Pantalla que aparece para mostrar el funcionamiento principal del sistema*/
PantallaSistema::PantallaSistema(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaSistema)
{
    ui->setupUi(this);

    this->controladorGeneral = new ControladorNegocio();

    this->pantallaCargadoSucursales = new PantallaCargaSucursales();
    this->ui->stackedWidget->addWidget(this->pantallaCargadoSucursales);


    connect( this->pantallaCargadoSucursales, &PantallaCargaSucursales::csvSucursalesCargado,this->controladorGeneral,&ControladorNegocio::procesarCsvSucursal);
    connect( this->pantallaCargadoSucursales, &PantallaCargaSucursales::csvConexionesCargado,this->controladorGeneral, &ControladorNegocio::procesarCsvConexion);

    connect( this->controladorGeneral,&ControladorNegocio::logGrafoSucursales, this->pantallaCargadoSucursales, &PantallaCargaSucursales::appendGrafoLog);
    connect( this->controladorGeneral, &ControladorNegocio::logCargaCsvSucursales, this->pantallaCargadoSucursales, &PantallaCargaSucursales::appendLogCarga);
    connect( this->controladorGeneral, &ControladorNegocio::tiempoProcesoSucursales, this->pantallaCargadoSucursales, &PantallaCargaSucursales::mostrarTiempo);

    connect(this->pantallaCargadoSucursales, &PantallaCargaSucursales::solicitarLogErrores, this->controladorGeneral, &ControladorNegocio::prepararLogParaDescargaSucursales);

    connect(this->controladorGeneral, &ControladorNegocio::evaluarErroresSucursalesLog, this->pantallaCargadoSucursales, &PantallaCargaSucursales::evaluarErrores);
    connect(this->controladorGeneral, &ControladorNegocio::logDescargarSucursales, this->pantallaCargadoSucursales, &PantallaCargaSucursales::logListoParaDescargar);

}


/*-------Fin del Apartado de slots que sirven para poder enviar datos al controlador de la pantalla de carga de sucursales----------*/

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

    if (!this->pantallaCargadoEnvios) {

        this->pantallaCargadoEnvios = new PantallaCargaEnvios(this);

        this->ui->stackedWidget->addWidget(this->pantallaCargadoEnvios);

        //Se conectan las signals para poder interactuar con la pantalla
        connect( this->pantallaCargadoEnvios, &PantallaCargaEnvios::csvEnviosCargado,this->controladorGeneral,&ControladorNegocio::procesarCsvEnvios);

        connect( this->controladorGeneral,&ControladorNegocio::logGrafoEnvios, this->pantallaCargadoEnvios, &PantallaCargaEnvios::appendGrafoLog);
        connect( this->controladorGeneral, &ControladorNegocio::logCargaCsvEnvios, this->pantallaCargadoEnvios, &PantallaCargaEnvios::appendLogCarga);
        connect( this->controladorGeneral, &ControladorNegocio::tiempoProcesoEnvios, this->pantallaCargadoEnvios, &PantallaCargaEnvios::mostrarTiempo);

        connect(this->pantallaCargadoEnvios, &PantallaCargaEnvios::solicitarLogErrores, this->controladorGeneral, &ControladorNegocio::prepararLogParaDescargaEnvios);

        connect(this->controladorGeneral, &ControladorNegocio::evaluarErroresEnviosLog, this->pantallaCargadoEnvios, &PantallaCargaEnvios::evaluarErrores);
        connect(this->controladorGeneral, &ControladorNegocio::logDescargarEnvios, this->pantallaCargadoEnvios, &PantallaCargaEnvios::logListoParaDescargar);

    }

    this->ui->stackedWidget->setCurrentWidget(this->pantallaCargadoEnvios);
    this->ui->labelTasks->setText("Cargar Envios");
}

/*Metodo que permite mostrar la pantalla de carga de csv de productos*/
void PantallaSistema::mostrarCargaProductos(){

    if (!this->pantallaCargadoProductos) {

        this->pantallaCargadoProductos = new PantallaCargaProductos(this);

        this->ui->stackedWidget->addWidget(this->pantallaCargadoProductos);

        //Se conectan las signals para poder interactuar con la pantalla
        connect(this->pantallaCargadoProductos, &PantallaCargaProductos::csvProductosCargado, this->controladorGeneral, &ControladorNegocio::procesarCsvProductos);
        connect(this->controladorGeneral, &ControladorNegocio::logArbolAvl,this->pantallaCargadoProductos, &PantallaCargaProductos::appendAvlLog);
        connect(this->controladorGeneral, &ControladorNegocio::logArbolB,this->pantallaCargadoProductos, &PantallaCargaProductos::appendBLog);
        connect(this->controladorGeneral, &ControladorNegocio::logArbolBMas,this->pantallaCargadoProductos, &PantallaCargaProductos::appendBMasLog);
        connect(this->controladorGeneral, &ControladorNegocio::logLista,this->pantallaCargadoProductos, &PantallaCargaProductos::appendListLog);
        connect(this->controladorGeneral, &ControladorNegocio::logHash,this->pantallaCargadoProductos, &PantallaCargaProductos::appendHashLog);
        connect(this->controladorGeneral, &ControladorNegocio::logCargaCsvProductos,this->pantallaCargadoProductos, &PantallaCargaProductos::appendLogCarga);

        connect(this->controladorGeneral, &ControladorNegocio::tiempoProcesoProductos, this->pantallaCargadoProductos, &PantallaCargaProductos::mostrarTiempo);

        connect(this->pantallaCargadoProductos, &PantallaCargaProductos::solicitarLogErrores, this->controladorGeneral, &ControladorNegocio::prepararLogParaDescargaProductos);

        connect(this->controladorGeneral, &ControladorNegocio::evaluarErroresProductosLog, this->pantallaCargadoProductos, &PantallaCargaProductos::evaluarErrores);
        connect(this->controladorGeneral, &ControladorNegocio::logDescargarProductos, this->pantallaCargadoProductos, &PantallaCargaProductos::logListoParaDescargar);

    }

    this->ui->stackedWidget->setCurrentWidget(this->pantallaCargadoProductos);
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

/*Metodo que permite mostrar la carga de envios*/
void PantallaSistema::on_btnCargaEnvios_clicked()
{
    this->mostrarCargaEnvios();
}

/*Metodo que permite mostrar la carga de productos asignados a una sucursal*/
void PantallaSistema::on_btnCargarProductos_clicked()
{
    this->mostrarCargaProductos();
}

/*Metodo que permite mostrar la creacion de nuevas sucursales*/
void PantallaSistema::on_btnAgregarSucursal_clicked()
{
    this->mostrarAgregarSucursal();
}

/*Metodo que permite modificar una sucursal*/
void PantallaSistema::on_btnModificarSucursal_clicked()
{
    this->mostrarModificarSucursal();

}

/*Metodo que permite eliminar una sucursal*/
void PantallaSistema::on_btnEliminarSucursal_clicked()
{
    this->mostrarEliminarSucursal();
}

/*Metodo que permite ver las sucursales*/
void PantallaSistema::on_btnVerSucursales_clicked()
{
    this->mostrarVerSucursales();

}

/*Metodo que permite ver el estado de envios por sucursales*/
void PantallaSistema::on_btnVerEnvios_clicked()
{
    this->mostrarVerEnvios();
}

