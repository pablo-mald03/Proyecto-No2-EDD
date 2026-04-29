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

    this->inicio = new PantallaPrincipal(this);

    this->controladorCrud= new Controlador();
    this->ui->stackedWidget->addWidget(this->inicio);



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
    mostrarInicio();
}

/*Region de metodos para poder mostrar las diferentes vistas*/
void MainWindow::mostrarInicio(){

    this->ui->labelTasks->setText("Menu Principal");
    this->ui->stackedWidget->setCurrentWidget(this->inicio);
    this->controladorCrud->evaluarEstadoCerrarCsv();
    this->controladorCrud->verificarRefrescado();
    this->controladorCrud->actualizarDatosIngresados();
}


/*Metodo utilizado para poder navegar a la ventana de agregar*/
void MainWindow::mostrarAgregar(){

    if (!this->pantallaAgregar) {

        this->pantallaAgregar = new PantallaAgregar(this);

        ui->stackedWidget->addWidget(this->pantallaAgregar);

        //Se conectan las signals para poder interactuar con la pantalla
        connect(this->controladorCrud, &Controlador::logInsertArbolAvl,this->pantallaAgregar, &PantallaAgregar::appendAvlLog);

        connect(this->controladorCrud, &Controlador::logInsertArbolB,this->pantallaAgregar, &PantallaAgregar::appendBLog);

        connect(this->controladorCrud, &Controlador::logInsertArbolBMas,this->pantallaAgregar, &PantallaAgregar::appendBMasLog);

        connect(this->controladorCrud, &Controlador::logInsertListaOrdenada,this->pantallaAgregar, &PantallaAgregar::appendListOrdenadaLog);

        connect(this->controladorCrud, &Controlador::logInsertListaNoOrdenada,this->pantallaAgregar, &PantallaAgregar::appendListNoOrdenadaLog);

        connect(this->controladorCrud, &Controlador::tiempoProcesoInsert, this->pantallaAgregar, &PantallaAgregar::mostrarTiempo);

        connect(this->pantallaAgregar, &PantallaAgregar::insertarProducto, this->controladorCrud, &Controlador::insercionProducto);

        connect(this->pantallaAgregar, &PantallaAgregar::verArboles, this, &MainWindow::mostrarVerArboles);

        connect(this->controladorCrud, &Controlador::tiempoProcesoInsert, this->pantallaAgregar, &PantallaAgregar::mostrarTiempo);

        connect(this, &MainWindow::limpiarAgregar, this->pantallaAgregar, &PantallaAgregar::limpiarPantalla);
    }

    emit this->limpiarAgregar();
    this->ui->labelTasks->setText("Agregar Productos");
    this->ui->stackedWidget->setCurrentWidget(this->pantallaAgregar);
}

/*Metodo utilizado para poder navegar a la ventana de buscar por nombre*/
void MainWindow::mostrarBuscarNombre(){

    if (!this->pantallaBusquedaNombre) {

        this->pantallaBusquedaNombre = new PantallaBuscarPorNombre(this);

        ui->stackedWidget->addWidget(this->pantallaBusquedaNombre);

        //Se conectan las signlas para poder interactuar con las pantallas
        connect(this->controladorCrud, &Controlador::logBusquedaNombreArbolAvl,this->pantallaBusquedaNombre, &PantallaBuscarPorNombre::appendAvlLog);

        connect(this->controladorCrud, &Controlador::logBusquedaNombreListaOrdenada,this->pantallaBusquedaNombre, &PantallaBuscarPorNombre::appendListOrdenadaLog);

        connect(this->controladorCrud, &Controlador::logBusquedaNombreListaNoOrdenada,this->pantallaBusquedaNombre, &PantallaBuscarPorNombre::appendListNoOrdenadaLog);

        connect(this->controladorCrud, &Controlador::tiempoProcesoBusquedaNombre, this->pantallaBusquedaNombre, &PantallaBuscarPorNombre::mostrarTiempo);

        connect(this->pantallaBusquedaNombre, &PantallaBuscarPorNombre::buscarPorNombre, this->controladorCrud, &Controlador::buscarPorNombre);

        connect(this->pantallaBusquedaNombre, &PantallaBuscarPorNombre::verArboles, this, &MainWindow::mostrarVerArboles);

        connect(this->controladorCrud, &Controlador::tiempoProcesoBusquedaNombre, this->pantallaBusquedaNombre, &PantallaBuscarPorNombre::mostrarTiempo);

        connect(this, &MainWindow::limpiarBuscarNombre, this->pantallaBusquedaNombre, &PantallaBuscarPorNombre::limpiarPantalla);

        /*Pruebas*/
        connect(this->controladorCrud, &Controlador::mostrarTiempoPruebasNombre, this->pantallaBusquedaNombre, &PantallaBuscarPorNombre::mostrarTiempoPruebas);

        connect(this->pantallaBusquedaNombre, &PantallaBuscarPorNombre::pruebaAleatoria, this->controladorCrud, &Controlador::pruebaAleatoriaNombre);

        connect(this->pantallaBusquedaNombre, &PantallaBuscarPorNombre::pruebaExtremos, this->controladorCrud, &Controlador::pruebaExtremosNombre);
    }

    emit this->limpiarBuscarNombre();
    this->controladorCrud->ordenarListado(1);
    this->ui->labelTasks->setText("Busqueda por nombre");
    this->ui->stackedWidget->setCurrentWidget(this->pantallaBusquedaNombre);

}

/*Metodo utilizado para poder navegar a la ventana de buscar por categoria*/
void MainWindow::mostrarBuscarCategoria(){

    if (!this->pantallaBusquedaCategoria) {

        this->pantallaBusquedaCategoria = new PantallaBuscarPorCategoria(this);

        ui->stackedWidget->addWidget(this->pantallaBusquedaCategoria);

        //Se conectan las signlas para poder interactuar con las pantallas PENDIENTE
        connect(this->controladorCrud, &Controlador::logBusquedaCategoriaArbolBMas,this->pantallaBusquedaCategoria, &PantallaBuscarPorCategoria::appendBMasLog);

        connect(this->controladorCrud, &Controlador::logBusquedaCategoriaListaOrdenada,this->pantallaBusquedaCategoria, &PantallaBuscarPorCategoria::appendListOrdenadaLog);

        connect(this->controladorCrud, &Controlador::logBusquedaCategoriaListaNoOrdenada,this->pantallaBusquedaCategoria, &PantallaBuscarPorCategoria::appendListNoOrdenadaLog);

        connect(this->controladorCrud, &Controlador::tiempoProcesoBusquedaCategoria, this->pantallaBusquedaCategoria, &PantallaBuscarPorCategoria::mostrarTiempo);

        connect(this->pantallaBusquedaCategoria, &PantallaBuscarPorCategoria::buscarPorCategoria, this->controladorCrud, &Controlador::buscarPorCategoria);

        connect(this->pantallaBusquedaCategoria, &PantallaBuscarPorCategoria::verArboles, this, &MainWindow::mostrarVerArboles);

        connect(this->controladorCrud, &Controlador::tiempoProcesoBusquedaCategoria, this->pantallaBusquedaCategoria, &PantallaBuscarPorCategoria::mostrarTiempo);

        connect(this, &MainWindow::limpiarBuscarCategoria, this->pantallaBusquedaCategoria, &PantallaBuscarPorCategoria::limpiarPantalla);

        /*Pruebas*/
        connect(this->controladorCrud, &Controlador::mostrarTiempoPruebasCategoria, this->pantallaBusquedaCategoria, &PantallaBuscarPorCategoria::mostrarTiempoPruebas);

        connect(this->pantallaBusquedaCategoria, &PantallaBuscarPorCategoria::pruebaAleatoria, this->controladorCrud, &Controlador::pruebaAleatoriaCategoria);

        connect(this->pantallaBusquedaCategoria, &PantallaBuscarPorCategoria::pruebaExtremos, this->controladorCrud, &Controlador::pruebaExtremosCategoria);

    }

    emit this->limpiarBuscarCategoria();
    this->controladorCrud->ordenarListado(2);
    this->ui->labelTasks->setText("Busqueda por categoria");
    this->ui->stackedWidget->setCurrentWidget(this->pantallaBusquedaCategoria);

}

/*Metodo utilizado para poder navegar a la ventana de buscar por rango*/
void MainWindow::mostrarBuscarRango(){

    if (!this->pantallaBusquedaRango) {

        this->pantallaBusquedaRango = new PantallaBuscarRango(this);

        ui->stackedWidget->addWidget(this->pantallaBusquedaRango);

        //Se conectan las signlas para poder interactuar con las pantallas PENDIENTE
        connect(this->controladorCrud, &Controlador::logBusquedaFechasArbolB,this->pantallaBusquedaRango, &PantallaBuscarRango::appendBLog);

        connect(this->controladorCrud, &Controlador::logBusquedaFechasListaOrdenada,this->pantallaBusquedaRango, &PantallaBuscarRango::appendListOrdenadaLog);

        connect(this->controladorCrud, &Controlador::logBusquedaFechasListaNoOrdenada,this->pantallaBusquedaRango, &PantallaBuscarRango::appendListNoOrdenadaLog);

        connect(this->controladorCrud, &Controlador::tiempoProcesoBusquedaFechas, this->pantallaBusquedaRango, &PantallaBuscarRango::mostrarTiempo);

        connect(this->pantallaBusquedaRango, &PantallaBuscarRango::buscarPorFechas, this->controladorCrud, &Controlador::buscarPorFecha);

        connect(this->pantallaBusquedaRango, &PantallaBuscarRango::verArboles, this, &MainWindow::mostrarVerArboles);

        connect(this->controladorCrud, &Controlador::tiempoProcesoBusquedaCategoria, this->pantallaBusquedaRango, &PantallaBuscarRango::mostrarTiempo);

        connect(this, &MainWindow::limpiarBuscarRango, this->pantallaBusquedaRango, &PantallaBuscarRango::limpiarPantalla);

        /*Pruebas*/
        connect(this->controladorCrud, &Controlador::mostrarTiempoPruebasFechas, this->pantallaBusquedaRango, &PantallaBuscarRango::mostrarTiempoPruebas);

        connect(this->pantallaBusquedaRango, &PantallaBuscarRango::pruebaAleatoria, this->controladorCrud, &Controlador::pruebaAleatoriaFechas);

        connect(this->pantallaBusquedaRango, &PantallaBuscarRango::pruebaExtremos, this->controladorCrud, &Controlador::pruebaExtremosFechas);

    }

    emit this->limpiarBuscarRango();
    this->controladorCrud->ordenarListado(3);
    this->ui->labelTasks->setText("Busqueda por rango de caducidad");
    this->ui->stackedWidget->setCurrentWidget(this->pantallaBusquedaRango);

}

/*Metodo utilizado para poder navegar a la ventana de buscar por rango*/
void MainWindow::mostrarEliminar(){

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

}

/*Metodo utilizado para poder navegar a la ventana de listar por nombres*/
void MainWindow::mostrarListarNombre(){

    if (!this->pantallaListarNombre) {

        this->pantallaListarNombre = new PantallaListarNombre(this);

        ui->stackedWidget->addWidget(this->pantallaListarNombre);

        //Se conectan las signlas para poder interactuar con las pantallas PENDIENTE
        connect(this->controladorCrud, &Controlador::logListarArbolAvl,this->pantallaListarNombre, &PantallaListarNombre::appendAvlLog);
        connect(this->controladorCrud, &Controlador::logListarListaOrdenada,this->pantallaListarNombre, &PantallaListarNombre::appendListOrdenadaLog);
        connect(this->controladorCrud, &Controlador::logListarListaNoOrdenada,this->pantallaListarNombre, &PantallaListarNombre::appendListNoOrdenadaLog);


        connect(this->controladorCrud, &Controlador::tiempoEliminarProceso, this->pantallaListarNombre, &PantallaListarNombre::mostrarTiempo);

        connect(this->pantallaListarNombre, &PantallaListarNombre::listarPorNombres, this->controladorCrud, &Controlador::listarProductos);

        connect(this->pantallaListarNombre, &PantallaListarNombre::verArboles, this, &MainWindow::mostrarVerArboles);

        connect(this->controladorCrud, &Controlador::tiempoProcesoListarNombre, this->pantallaListarNombre, &PantallaListarNombre::mostrarTiempo);

        connect(this, &MainWindow::limpiarListar, this->pantallaListarNombre, &PantallaListarNombre::limpiarPantalla);
    }

    emit this->limpiarListar();
    this->controladorCrud->ordenarListado(1);
    this->ui->labelTasks->setText("Listar por nombre");
    this->ui->stackedWidget->setCurrentWidget(this->pantallaListarNombre);

}

/*Metodo utilizado para poder navegar a la ventana de ver arboles*/
void MainWindow::mostrarVerArboles(){

    if (!this->pantallaVerArboles) {

        this->pantallaVerArboles = new PantallaVerArboles(this);

        ui->stackedWidget->addWidget(this->pantallaVerArboles);

        /*Signals del arbol AVL*/
        connect(this->pantallaVerArboles, &PantallaVerArboles::solicitarArbolAvl,
                this->controladorCrud, &Controlador::obtenerArbolAvl);

        connect(this->controladorCrud, &Controlador::enviarArbolAvl,
                this->pantallaVerArboles, &PantallaVerArboles::recibirArbolAvl);

        connect(this->pantallaVerArboles, &PantallaVerArboles::solicitarGraphArbolAvl,
                this->controladorCrud, &Controlador::generarGraphArbolAvl);

        connect(this->controladorCrud, &Controlador::enviarGraphvizArbolAvl,
                this->pantallaVerArboles, &PantallaVerArboles::recibirGrapvizAvl);


        /*Signals del arbol B*/
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

}


MainWindow::~MainWindow()
{
    delete ui;
}

/*Metodo que permite navegar al inicio*/
void MainWindow::on_btnCsv_clicked()
{
    mostrarInicio();
}

/*Metodo que permite navegar a la pantalla de agregar*/
void MainWindow::on_btnAgregar_clicked()
{
    this->mostrarAgregar();
}

/*Metodo que permite navegar a la pantalla de buscar por nombre*/
void MainWindow::on_btnBuscarNombre_clicked()
{
    this->mostrarBuscarNombre();
}

/*Metodo que permite navegar a la pantalla de buscar por categoria*/
void MainWindow::on_btnBuscarCategoria_clicked()
{
    this->mostrarBuscarCategoria();
}

/*Metodo que permite navegar a la pantalla de buscar por rango de caducidad*/
void MainWindow::on_btnBuscarCaducidad_clicked()
{
    this->mostrarBuscarRango();
}

/*Metodo que permite navegar a la pantalla de eliminar un producto*/
void MainWindow::on_btnEliminar_clicked()
{
    this->mostrarEliminar();
}

/*Metodo que permite navegar a la pantalla de listar por nombre*/
void MainWindow::on_btnListarNombre_clicked()
{
    this->mostrarListarNombre();
}

/*Metodo que permite navegar a la pantalla de mostrar el estado de los arboles*/
void MainWindow::on_btnArboles_clicked()
{
    this->mostrarVerArboles();
}

