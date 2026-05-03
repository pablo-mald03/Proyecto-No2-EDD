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
                             "Por favor, revisa los campos. Los tiempos deben ser numéricos.");
        return;
    }

    std::string id = ui->textID->text().trimmed().toStdString();
    std::string nombre = ui->textNombre->text().trimmed().toStdString();
    std::string ubicacion = ui->textUbicacion->text().trimmed().toStdString();
    double ingreso = ui->textITiempoIngreso->text().trimmed().toDouble();
    double despacho = ui->textTiempoDesapacho->text().trimmed().toDouble();
    double preparacion = ui->textITiempoPreparacion->text().trimmed().toDouble();

    emit insertarSucursal(id,nombre,ubicacion,ingreso,despacho,preparacion);
}

/*Metodo que permite inicializar los comboBox de asociacion de conexiones*/
void PantallaAgregarSucursal::inicializarCombos() {

    ui->comboOrigen->blockSignals(true);
    ui->comboDestino->blockSignals(true);
    ui->comboOrigen->clear();
    ui->comboDestino->clear();

    ui->comboDestino->addItem("Sucursal Central - Ciudad", "ID_001");
    ui->comboDestino->addItem("Sucursal Norte - Petén", "ID_002");
    ui->comboDestino->addItem("Sucursal Occidente - Xela", "ID_003");

    ui->comboOrigen->addItem("Sucursal Central - Ciudad", "ID_001");
    ui->comboOrigen->addItem("Sucursal Norte - Petén", "ID_002");
    ui->comboOrigen->addItem("Sucursal Occidente - Xela", "ID_003");

    ui->comboDestino->setCurrentIndex(-1);

    ui->comboDestino->blockSignals(false);

    ui->comboOrigen->setCurrentIndex(-1);

    ui->comboOrigen->blockSignals(false);
}

/*Signal que permite dar el mensaje al asociar una conexion*/
void PantallaAgregarSucursal::confirmarAsociacion(QString mensaje, bool estado){

    if(estado){
        QMessageBox::information(this, "Éxito",
                                 "Conexión asociada correctamente.");

        ui->textCostoTraspaso->clear();
        ui->textTraspaso->clear();
        ui->comboOrigen->setCurrentIndex(-1);
        ui->comboDestino->setCurrentIndex(-1);

    }else{
        QMessageBox::warning(this, "Ha ocurrido un error",
                                 mensaje);
    }
}


void PantallaAgregarSucursal::on_btnLimpiar_clicked()
{
    this->limpiarDatos();
}

/*Metodo que permite agregar una nueva sucursal*/
void PantallaAgregarSucursal::on_btnSucursales_clicked()
{
    emit verSucursales();
}

/*Metodo que permite validar las conexiones*/
bool PantallaAgregarSucursal::validarConexiones() {
    if (ui->comboOrigen->currentIndex() == -1 || ui->comboDestino->currentIndex() == -1) {
        QMessageBox::warning(this, "Error de Selección", "Debes seleccionar una sucursal de origen y una de destino.");
        return false;
    }

    if (ui->comboOrigen->currentData().toString() == ui->comboDestino->currentData().toString()) {
        QMessageBox::warning(this, "Error de Lógica", "No puedes conectar una sucursal con ella misma.");
        return false;
    }

    bool costoOk, tiempoOk;
    double costo = ui->textCostoTraspaso->text().toDouble(&costoOk);
    double tiempo = ui->textTraspaso->text().toDouble(&tiempoOk);

    if (!costoOk || !tiempoOk) {
        QMessageBox::warning(this, "Error Numérico", "El costo y el tiempo de traspaso deben ser valores numéricos.");
        return false;
    }

    if (costo < 0 || tiempo < 0) {
        QMessageBox::warning(this, "Error", "Los valores no pueden ser negativos.");
        return false;
    }

    return true;
}


/*Metodo que permite asociar una conexion entre sucursales*/
void PantallaAgregarSucursal::on_btnAsociar_clicked()
{

    if (!validarConexiones()) {
        return;
    }

    QString idOrigen = ui->comboOrigen->currentData().toString();
    QString idDestino = ui->comboDestino->currentData().toString();
    double costo = ui->textCostoTraspaso->text().trimmed().toDouble();
    double tiempo = ui->textTraspaso->text().trimmed().toDouble();

    emit asociarConexion(idOrigen.toStdString(),idDestino.toStdString(),tiempo,costo);
}

