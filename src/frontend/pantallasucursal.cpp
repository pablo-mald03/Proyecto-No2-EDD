#include "pantallasucursal.h"
#include "ui_pantallasucursal.h"

PantallaSucursal::PantallaSucursal(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaSucursal)
{
    ui->setupUi(this);

    this->controladorGestion = new ControladorSucursal();

    this->pantallaEstadoEnvios = new PantallaVerEstadoEnvios(this);

    this->ui->stackedWidget->addWidget(this->pantallaEstadoEnvios);

    /*Pendientes connects*/

}

/*Metodo que permite agregar los recursos que se utilizaran en el backend*/
void PantallaSucursal::setRecursos(Sucursal* _sucursal, Grafo* _redGrafo, GestorEnvios* _gestor){
    this->controladorGestion->setRecursosActuales(_sucursal,_redGrafo,_gestor);
}

/*Destructor*/
PantallaSucursal::~PantallaSucursal()
{
    delete ui;
}


/*Metodo utilizado para poder navegar a la ventana de agregar*/
void PantallaSucursal::mostrarEstadoEnvios(){

    this->solicitarTitulo("Ver Estado de Envios");
    this->ui->stackedWidget->setCurrentWidget(this->pantallaEstadoEnvios);
    this->pantallaEstadoEnvios->inicializarRed(this->controladorGestion->obtenerGrafo(),this->controladorGestion->obtenerSucursalActual());

}

/*Signal que permite poder cambiar el texto de un label*/
void PantallaSucursal::solicitarTitulo(QString titulo){
    emit cambiarTitulo(titulo);
}

/*Metodo utilizado para poder navegar a la ventana de agregar*/
void PantallaSucursal::mostrarEnvioProductos(){

    if (!this->pantallaEnviarProducto) {

        this->pantallaEnviarProducto = new PantallaEnviarProductos(this);

        this->ui->stackedWidget->addWidget(this->pantallaEnviarProducto);

        //Se conectan las signals para poder interactuar con la pantalla
        /*connect(this->controladorCrud, &Controlador::logInsertArbolAvl,this->pantallaAgregar, &PantallaAgregar::appendAvlLog);

        connect(this->controladorCrud, &Controlador::logInsertArbolB,this->pantallaAgregar, &PantallaAgregar::appendBLog);

        connect(this->controladorCrud, &Controlador::logInsertArbolBMas,this->pantallaAgregar, &PantallaAgregar::appendBMasLog);

        connect(this->controladorCrud, &Controlador::logInsertListaOrdenada,this->pantallaAgregar, &PantallaAgregar::appendListOrdenadaLog);

        connect(this->controladorCrud, &Controlador::logInsertListaNoOrdenada,this->pantallaAgregar, &PantallaAgregar::appendListNoOrdenadaLog);

        connect(this->controladorCrud, &Controlador::logInsertTablaHash,this->pantallaAgregar, &PantallaAgregar::appendTablaHash);

        connect(this->controladorCrud, &Controlador::tiempoProcesoInsert, this->pantallaAgregar, &PantallaAgregar::mostrarTiempo);

        connect(this->pantallaAgregar, &PantallaAgregar::insertarProducto, this->controladorCrud, &Controlador::insercionProducto);

        connect(this->pantallaAgregar, &PantallaAgregar::verArboles, this, &PantallaMain::mostrarVerArboles);

        connect(this->controladorCrud, &Controlador::tiempoProcesoInsert, this->pantallaAgregar, &PantallaAgregar::mostrarTiempo);

        connect(this, &PantallaMain::limpiarAgregar, this->pantallaAgregar, &PantallaAgregar::limpiarPantalla);
    */
    }

    this->solicitarTitulo("Enviar Productos");
    this->ui->stackedWidget->setCurrentWidget(this->pantallaEnviarProducto);

    this->pantallaEnviarProducto->inicializarRed(this->controladorGestion->obtenerGrafo(),this->controladorGestion->obtenerSucursalActual());

}

/*Metodo que permite abrir los envios*/
void PantallaSucursal::on_btnVerEnvios_clicked()
{
    this->mostrarEstadoEnvios();
}

/*Metodo que permite abrir la ventana para hacer los envios*/
void PantallaSucursal::on_btnEnvioProducto_clicked()
{
    this->mostrarEnvioProductos();
}

