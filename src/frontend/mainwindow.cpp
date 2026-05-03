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

    this->ui->stackedWidget->addWidget(this->pantallaInicio);

    connect(this->pantallaInicio, &PantallaSistema::solicitarApertura, this, &MainWindow::abrirSucursal);
    /*
    connect(this->inicio, &PantallaPrincipal::solicitarLimpieza,this->controladorCrud, &Controlador::limpiarDatos);
   */
    mostrarInicio();
}

/*Metodo que permite comunicar que se va a cambiar a una sucursal*/
void MainWindow::abrirSucursal(Sucursal * _sucursal, Grafo * redGrafo){
    this->mostrarGestion(_sucursal,redGrafo);
}

/*Region de metodos para poder mostrar las diferentes vistas*/
void MainWindow::mostrarInicio(){

    this->ui->stackedWidget->setCurrentWidget(this->pantallaInicio);
    this->pantallaInicio->setPantallanInicio();
}

void MainWindow::regresarPantalla(){
    this->mostrarInicio();

}
/*Metodo utilizado para poder navegar a la ventana de buscar por rango*/
void MainWindow::mostrarGestion(Sucursal * _sucursal, Grafo * redGrafo){

    if (!this->pantallaGestion) {

        this->pantallaGestion = new PantallaGestion(this);

        ui->stackedWidget->addWidget(this->pantallaGestion);

        //Se conectan las signlas para poder interactuar con las pantallas
        connect(this->pantallaGestion, &PantallaGestion::solicitarRegreso, this, &MainWindow::regresarPantalla);
    }

    this->pantallaGestion->setSucursal(_sucursal,redGrafo);
    this->ui->stackedWidget->setCurrentWidget(this->pantallaGestion);
    this->pantallaGestion->setPantallaInicio();
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


