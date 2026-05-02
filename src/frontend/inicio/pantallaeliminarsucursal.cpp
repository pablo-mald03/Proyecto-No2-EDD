#include "pantallaeliminarsucursal.h"
#include "ui_pantallaeliminarsucursal.h"
#include<QMessageBox>

PantallaEliminarSucursal::PantallaEliminarSucursal(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaEliminarSucursal)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_StyledBackground, true);

    //Se aplica el estilo al contenedor padre
    this->setStyleSheet("QWidget#PantallaEliminarSucursal { "
                        "border-image: url(:/assets/fondo/GrafosBackground.png) 0 0 0 0 stretch stretch; "
                        "} ");
    this->ui->textGrafo->setReadOnly(true);
}

/*Metodo signal que permite limpiar los datos de una pantalla*/
void PantallaEliminarSucursal::limpiarPantalla(){
    this->limpiarDatos();
    this->limpiarLogs();
}

/*Metodo que permite limpiar los componentes de insercion*/
void PantallaEliminarSucursal::limpiarDatos(){

    this->ui->textID->clear();
}

/*Metodo que permite limpiar los logs*/
void PantallaEliminarSucursal::limpiarLogs(){

    this->ui->textGrafo->clear();
    this->ui->labelTiempoGrafo->setText("Tiempo de eliminacion: 0 ms");
}


/*Metodo que permite validar las entradas*/
bool PantallaEliminarSucursal::validarCampos() {
    QString idStr = ui->textID->text();

    return !idStr.isEmpty();
}

void PantallaEliminarSucursal::appendGrafoLog(QString mensaje, QString color){

    this->ui->textGrafo->append(
        "<span style='color:" + color + ";'>" + mensaje + "</span>"
        );
}


/*---***--- Fin del Apartado de metodos que permiten comunicar a la UI los logs que se van a mostrar----***--*/


/*Metodo para poder dar el tiempo total en procesar una instruccion*/
void PantallaEliminarSucursal::mostrarTiempo( double milisegundos){

    QString tiempoTexto = "Tiempo de eliminacion: " + QString::number(milisegundos, 'f', 3) + " ms";

    this->ui->labelTiempoGrafo->setText( tiempoTexto);
}


/*Destructor*/
PantallaEliminarSucursal::~PantallaEliminarSucursal()
{
    delete ui;
}

void PantallaEliminarSucursal::on_btnEliminar_clicked()
{

    if (!validarCampos()) {
        QMessageBox::warning(this, "Campos invalidos",
                             "Por favor, revisa los campos. El ID no debe estar vacio.");
        return;
    }

    std::string id = ui->textID->text().trimmed().toStdString();

    emit eliminarSucursal(id);

}

void PantallaEliminarSucursal::on_btnLimpiar_clicked() {
    this->limpiarDatos();
}

void PantallaEliminarSucursal::on_btnSucursales_clicked()
{
    emit verSucursales();
}

