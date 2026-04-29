#include "pantallaagregar.h"
#include "ui_pantallaagregar.h"
#include<QMessageBox>

PantallaAgregar::PantallaAgregar(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaAgregar)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_StyledBackground, true);

    //Se aplica el estilo al contenedor padre
    this->setStyleSheet("QWidget#PantallaAgregar { "
                        "border-image: url(:/assets/fondo/fondooverlay.png) 0 0 0 0 stretch stretch; "
                        "} ");

    this->ui->dateExpiracion->setCalendarPopup(true);
    this->ui->dateExpiracion->setDate(QDate::currentDate());

    this->ui->textArbolAvl->setReadOnly(true);
    this->ui->textArbolB->setReadOnly(true);
    this->ui->textArbolBMas->setReadOnly(true);
    this->ui->textEditListNoOrdenada->setReadOnly(true);
    this->ui->textEditListOrdenada->setReadOnly(true);
}

/*Destructor*/
PantallaAgregar::~PantallaAgregar()
{
    delete ui;
}


/*---***---Apartado de metodos que permiten comunicar a la UI los logs que se van a mostrar----***--*/
void PantallaAgregar::appendAvlLog(QString mensaje, QString color){

    this->ui->textArbolAvl->append(
        "<span style='color:" + color + ";'>" + mensaje + "</span>"
        );
}


void PantallaAgregar::appendBLog(QString mensaje, QString color){

    this->ui->textArbolB->append(
        "<span style='color:" + color + ";'>" + mensaje + "</span>"
        );
}

void PantallaAgregar::appendBMasLog(QString mensaje, QString color){

    this->ui->textArbolBMas->append(
        "<span style='color:" + color + ";'>" + mensaje + "</span>"
        );
}

void PantallaAgregar::appendListOrdenadaLog(QString mensaje, QString color){

    this->ui->textEditListOrdenada->append(
        "<span style='color:" + color + ";'>" + mensaje + "</span>"
        );
}

void PantallaAgregar::appendListNoOrdenadaLog(QString mensaje, QString color){

    this->ui->textEditListNoOrdenada->append(
        "<span style='color:" + color + ";'>" + mensaje + "</span>"
        );
}


/*---***--- Fin del Apartado de metodos que permiten comunicar a la UI los logs que se van a mostrar----***--*/


/*Metodo para poder dar el tiempo total en procesar una instruccion
*
* 1 -> AVL
* 2 -> B
* 3 -> B+
* 4 -> LISTA ORDENADA
* 5 -> LISTA NO ORDENADA
*
*/
void PantallaAgregar::mostrarTiempo(int estructura, double milisegundos){

    QString tiempoTexto = "Tiempo de insercion: " + QString::number(milisegundos, 'f', 3) + " ms";

    switch(estructura){

    case 1:
        this->ui->labelTiempoAvl->setText(tiempoTexto);
        break;

    case 2:
        this->ui->labelTiempoB->setText(tiempoTexto);
        break;

    case 3:
        this->ui->labelTiempoBMas->setText( tiempoTexto);
        break;

    case 4:
        this->ui->labelTiempoListOrdenada->setText( tiempoTexto);
        break;
    case 5:
        this->ui->labelTiempoListNoOrdenada->setText(tiempoTexto );
        break;
    }

}

/*Metodo utilizado para poder validar los datos*/
bool PantallaAgregar::validarCampos() {
    struct Campo {
        QLineEdit* widget;
        QString nombre;
    };

    QList<Campo> campos = {
        {ui->textNombre, "Nombre"},
        {ui->textBarra, "Codigo de Barras"},
        {ui->textCategoria, "Categoría"},
        {ui->textMarca, "Marca"},
        {ui->textPrecio, "Precio"},
        {ui->textStock, "Stock"}
    };

    for (const auto& campo : campos) {
        if (campo.widget->text().trimmed().isEmpty()) {
            QMessageBox::warning(this, "Campo Obligatorio",
                                 "El campo <b>" + campo.nombre + "</b> no puede estar vacio.");
            campo.widget->setFocus();
            return false;
        }
    }

    return true;
}


/*Metodo que permite insertar un producto nuevo en todas las estructuras*/
void PantallaAgregar::on_btnAgregar_clicked()
{
    this->limpiarLogs();

    if (!validarCampos()) {
        return;
    }

    std::string nombre = this->ui->textNombre->text().trimmed().toStdString();
    std::string barra = this->ui->textBarra->text().trimmed().toStdString();
    std::string categoria = this->ui->textCategoria->text().trimmed().toStdString();
    std::string marca = this->ui->textMarca->text().trimmed().toStdString();
    std::string precio = this->ui->textPrecio->text().trimmed().toStdString();
    std::string stock = this->ui->textStock->text().trimmed().toStdString();
    std::string fecha = this->ui->dateExpiracion->date().toString("yyyy-MM-dd").trimmed().toStdString();

    emit insertarProducto(nombre, barra, categoria,fecha,marca,precio,stock);
}

/*Metodo que permite ir a ver el estado de los arboles*/
void PantallaAgregar::on_btnVerArboles_clicked()
{
    emit verArboles();
}

/*Metodo signal que permite limpiar los datos de una pantalla*/
void PantallaAgregar::limpiarPantalla(){
    this->limpiarDatos();
    this->limpiarLogs();
}


/*Metodo que permite limpiar los componentes de insercion*/
void PantallaAgregar::limpiarDatos(){

    this->ui->textNombre->clear();
    this->ui->textBarra->clear();
    this->ui->textMarca->clear();
    this->ui->textStock->clear();
    this->ui->textCategoria->clear();
    this->ui->textPrecio->clear();
    this->ui->dateExpiracion->setDate(QDate::currentDate());
}

/*Metodo que permite limpiar los logs*/
void PantallaAgregar::limpiarLogs(){

    this->ui->textArbolB->clear();
    this->ui->textArbolAvl->clear();
    this->ui->textArbolBMas->clear();
    this->ui->textEditListNoOrdenada->clear();
    this->ui->textEditListOrdenada->clear();

    this->ui->labelTiempoListNoOrdenada->setText("Tiempo de insercion: 0 ms");
    this->ui->labelTiempoListOrdenada->setText("Tiempo de insercion: 0 ms");
    this->ui->labelTiempoAvl->setText("Tiempo de insercion: 0 ms");
    this->ui->labelTiempoB->setText("Tiempo de insercion: 0 ms");
    this->ui->labelTiempoBMas->setText("Tiempo de insercion: 0 ms");
}

/*Metodo del boton para limpiar*/
void PantallaAgregar::on_btnLimpiar_clicked()
{
    this->limpiarDatos();
}

/*Metodo que permite limpiar los logs*/
void PantallaAgregar::on_btnLimpiarLogs_clicked()
{
    this->limpiarLogs();
}

