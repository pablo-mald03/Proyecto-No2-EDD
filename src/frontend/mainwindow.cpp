#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScreen>
#include <QGuiApplication>
#include <QStyle>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setStyleSheet("QMainWindow { background-color: #1a1a1a; } ");

    //Instrucciones indicadas para poder abrir en mas de una pantalla
    QList<QScreen *> screens = QGuiApplication::screens();

    if (screens.size() > 1) {
        QScreen *segundaPantalla = screens.at(1);
        QRect geometria = segundaPantalla->availableGeometry();

        this->setGeometry(
            QStyle::alignedRect(
                Qt::LeftToRight,
                Qt::AlignCenter,
                this->size(),
                geometria
                )
            );
    } else {
        this->move(QGuiApplication::primaryScreen()->availableGeometry().center() - this->rect().center());
    }

    this->pantallaInicio = new PantallaSistema(this);

    this->controladorGeneral= new ControladorNegocio();
    this->ui->stackedWidget->addWidget(this->pantallaInicio);


/*
    connect(this->inicio, &PantallaPrincipal::csvCargado, this->controladorCrud, &Controlador::procesarCsv);
    connect(this->controladorCrud, &Controlador::logArbolAvl,this->inicio, &PantallaPrincipal::appendAvlLog);
    connect(this->controladorCrud, &Controlador::logArbolB,this->inicio, &PantallaPrincipal::appendBLog);
    connect(this->controladorCrud, &Controlador::logArbolBMas,this->inicio, &PantallaPrincipal::appendBMasLog);
    connect(this->controladorCrud, &Controlador::logLista,this->inicio, &PantallaPrincipal::appendListLog);
    connect(this->controladorCrud, &Controlador::logCargaCsv,this->inicio, &PantallaPrincipal::appendLogCarga);
    connect(this->controladorCrud, &Controlador::tiempoProceso, this->inicio, &PantallaPrincipal::mostrarTiempo);
    connect(this->inicio, &PantallaPrincipal::solicitarLogErrores, this->controladorCrud, &Controlador::prepararLogParaDescarga);
    connect(this->controladorCrud, &Controlador::logDescargar, this->inicio, &PantallaPrincipal::logListoParaDescargar);
    connect(this->controladorCrud, &Controlador::evaluarErroresLog, this->inicio, &PantallaPrincipal::evaluarErrores);
    connect(this->controladorCrud, &Controlador::evaluarCerrarCsv, this->inicio, &PantallaPrincipal::evaluarCierreCsv);
    connect(this->controladorCrud, &Controlador::refrescarDatos, this->inicio, &PantallaPrincipal::refrescarPantallaCsv);

    connect(this->inicio, &PantallaPrincipal::solicitarGuardarCsv,this->controladorCrud, &Controlador::guardarArchivoCsv);
    connect(this->controladorCrud, &Controlador::contenidoCsvListo, this->inicio, &PantallaPrincipal::recibirGuardadoCsv);

    connect(this->inicio, &PantallaPrincipal::solicitarLimpieza,this->controladorCrud, &Controlador::limpiarDatos);
   */
    mostrarInicio();
}

/*Region de metodos para poder mostrar las diferentes vistas*/
void MainWindow::mostrarInicio(){

   // this->pantallaInicio->setText("Menu Principal");
   /*this->ui->stackedWidget->setCurrentWidget(this->pantallaInicio);
    this->controladorGeneral->evaluarEstadoCerrarCsv();
    this->controladorGeneral->verificarRefrescado();
    this->controladorGeneral->actualizarDatosIngresados();*/
}

/*Metodo utilizado para poder navegar a la ventana de buscar por rango*/
void MainWindow::mostrarGestion(){
/*
    if (!this->pantallaEliminar) {

        this->pantallaEliminar = new PantallaEliminarProducto(this);

        ui->stackedWidget->addWidget(this->pantallaEliminar);

        //Se conectan las signlas para poder interactuar con las pantallas PENDIENTE
        connect(this->controladorCrud, &Controlador::logEliminarArbolAvl,this->pantallaEliminar, &PantallaEliminarProducto::appendAvlLog);
        connect(this->controladorCrud, &Controlador::logEliminarArbolB,this->pantallaEliminar, &PantallaEliminarProducto::appendBLog);
        connect(this->controladorCrud, &Controlador::logEliminarArbolBMas,this->pantallaEliminar, &PantallaEliminarProducto::appendBMasLog);
        connect(this->controladorCrud, &Controlador::logEliminarListaOrdenada,this->pantallaEliminar, &PantallaEliminarProducto::appendListOrdenadaLog);
        connect(this->controladorCrud, &Controlador::logEliminarListaNoOrdenada,this->pantallaEliminar, &PantallaEliminarProducto::appendListNoOrdenadaLog);


        connect(this->controladorCrud, &Controlador::tiempoEliminarProceso, this->pantallaEliminar, &PantallaEliminarProducto::mostrarTiempo);


        connect(this->pantallaEliminar, &PantallaEliminarProducto::eliminarProducto, this->controladorCrud, &Controlador::eliminarProducto);

        connect(this->pantallaEliminar, &PantallaEliminarProducto::verArboles, this, &MainWindow::mostrarVerArboles);

        connect(this->controladorCrud, &Controlador::tiempoEliminarProceso, this->pantallaEliminar, &PantallaEliminarProducto::mostrarTiempo);

        connect(this, &MainWindow::limpiarEliminar, this->pantallaEliminar, &PantallaEliminarProducto::limpiarPantalla);
    }

    emit this->limpiarEliminar();
    this->controladorCrud->ordenarListado(4);
    this->ui->labelTasks->setText("Eliminar productos");
    this->ui->stackedWidget->setCurrentWidget(this->pantallaEliminar);
*/
}


/*Metodo utilizado para poder navegar a la ventana de ver arboles
void MainWindow::mostrarVerArboles(){

    /*if (!this->pantallaVerArboles) {

        this->pantallaVerArboles = new PantallaVerArboles(this);

        ui->stackedWidget->addWidget(this->pantallaVerArboles);

        /*Signals del arbol AVL
        connect(this->pantallaVerArboles, &PantallaVerArboles::solicitarArbolAvl,
                this->controladorCrud, &Controlador::obtenerArbolAvl);

        connect(this->controladorCrud, &Controlador::enviarArbolAvl,
                this->pantallaVerArboles, &PantallaVerArboles::recibirArbolAvl);

        connect(this->pantallaVerArboles, &PantallaVerArboles::solicitarGraphArbolAvl,
                this->controladorCrud, &Controlador::generarGraphArbolAvl);

        connect(this->controladorCrud, &Controlador::enviarGraphvizArbolAvl,
                this->pantallaVerArboles, &PantallaVerArboles::recibirGrapvizAvl);


        /*Signals del arbol B
        connect(this->pantallaVerArboles, &PantallaVerArboles::solicitarArbolB,
                this->controladorCrud, &Controlador::obtenerArbolB);

        connect(this->controladorCrud, &Controlador::enviarArbolB,
                this->pantallaVerArboles, &PantallaVerArboles::recibirArbolB);

        connect(this->pantallaVerArboles, &PantallaVerArboles::solicitarGraphArbolB,
                this->controladorCrud, &Controlador::generarGraphArbolB);

        connect(this->controladorCrud, &Controlador::enviarGraphvizArbolB,
                this->pantallaVerArboles, &PantallaVerArboles::recibirGrapvizB);



        connect(this->pantallaVerArboles, &PantallaVerArboles::solicitarArbolBMas,
                this->controladorCrud, &Controlador::obtenerArbolBMas);

        connect(this->controladorCrud, &Controlador::enviarArbolBMas,
                this->pantallaVerArboles, &PantallaVerArboles::recibirArbolBMas);

        connect(this->pantallaVerArboles, &PantallaVerArboles::solicitarGraphArbolBMas,
                this->controladorCrud, &Controlador::generarGraphArbolBMas);

        connect(this->controladorCrud, &Controlador::enviarGraphvizArbolBMas,
                this->pantallaVerArboles, &PantallaVerArboles::recibirGrapvizBMas);

    }

    this->ui->labelTasks->setText("Visualizar Arboles");
    this->ui->stackedWidget->setCurrentWidget(this->pantallaVerArboles);
    this->pantallaVerArboles->reestablecerVistas();

}*/


MainWindow::~MainWindow()
{
    delete ui;
}


