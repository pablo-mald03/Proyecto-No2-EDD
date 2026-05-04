#include "pantallaverarboles.h"
#include "ui_pantallaverarboles.h"

PantallaVerArboles::PantallaVerArboles(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaVerArboles), contadorPantallas(1)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_StyledBackground, true);

    //Se aplica el estilo al contenedor padre
    this->setStyleSheet("QWidget#PantallaVerArboles { "
                        "border-image: url(:/assets/fondo/fondooverlay.png) 0 0 0 0 stretch stretch; "
                        "} ");

    this->pantallaAvl = new PantallaArbolAvl();

    this->ui->stackedWidget->addWidget(this->pantallaAvl);

    /*Connect principal para mostrar la vista del arbol AVL*/
    connect(this->pantallaAvl, &PantallaArbolAvl::solicitarArbolAvl, this, &PantallaVerArboles::onSolicitarArbolAvl);
    connect(this->pantallaAvl, &PantallaArbolAvl::solicitarGraphvizAvl, this, &PantallaVerArboles::onSolicitarGraphvizAvl);

    this->mostrarVistaAvl();

}

/*Destructor*/
PantallaVerArboles::~PantallaVerArboles()
{
    delete ui;
}

/*Metodo que permite generar el reinicio y foco a la primera vista de los arboles*/
void PantallaVerArboles::reestablecerVistas(){
    this->contadorPantallas = 1;
    this->mostrarVistaAvl();
}

/*Metodo que permite mostrar el arbol Avl*/
void PantallaVerArboles::mostrarVistaAvl(){
    this->ui->labelArboles->setText("Arbol AVL");
    this->ui->stackedWidget->setCurrentWidget(this->pantallaAvl);
    this->onSolicitarArbolAvl();
}

/*Metodo que permite mostrar el arbol B*/
void PantallaVerArboles::mostrarVistaB(){

    if (!this->pantallaB) {

        this->pantallaB = new PantallaArbolB(this);

        ui->stackedWidget->addWidget(this->pantallaB);

        //Se conectan las signals para poder interactuar con la pantalla
        connect(this->pantallaB, &PantallaArbolB::solicitarArbolB, this, &PantallaVerArboles::onSolicitarArbolB);
        connect(this->pantallaB, &PantallaArbolB::solicitarGraphvizB, this, &PantallaVerArboles::onSolicitarGraphvizB);
    }

    this->ui->labelArboles->setText("Arbol B");
    this->ui->stackedWidget->setCurrentWidget(this->pantallaB);
    this->solicitarArbolB();
}

/*Metodo que permite mostrar el arbol B+*/
void PantallaVerArboles::mostrarVistaBMas(){

    if (!this->pantallaBMas) {

        this->pantallaBMas = new PantallaArbolBMas(this);

        ui->stackedWidget->addWidget(this->pantallaBMas);

        //Se conectan las signals para poder interactuar con la pantalla
        connect(this->pantallaBMas, &PantallaArbolBMas::solicitarArbolBMas, this, &PantallaVerArboles::onSolicitarArbolBMas);
        connect(this->pantallaBMas, &PantallaArbolBMas::solicitarGraphvizBMas, this, &PantallaVerArboles::onSolicitarGraphvizBMas);
    }

    this->ui->labelArboles->setText("Arbol B+");
    this->ui->stackedWidget->setCurrentWidget(this->pantallaBMas);
    this->solicitarArbolBMas();
}

/*Metodo que permite mostrar la tabla hash*/
void PantallaVerArboles::mostrarVistaTablaHash(){

    if (!this->pantallaTablaHash) {

        this->pantallaTablaHash = new PantallaTablaHash(this);

        ui->stackedWidget->addWidget(this->pantallaTablaHash);

        //Se conectan las signals para poder interactuar con la pantalla
        connect(this->pantallaTablaHash, &PantallaTablaHash::solicitarGraphvizHash, this, &PantallaVerArboles::onSolicitarGraphvizTablaHash);
    }

    this->ui->labelArboles->setText("Tabla Hash");
    this->ui->stackedWidget->setCurrentWidget(this->pantallaTablaHash);
    this->solicitarTablaHash();
}

/*Metodo que permite mostrar la lista*/
void PantallaVerArboles::mostrarVistaLista(){

    if (!this->pantallaListaEnlazada) {

        this->pantallaListaEnlazada = new PantallaListaEnlazada(this);

        ui->stackedWidget->addWidget(this->pantallaListaEnlazada);

        //Se conectan las signals para poder interactuar con la pantalla
        connect(this->pantallaListaEnlazada, &PantallaListaEnlazada::solicitarGraphvizListaOrdenada, this, &PantallaVerArboles::onSolicitarGraphvizLista);
    }

    this->ui->labelArboles->setText("Lista Ordenada");
    this->ui->stackedWidget->setCurrentWidget(this->pantallaListaEnlazada);
    this->solicitarLista();
}


/*Metodo que permite ir moviendose entre vistas*/
void PantallaVerArboles::refrescarVista(){

    switch(this->contadorPantallas){

        case 1:
            this->mostrarVistaAvl();
            break;
        case 2:
            this->mostrarVistaB();
            break;
        case 3:
            this->mostrarVistaBMas();
            break;
        case 4:
            this->mostrarVistaTablaHash();
            break;
        case 5:
            this->mostrarVistaLista();
            break;
    }

}


/*Metodo que permite ir a la siguiente vista*/
void PantallaVerArboles::on_btnSiguiente_clicked()
{
    if(this->contadorPantallas >= 5){
        return;
    }

    this->contadorPantallas++;

    this->refrescarVista();
}

/*Metodo que permite ir a la anterior vista*/
void PantallaVerArboles::on_btnAnterior_clicked()
{
    if(this->contadorPantallas == 1){
        return;
    }

    this->contadorPantallas--;

    this->refrescarVista();
}

/*Metodos que permiten generar las acciones cada vez que se ejecutan las cargas de los arboles*/
/*Metodo para recibir el arbol AVL*/
void PantallaVerArboles::recibirArbolAvl(NodoAvl * arbol){

    if(this->pantallaAvl){
        this->pantallaAvl->setArbol(arbol);
    }

}


/*Metodo para recibir el graphviz del arbol AVL*/
void PantallaVerArboles::recibirGrapvizAvl(std::string dot){

    if(this->pantallaAvl){
        this->pantallaAvl->generarGraphviz(dot);
    }
}


/*Metodo para recibir el graphviz del arbol B*/
void PantallaVerArboles::recibirGrapvizB(std::string dot){

    if(this->pantallaB){
        this->pantallaB->generarGraphviz(dot);
    }
}

/*Metodo para recibir el graphviz del arbol B+*/
void PantallaVerArboles::recibirGrapvizBMas(std::string dot){

    if(this->pantallaBMas){
        this->pantallaBMas->generarGraphviz(dot);
    }
}

/*Metodo para recibir el graphviz de la tabla Hash*/
void PantallaVerArboles::recibirGrapvizTablaHash(std::string dot){

    if(this->pantallaTablaHash){
        this->pantallaTablaHash->generarGraphviz(dot);
    }
}

/*Metodo para recibir el graphviz de la lista enlazada ordenada*/
void PantallaVerArboles::recibirGrapvizLista(std::string dot){

    if(this->pantallaListaEnlazada){
        this->pantallaListaEnlazada->generarGraphviz(dot);
    }
}


/*Metodo para recibir el arbol B*/
void PantallaVerArboles::recibirArbolB(NodoB * arbol){

    if(this->pantallaB){
        this->pantallaB->setArbol(arbol);
    }

}

/*Metodo para recibir el arbol B+ */
void PantallaVerArboles::recibirArbolBMas(NodoBMas * arbol){

    if(this->pantallaBMas){
        this->pantallaBMas->setArbol(arbol);
    }
}

/*Metodo para recibir la tabla Hash */
void PantallaVerArboles::recibirTablaHash(ListaEnlazada<Producto>**  _tabla, int capacidad){

    if(this->pantallaTablaHash){
        this->pantallaTablaHash->setTabla(_tabla,capacidad);
    }
}

/*Metodo para recibir la lista ordenada */
void PantallaVerArboles::recibirLista(NodoLista<Producto> * _cabeza, int parametro){

    if(this->pantallaListaEnlazada){
        this->pantallaListaEnlazada->setCabeza(_cabeza,parametro);
    }
}


/*Metodos para poder solicitar el graphviz del arbol AVL*/
void PantallaVerArboles::onSolicitarGraphvizAvl(){
    emit solicitarGraphArbolAvl();
}

/*Metodos para poder solicitar el graphviz del arbol B*/
void PantallaVerArboles::onSolicitarGraphvizB(){
    emit solicitarGraphArbolB();
}

/*Metodos para poder solicitar el graphviz del arbol B+*/
void PantallaVerArboles::onSolicitarGraphvizBMas(){
    emit solicitarGraphArbolBMas();
}

/*Metodos para poder solicitar el graphviz de la tabla hash*/
void PantallaVerArboles::onSolicitarGraphvizTablaHash(){
    emit solicitarGraphTablaHash();
}

/*Metodos para poder solicitar el graphviz de la lista ordenada*/
void PantallaVerArboles::onSolicitarGraphvizLista(){
    emit solicitarGraphLista();
}


/*Metodo que permite solicitar al arbol AVL para poderlo graficar*/
void PantallaVerArboles::onSolicitarArbolAvl()
{
    emit solicitarArbolAvl();
}

/*Metodo que permite solicitar al arbol B para poderlo graficar*/
void PantallaVerArboles::onSolicitarArbolB()
{
    emit solicitarArbolB();
}


/*Metodo que permite solicitar al arbol B+ para poderlo graficar*/
void PantallaVerArboles::onSolicitarArbolBMas()
{
    emit solicitarArbolBMas();
}


/*Metodo que permite solicitar la tabla hash para poderla graficar*/
void PantallaVerArboles::onSolicitarTablaHash()
{
    emit solicitarTablaHash();
}


/*Metodo que permite solicitar la lista enlazada ordenada para poderla graficar*/
void PantallaVerArboles::onSolicitarLista()
{
    emit solicitarLista();
}
