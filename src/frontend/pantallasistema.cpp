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


    /*Connects que permiten interactuar con el contenedor padre de la main window*/
    connect( this->controladorGeneral, &ControladorNegocio::abrirSucursal, this, &PantallaSistema::cargarSucursal);

    /*Connects que permiten interactuar con la pantalla de sucursales*/
    connect( this->pantallaCargadoSucursales, &PantallaCargaSucursales::csvSucursalesCargado,this->controladorGeneral,&ControladorNegocio::procesarCsvSucursal);
    connect( this->pantallaCargadoSucursales, &PantallaCargaSucursales::csvConexionesCargado,this->controladorGeneral, &ControladorNegocio::procesarCsvConexion);

    connect( this->controladorGeneral,&ControladorNegocio::logGrafoSucursales, this->pantallaCargadoSucursales, &PantallaCargaSucursales::appendGrafoLog);
    connect( this->controladorGeneral, &ControladorNegocio::logCargaCsvSucursales, this->pantallaCargadoSucursales, &PantallaCargaSucursales::appendLogCarga);
    connect( this->controladorGeneral, &ControladorNegocio::tiempoProcesoSucursales, this->pantallaCargadoSucursales, &PantallaCargaSucursales::mostrarTiempo);

    connect(this->pantallaCargadoSucursales, &PantallaCargaSucursales::solicitarLogErrores, this->controladorGeneral, &ControladorNegocio::prepararLogParaDescargaSucursales);

    connect(this->controladorGeneral, &ControladorNegocio::evaluarErroresSucursalesLog, this->pantallaCargadoSucursales, &PantallaCargaSucursales::evaluarErrores);
    connect(this->controladorGeneral, &ControladorNegocio::logDescargarSucursales, this->pantallaCargadoSucursales, &PantallaCargaSucursales::logListoParaDescargar);

}


/*Metodo que permite comunicarle al padre que abra otra ventana con la sucursal seleccionada*/
void PantallaSistema::cargarSucursal(Sucursal* _sucursal, Grafo* _redGrafo, GestorEnvios* _gestor){

    emit solicitarApertura(_sucursal,_redGrafo,_gestor);
}

/*------- Apartado de slots que sirven para poder enviar datos al controlador de la pantalla de carga de sucursales----------*/

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

    if (!this->pantallaAgregadoSucursal) {

        this->pantallaAgregadoSucursal = new PantallaAgregarSucursal(this);

        this->ui->stackedWidget->addWidget(this->pantallaAgregadoSucursal);

        //Se conectan las signals para poder interactuar con la pantalla
        connect(this->controladorGeneral, &ControladorNegocio::logInsertGrafo,this->pantallaAgregadoSucursal, &PantallaAgregarSucursal::appendGrafoLog);

        connect(this->pantallaAgregadoSucursal, &PantallaAgregarSucursal::insertarSucursal, this->controladorGeneral, &ControladorNegocio::insercionSucursal);

        connect(this->controladorGeneral, &ControladorNegocio::tiempoProcesoInsercionGrafo, this->pantallaAgregadoSucursal, &PantallaAgregarSucursal::mostrarTiempo);

        connect(this->pantallaAgregadoSucursal, &PantallaAgregarSucursal::verSucursales, this, &PantallaSistema::mostrarVistaSucursales);

        connect(this->pantallaAgregadoSucursal, &PantallaAgregarSucursal::asociarConexion, this->controladorGeneral, &ControladorNegocio::conexionSucursal);

        connect(this->controladorGeneral, &ControladorNegocio::mensajeConfirmacionConexion, this->pantallaAgregadoSucursal, &PantallaAgregarSucursal::confirmarAsociacion);

        connect(this->controladorGeneral, &ControladorNegocio::actualizacionCombos, this->pantallaAgregadoSucursal, &PantallaAgregarSucursal::actualizarCombos);
    }
    this->pantallaAgregadoSucursal->limpiarPantalla();
    this->ui->stackedWidget->setCurrentWidget(this->pantallaAgregadoSucursal);
    this->pantallaAgregadoSucursal->inicializarCombos(this->controladorGeneral->obtenerGrafo()->getNodos());
    this->ui->labelTasks->setText("Agregar Sucursal");
}

/*Signal que permite viajar a ver las sucursales*/
void PantallaSistema::mostrarVistaSucursales(){
    this->mostrarVerSucursales();
}


/*Metodo que permite mostrar la pantalla de modificar sucursales*/
void PantallaSistema::mostrarModificarSucursal(){

    if (!this->pantallaModificadoSucursal) {

        this->pantallaModificadoSucursal = new PantallaModificarSucursal(this);

        this->ui->stackedWidget->addWidget(this->pantallaModificadoSucursal);

        //Se conectan las signals para poder interactuar con la pantalla
        connect(this->controladorGeneral, &ControladorNegocio::logModificacionGrafo,this->pantallaModificadoSucursal, &PantallaModificarSucursal::appendGrafoLog);

        connect(this->pantallaModificadoSucursal, &PantallaModificarSucursal::modificarSucursal, this->controladorGeneral, &ControladorNegocio::modificacionSucursal);

        connect(this->controladorGeneral, &ControladorNegocio::tiempoProcesoModificacionGrafo, this->pantallaModificadoSucursal, &PantallaModificarSucursal::mostrarTiempo);

        connect(this->pantallaModificadoSucursal, &PantallaModificarSucursal::verSucursales, this, &PantallaSistema::mostrarVistaSucursales);

        connect(this->controladorGeneral, &ControladorNegocio::enviarInformacion, this->pantallaModificadoSucursal, &PantallaModificarSucursal::recibirSucursal);

        connect(this->pantallaModificadoSucursal, &PantallaModificarSucursal::solicitarSucursal, this->controladorGeneral, &ControladorNegocio::buscarSucursal);

        connect(this->controladorGeneral, &ControladorNegocio::mensajeErrorModificar, this->pantallaModificadoSucursal, &PantallaModificarSucursal::recibirMensajeError);

    }

    this->pantallaModificadoSucursal->limpiarPantalla();
    this->ui->stackedWidget->setCurrentWidget(this->pantallaModificadoSucursal);

    this->pantallaModificadoSucursal->inicializarCombo(this->controladorGeneral->obtenerGrafo()->getNodos());
    this->ui->labelTasks->setText("Modificar Sucursal");
}

/*Metodo que permite mostrar la pantalla de eliminar sucursales*/
void PantallaSistema::mostrarEliminarSucursal(){

    if (!this->pantallaEliminadoSucursal) {

        this->pantallaEliminadoSucursal = new PantallaEliminarSucursal(this);

        this->ui->stackedWidget->addWidget(this->pantallaEliminadoSucursal);

        //Se conectan las signals para poder interactuar con la pantalla
        connect(this->controladorGeneral, &ControladorNegocio::logEliminacionGrafo,this->pantallaEliminadoSucursal, &PantallaEliminarSucursal::appendGrafoLog);

        connect(this->pantallaEliminadoSucursal, &PantallaEliminarSucursal::eliminarSucursal, this->controladorGeneral, &ControladorNegocio::eliminacionSucursal);

        connect(this->controladorGeneral, &ControladorNegocio::tiempoProcesoEliminacionGrafo, this->pantallaEliminadoSucursal, &PantallaEliminarSucursal::mostrarTiempo);

        connect(this->pantallaEliminadoSucursal, &PantallaEliminarSucursal::verSucursales, this, &PantallaSistema::mostrarVistaSucursales);
    }

    this->pantallaEliminadoSucursal->limpiarPantalla();
    this->ui->stackedWidget->setCurrentWidget(this->pantallaEliminadoSucursal);

    this->ui->labelTasks->setText("Eliminar Sucursal");
}

/*Metodo que permite mostrar la pantalla de ver sucursales*/
void PantallaSistema::mostrarVerSucursales(){

    if (!this->pantallaVistaSucursales) {

        this->pantallaVistaSucursales = new PantallaVerSucursales(this);

        this->ui->stackedWidget->addWidget(this->pantallaVistaSucursales);

        connect(this->pantallaVistaSucursales, &PantallaVerSucursales::navegarASucursal, this->controladorGeneral, &ControladorNegocio::cargarSucursal);

        connect(this->pantallaVistaSucursales, &PantallaVerSucursales::solicitarGraphvizGrafo, this->controladorGeneral, &ControladorNegocio::generarGraphvizGrafo);

        connect(this->controladorGeneral, &ControladorNegocio::enviarGraphvizGrafo, this->pantallaVistaSucursales, &PantallaVerSucursales::generarGraphviz);
    }

    this->ui->stackedWidget->setCurrentWidget(this->pantallaVistaSucursales);
    this->ui->labelTasks->setText("Ver Sucursales");
    this->pantallaVistaSucursales->inicializarRed(this->controladorGeneral->obtenerGrafo());
}

/*Metodo que permite mostrar la pantalla de ver envios*/
void PantallaSistema::mostrarVerEnvios(){

    if (!this->pantallaEnvios) {

        this->pantallaEnvios = new PantallaVerEnvios(this);

        this->ui->stackedWidget->addWidget(this->pantallaEnvios);

        connect(this->pantallaEnvios, &PantallaVerEnvios::navegarASucursal, this->controladorGeneral, &ControladorNegocio::cargarSucursal);

        connect(this->pantallaEnvios, &PantallaVerEnvios::verificarEnvios, this->controladorGeneral, &ControladorNegocio::buscarEnvios);

        connect(this->controladorGeneral, &ControladorNegocio::actualizarEnvio, this->pantallaEnvios, &PantallaVerEnvios::actualizarTrayectoria);
    }

    this->ui->stackedWidget->setCurrentWidget(this->pantallaEnvios);
    this->pantallaEnvios->inicializarDatos();
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

