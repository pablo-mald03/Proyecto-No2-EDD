#include "pantallacompararbusquedas.h"
#include "ui_pantallacompararbusquedas.h"
#include<QMessageBox>

PantallaCompararBusquedas::PantallaCompararBusquedas(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaCompararBusquedas)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_StyledBackground, true);

    //Se aplica el estilo al contenedor padre
    this->setStyleSheet("QWidget#PantallaCompararBusquedas { "
                        "border-image: url(:/assets/fondo/fondooverlay.png) 0 0 0 0 stretch stretch; "
                        "} ");

    this->ui->textTablaHash->setReadOnly(true);
    this->ui->textListaOrdenada->setReadOnly(true);
    this->ui->textListaNoOrdenada->setReadOnly(true);
    this->ui->textArbolAvl->setReadOnly(true);
}

/*Destructor*/
PantallaCompararBusquedas::~PantallaCompararBusquedas()
{
    delete ui;
}

/*---***---Apartado de metodos que permiten comunicar a la UI los logs que se van a mostrar----***--*/
void PantallaCompararBusquedas::appendHashLog(QString mensaje, QString color){

    QString htmlMensaje = mensaje.replace("\n", "<br>");

    this->ui->textTablaHash->append(
        "<span style='color:" + color + ";'>" + htmlMensaje + "</span>"
        );
}

void PantallaCompararBusquedas::appendListOrdenadaLog(QString mensaje, QString color){

    QString htmlMensaje = mensaje.replace("\n", "<br>");

    this->ui->textListaOrdenada->append(
        "<span style='color:" + color + ";'>" + htmlMensaje + "</span>"
        );
}

void PantallaCompararBusquedas::appendListNoOrdenadaLog(QString mensaje, QString color){

    QString htmlMensaje = mensaje.replace("\n", "<br>");

    this->ui->textListaNoOrdenada->append(
        "<span style='color:" + color + ";'>" + htmlMensaje + "</span>"
        );
}

void PantallaCompararBusquedas::appendAvlLog(QString mensaje, QString color){

    QString htmlMensaje = mensaje.replace("\n", "<br>");

    this->ui->textArbolAvl->append(
        "<span style='color:" + color + ";'>" + htmlMensaje + "</span>"
        );
}


/*---***--- Fin del Apartado de metodos que permiten comunicar a la UI los logs que se van a mostrar----***--*/


/*Metodo para poder dar el tiempo total en procesar una instruccion
*
* 1 -> HASH
* 2 -> LISTA ORDENADA
* 3 -> LISTA NO ORDENADA
* 4 -> ARBOL AVL
*
*/
void PantallaCompararBusquedas::mostrarTiempo(int estructura, double milisegundos){

    QString tiempoTexto = "Tiempo de busqueda: " + QString::number(milisegundos, 'f', 3) + " ms";

    switch(estructura){

    case 1:
        this->ui->labelTiempoHash->setText(tiempoTexto);
        break;
    case 2:
        this->ui->labelTiempoOrdenada->setText(tiempoTexto);
        break;
    case 3:
        this->ui->labelTiempoNoOrdenada->setText(tiempoTexto);
        break;
    case 4:
        this->ui->labelTiempoAvl->setText(tiempoTexto);
        break;
    }

}

/*Metodo que permite limpiar los componentes de insercion*/
void PantallaCompararBusquedas::limpiarDatos(){
    this->ui->textVeces->clear();
    this->ui->textConsulta->clear();
}

/*Metodo que permite limpiar los logs*/
void PantallaCompararBusquedas::limpiarLogs(){

    this->ui->textTablaHash->clear();
    this->ui->textListaNoOrdenada->clear();
    this->ui->textListaOrdenada->clear();
     this->ui->textArbolAvl->clear();

    this->ui->labelTiempoNoOrdenada->setText("Tiempo de busqueda: 0 ms");
    this->ui->labelTiempoOrdenada->setText("Tiempo de busqueda: 0 ms");
    this->ui->labelTiempoHash->setText("Tiempo de busqueda: 0 ms");
    this->ui->labelTiempoAvl->setText("Tiempo de busqueda: 0 ms");
}

/*Metodo signal que permite limpiar los datos de una pantalla*/
void PantallaCompararBusquedas::limpiarPantalla(){
    this->limpiarDatos();
    this->limpiarLogs();
}

/*Metodo que permite validar los campos de entrada*/
bool PantallaCompararBusquedas::validarPruebas(int &consultas, int &veces){

    QString strVeces = this->ui->textVeces->text().trimmed();
    QString strConsulta = this->ui->textConsulta->text().trimmed();

    if (strVeces.isEmpty() || strConsulta.isEmpty()) {
        QMessageBox::warning(this, "Campos vacios", "Por favor llene todos los campos \"Consultas\" y \"Veces\".");
        return false;
    }

    bool okVeces, okConsulta;
    veces = strVeces.toInt(&okVeces);
    consultas = strConsulta.toInt(&okConsulta);

    if (!okVeces || !okConsulta) {
        QMessageBox::warning(this, "Campos no numericos", "El valor de veces y de consultas tiene que ser numerico entero.");
        return false;
    }

    if (veces <= 0 || consultas <= 0) {
        QMessageBox::warning(this, "Campos negativos", "El valor de veces y de consultas no puede ser negativo.");
        return false;
    }

    return true;
}

/*Metodo que permite viajar a la vista de arboles*/
void PantallaCompararBusquedas::on_btnVerArboles_clicked()
{
    emit verArboles();
}

/*Metodo que permite ejecutar una prueba aleatoria*/
void PantallaCompararBusquedas::on_btnAleatorio_clicked()
{
    int veces = 0;
    int consultas = 0;

    bool validarEntradas = validarPruebas(consultas,veces);

    if(!validarEntradas){
        return;
    }

    this->limpiarLogs();

    emit pruebaAleatoria(consultas, veces);
}

