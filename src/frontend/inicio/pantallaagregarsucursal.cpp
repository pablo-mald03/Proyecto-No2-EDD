#include "pantallaagregarsucursal.h"
#include "ui_pantallaagregarsucursal.h"
#include<QMessageBox>

PantallaAgregarSucursal::PantallaAgregarSucursal(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaAgregarSucursal)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_StyledBackground, true);

    //Se aplica el estilo al contenedor padre
    this->setStyleSheet("QWidget#PantallaAgregarSucursal { "
                        "border-image: url(:/assets/fondo/GrafosBackground.png) 0 0 0 0 stretch stretch; "
                        "} ");

    this->ui->textGrafo->setReadOnly(true);
}

/*Destructor*/
PantallaAgregarSucursal::~PantallaAgregarSucursal()
{
    delete ui;
}

/*Metodo signal que permite limpiar los datos de una pantalla*/
void PantallaAgregarSucursal::limpiarPantalla(){
    this->limpiarDatos();
    this->limpiarLogs();
}

/*Metodo que permite limpiar los componentes de insercion*/
void PantallaAgregarSucursal::limpiarDatos(){

    this->ui->textID->clear();
    this->ui->textNombre->clear();
    this->ui->textUbicacion->clear();
    this->ui->textITiempoIngreso->clear();
    this->ui->textTiempoDesapacho->clear();
    this->ui->textITiempoPreparacion->clear();
}

/*Metodo que permite limpiar los logs*/
void PantallaAgregarSucursal::limpiarLogs(){

    this->ui->textGrafo->clear();
    this->ui->labelTiempoGrafo->setText("Tiempo de insercion: 0 ms");
}


/*Metodo que permite validar las entradas*/
bool PantallaAgregarSucursal::validarCampos() {
    QString idStr = ui->textID->text();
    QString nombre = ui->textNombre->text();
    QString ubicacion = ui->textUbicacion->text();
    QString tIngreso = ui->textITiempoIngreso->text();
    QString tDespacho = ui->textTiempoDesapacho->text();
    QString tPreparacion = ui->textITiempoPreparacion->text();

    if (idStr.isEmpty() || nombre.isEmpty() || ubicacion.isEmpty() ||
        tIngreso.isEmpty() || tDespacho.isEmpty() || tPreparacion.isEmpty()) {
        return false;
    }

    bool okId;
    idStr.toInt(&okId);
    if (!okId) return false;

    bool ok1, ok2, ok3;
    tIngreso.toDouble(&ok1);
    tDespacho.toDouble(&ok2);
    tPreparacion.toDouble(&ok3);

    return (ok1 && ok2 && ok3);
}

void PantallaAgregarSucursal::appendGrafoLog(QString mensaje, QString color){

    this->ui->textGrafo->append(
        "<span style='color:" + color + ";'>" + mensaje + "</span>"
        );
}


/*---***--- Fin del Apartado de metodos que permiten comunicar a la UI los logs que se van a mostrar----***--*/


/*Metodo para poder dar el tiempo total en procesar una instruccion*/
void PantallaAgregarSucursal::mostrarTiempo( double milisegundos){

    QString tiempoTexto = "Tiempo de insercion: " + QString::number(milisegundos, 'f', 3) + " ms";

    this->ui->labelTiempoGrafo->setText( tiempoTexto);
}

/*Metodo que permite agregar una sucursal*/
void PantallaAgregarSucursal::on_btnAgregar_clicked()
{

    if (!validarCampos()) {
        QMessageBox::warning(this, "Campos invalidos",
                             "Por favor, revisa los campos. El ID debe ser entero y los tiempos numéricos.");
        return;
    }

    int id = ui->textID->text().trimmed().toInt();
    std::string nombre = ui->textNombre->text().trimmed().toStdString();
    std::string ubicacion = ui->textUbicacion->text().trimmed().toStdString();
    double ingreso = ui->textITiempoIngreso->text().trimmed().toDouble();
    double despacho = ui->textTiempoDesapacho->text().trimmed().toDouble();
    double preparacion = ui->textITiempoPreparacion->text().trimmed().toDouble();

    emit insertarSucursal(id,nombre,ubicacion,ingreso,despacho,preparacion);
}


void PantallaAgregarSucursal::on_btnLimpiar_clicked()
{
    this->limpiarDatos();
}


void PantallaAgregarSucursal::on_btnSucursales_clicked()
{
    emit verSucursales();
}

