#include "pantallabuscarcodigo.h"
#include "ui_pantallabuscarcodigo.h"
#include<QMessageBox>

PantallaBuscarCodigo::PantallaBuscarCodigo(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaBuscarCodigo)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_StyledBackground, true);

    //Se aplica el estilo al contenedor padre
    this->setStyleSheet("QWidget#PantallaBuscarCodigo { "
                        "border-image: url(:/assets/fondo/fondooverlay.png) 0 0 0 0 stretch stretch; "
                        "} ");

    this->ui->textTablaHash->setReadOnly(true);
    this->ui->textListaOrdenada->setReadOnly(true);
    this->ui->textListaNoOrdenada->setReadOnly(true);
}

/*Destructor*/
PantallaBuscarCodigo::~PantallaBuscarCodigo()
{
    delete ui;
}

/*---***---Apartado de metodos que permiten comunicar a la UI los logs que se van a mostrar----***--*/
void PantallaBuscarCodigo::appendHashLog(QString mensaje, QString color){

    QString htmlMensaje = mensaje.replace("\n", "<br>");

    this->ui->textTablaHash->append(
        "<span style='color:" + color + ";'>" + htmlMensaje + "</span>"
        );
}

void PantallaBuscarCodigo::appendListOrdenadaLog(QString mensaje, QString color){

    QString htmlMensaje = mensaje.replace("\n", "<br>");

    this->ui->textListaOrdenada->append(
        "<span style='color:" + color + ";'>" + htmlMensaje + "</span>"
        );
}

void PantallaBuscarCodigo::appendListNoOrdenadaLog(QString mensaje, QString color){

    QString htmlMensaje = mensaje.replace("\n", "<br>");

    this->ui->textListaNoOrdenada->append(
        "<span style='color:" + color + ";'>" + htmlMensaje + "</span>"
        );
}


/*---***--- Fin del Apartado de metodos que permiten comunicar a la UI los logs que se van a mostrar----***--*/


/*Metodo para poder dar el tiempo total en procesar una instruccion
*
* 1 -> HASH
* 2 -> LISTA ORDENADA
* 3 -> LISTA NO ORDENADA
*
*/
void PantallaBuscarCodigo::mostrarTiempo(int estructura, double milisegundos){

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
    }

}

/*Metodo que permite mostrar el tiempo que tomo hacer las pruebas*/
void PantallaBuscarCodigo::mostrarTiempoPruebas(double milisegundos){

    QString tiempoTexto = "Promedio de consultas: " + QString::number(milisegundos, 'f', 3) + " ms";

    this->ui->labelPromedio->setText(tiempoTexto);
}

/*Metodo que permite limpiar los componentes de insercion*/
void PantallaBuscarCodigo::limpiarDatos(){

    this->ui->textCodigo->clear();
    this->ui->textVeces->clear();
    this->ui->textConsulta->clear();
}

/*Metodo que permite limpiar los logs*/
void PantallaBuscarCodigo::limpiarLogs(){

    this->ui->textTablaHash->clear();
    this->ui->textListaNoOrdenada->clear();
    this->ui->textListaOrdenada->clear();

    this->ui->labelTiempoNoOrdenada->setText("Tiempo de busqueda: 0 ms");
    this->ui->labelTiempoOrdenada->setText("Tiempo de busqueda: 0 ms");
    this->ui->labelTiempoHash->setText("Tiempo de busqueda: 0 ms");
    this->ui->labelPromedio->setText("Promedio de consultas: 0 ms");

}

/*Metodo signal que permite limpiar los datos de una pantalla*/
void PantallaBuscarCodigo::limpiarPantalla(){
    this->limpiarDatos();
    this->limpiarLogs();
}

/*Metodo que permite validar los campos de entrada*/
bool PantallaBuscarCodigo::validarPruebas(int &consultas, int &veces){

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

/*Metodo que permite buscar un producto por codigo*/
void PantallaBuscarCodigo::on_btnBuscar_clicked()
{

    this->limpiarLogs();

    QString codigoOriginal = ui->textCodigo->text();
    QString codigoLimpio = codigoOriginal.trimmed();

    if (codigoLimpio.isEmpty()) {

        QMessageBox::warning(
            this,
            "Campo requerido",
            "Ingrese un codigo valido (no puede esta vacio)."
            );

        return;
    }

    emit buscarPorCodigo(codigoLimpio.toStdString());
}

/*Metodo que permite limpiar datos*/
void PantallaBuscarCodigo::on_btnLimpiar_clicked()
{
    this->limpiarDatos();
    this->limpiarLogs();
}

/*Metotdo que permite viajar para ver los arboles*/
void PantallaBuscarCodigo::on_btnVerArboles_clicked()
{
    emit verArboles();
}

/*Metodo que genera pruebas aleatorias*/
void PantallaBuscarCodigo::on_btnAleatorio_clicked()
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

/*Metodo que genera pruebas en extremos*/
void PantallaBuscarCodigo::on_btnExtremos_clicked()
{

    int veces = 0;
    int consultas = 0;

    bool validarEntradas = validarPruebas(consultas,veces);

    if(!validarEntradas){
        return;
    }

    this->limpiarLogs();

    emit pruebaExtremos(consultas, veces);
}

