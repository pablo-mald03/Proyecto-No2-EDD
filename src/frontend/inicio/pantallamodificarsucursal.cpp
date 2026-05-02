#include "pantallamodificarsucursal.h"
#include "ui_pantallamodificarsucursal.h"
#include<QMessageBox>

PantallaModificarSucursal::PantallaModificarSucursal(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaModificarSucursal)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_StyledBackground, true);

    //Se aplica el estilo al contenedor padre
    this->setStyleSheet("QWidget#PantallaModificarSucursal { "
                        "border-image: url(:/assets/fondo/GrafosBackground.png) 0 0 0 0 stretch stretch; "
                        "} ");

    this->ui->textGrafo->setReadOnly(true);
    ui->textID->setReadOnly(true);
}

/*Destructor*/
PantallaModificarSucursal::~PantallaModificarSucursal()
{
    delete ui;
}


/*Metodo signal que permite limpiar los datos de una pantalla*/
void PantallaModificarSucursal::limpiarPantalla(){
    this->limpiarDatos();
    this->limpiarLogs();
}

/*Metodo que permite limpiar los componentes de insercion*/
void PantallaModificarSucursal::limpiarDatos(){

    this->ui->textID->clear();
    this->ui->textNombre->clear();
    this->ui->textUbicacion->clear();
    this->ui->textITiempoIngreso->clear();
    this->ui->textTiempoDesapacho->clear();
    this->ui->textITiempoPreparacion->clear();
}

/*Metodo que permite limpiar los logs*/
void PantallaModificarSucursal::limpiarLogs(){

    this->ui->textGrafo->clear();
    this->ui->labelTiempoGrafo->setText("Tiempo de insercion: 0 ms");
}


/*Metodo que permite validar las entradas*/
bool PantallaModificarSucursal::validarCampos() {
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

    bool ok1, ok2, ok3;
    tIngreso.toDouble(&ok1);
    tDespacho.toDouble(&ok2);
    tPreparacion.toDouble(&ok3);

    return (ok1 && ok2 && ok3);
}

void PantallaModificarSucursal::appendGrafoLog(QString mensaje, QString color){

    this->ui->textGrafo->append(
        "<span style='color:" + color + ";'>" + mensaje + "</span>"
        );
}


/*---***--- Fin del Apartado de metodos que permiten comunicar a la UI los logs que se van a mostrar----***--*/


/*Metodo para poder dar el tiempo total en procesar una instruccion*/
void PantallaModificarSucursal::mostrarTiempo( double milisegundos){

    QString tiempoTexto = "Tiempo de insercion: " + QString::number(milisegundos, 'f', 3) + " ms";

    this->ui->labelTiempoGrafo->setText( tiempoTexto);
}

/*Metodo que permite dar la signal para modificar una sucursal*/
void PantallaModificarSucursal::on_btnModificar_clicked()
{

    if (!validarCampos()) {
        QMessageBox::warning(this, "Campos invalidos",
                             "Por favor, revisa los campos. Los tiempos deben ser numéricos.");
        return;
    }

    std::string id = ui->textID->text().trimmed().toStdString();
    std::string nombre = ui->textNombre->text().trimmed().toStdString();
    std::string ubicacion = ui->textUbicacion->text().trimmed().toStdString();
    double ingreso = ui->textITiempoIngreso->text().trimmed().toDouble();
    double despacho = ui->textTiempoDesapacho->text().trimmed().toDouble();
    double preparacion = ui->textITiempoPreparacion->text().trimmed().toDouble();

    emit modificarSucursal(id,nombre,ubicacion,ingreso,despacho,preparacion);
}

void PantallaModificarSucursal::inicializarCombo() {

    ui->comboBox->blockSignals(true);
    ui->comboBox->clear();

    ui->comboBox->addItem("Sucursal Central - Ciudad", "ID_001");
    ui->comboBox->addItem("Sucursal Norte - Petén", "ID_002");
    ui->comboBox->addItem("Sucursal Occidente - Xela", "ID_003");

    ui->comboBox->setCurrentIndex(-1);

    ui->comboBox->blockSignals(false);
}

/*METODO PROVISIONAL*/
Sucursal PantallaModificarSucursal::buscarEnHashHardcoded(QString id) {
    Sucursal s;
    if (id == "ID_001") {
        s = {"ID_001", "Sucursal Central", "Ciudad de Guatemala"};
    } else if (id == "ID_002") {
        s = {"ID_002", "Sucursal Norte", "Flores, Petén"};
    } else {
        s = {"ID_003", "Sucursal Occidente", "Quetzaltenango"};
    }
    return s;
}

/*Metodo que permite quitar la seleccion de la sucursal*/
void PantallaModificarSucursal::on_btnQuitar_clicked()
{
     this->limpiarDatos();
}

/*Evento que permite detectar que opcion de clickeo*/
void PantallaModificarSucursal::on_comboBox_currentIndexChanged(int index)
{

    if (index == -1) return;

    QString idSeleccionado = ui->comboBox->currentData().toString();

    if (idSeleccionado.isEmpty()) return;

    Sucursal datos = buscarEnHashHardcoded(idSeleccionado);

    ui->textID->setText(datos.id);
    ui->textNombre->setText(datos.nombre);
    ui->textUbicacion->setText(datos.ubicacion);

    ui->textID->setReadOnly(true);

}

/*Metodo que permite ver las sucursales*/
void PantallaModificarSucursal::on_btnSucursales_clicked()
{
    emit verSucursales();
}

/*Metodo que permite limpiar los datos*/
void PantallaModificarSucursal::on_btnLimpiar_clicked()
{
    this->limpiarDatos();
}

