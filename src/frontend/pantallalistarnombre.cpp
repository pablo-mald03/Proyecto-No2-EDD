#include "pantallalistarnombre.h"
#include "ui_pantallalistarnombre.h"

PantallaListarNombre::PantallaListarNombre(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaListarNombre)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_StyledBackground, true);

    //Se aplica el estilo al contenedor padre
    this->setStyleSheet("QWidget#PantallaListarNombre { "
                        "border-image: url(:/assets/fondo/fondooverlay.png) 0 0 0 0 stretch stretch; "
                        "} ");

    this->ui->textArbolAvl->setReadOnly(true);
    this->ui->textListaOrdenada->setReadOnly(true);
    this->ui->textListaNoOrdenada->setReadOnly(true);
}

/*Destructor*/
PantallaListarNombre::~PantallaListarNombre()
{
    delete ui;
}



/*---***---Apartado de metodos que permiten comunicar a la UI los logs que se van a mostrar----***--*/
void PantallaListarNombre::appendAvlLog(QString mensaje, QString color){

    QString htmlMensaje = mensaje.replace("\n", "<br>");

    this->ui->textArbolAvl->append(
        "<span style='color:" + color + ";'>" + htmlMensaje + "</span>"
        );
}

void PantallaListarNombre::appendListOrdenadaLog(QString mensaje, QString color){

    QString htmlMensaje = mensaje.replace("\n", "<br>");

    this->ui->textListaOrdenada->append(
        "<span style='color:" + color + ";'>" + htmlMensaje + "</span>"
        );
}

void PantallaListarNombre::appendListNoOrdenadaLog(QString mensaje, QString color){

    QString htmlMensaje = mensaje.replace("\n", "<br>");

    this->ui->textListaNoOrdenada->append(
        "<span style='color:" + color + ";'>" + htmlMensaje + "</span>"
        );
}


/*---***--- Fin del Apartado de metodos que permiten comunicar a la UI los logs que se van a mostrar----***--*/


/*Metodo para poder dar el tiempo total en procesar una instruccion
*
* 1 -> AVL
* 2 -> LISTA ORDENADA
* 3 -> LISTA NO ORDENADA
*
*/
void PantallaListarNombre::mostrarTiempo(int estructura, double milisegundos){

    QString tiempoTexto = "Tiempo transcurrido: " + QString::number(milisegundos, 'f', 3) + " ms";

    switch(estructura){

    case 1:
        this->ui->labelTiempoAvl->setText(tiempoTexto);
        break;

    case 2:
        this->ui->labelTiempoOrdenada->setText(tiempoTexto);
        break;

    case 3:
        this->ui->labelTiempoNoOrdenada->setText(tiempoTexto);
        break;
    }

}


/*Metodo que permite limpiar los logs*/
void PantallaListarNombre::limpiarLogs(){

    this->ui->textArbolAvl->clear();
    this->ui->textListaNoOrdenada->clear();
    this->ui->textListaOrdenada->clear();

    this->ui->labelTiempoNoOrdenada->setText("Tiempo transcurrido: 0 ms");
    this->ui->labelTiempoOrdenada->setText("Tiempo transcurrido: 0 ms");
    this->ui->labelTiempoAvl->setText("Tiempo transcurrido: 0 ms");

}

/*Metodo que permite emitir la signal para poder listar*/
void PantallaListarNombre::on_btnBuscar_clicked()
{
    emit listarPorNombres();
}


/*Metodo que permite emitir la signal para poder limpiar*/
void PantallaListarNombre::on_btnLimpiar_clicked()
{
    this->limpiarLogs();
}




/*Metodo que permite redireccionar para poder consultar los arboles*/
void PantallaListarNombre::on_btnVerArboles_clicked()
{
    emit verArboles();
}


/*Metodo signal que permite limpiar los datos de una pantalla*/
void PantallaListarNombre::limpiarPantalla(){
    this->limpiarLogs();
}






