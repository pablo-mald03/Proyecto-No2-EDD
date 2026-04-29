#include "pantallaprincipal.h"
#include "ui/ui_pantallaprincipal.h"
#include<QFileDialog>
#include<QFile>
#include<QTextStream>
#include<QMessageBox>

PantallaPrincipal::PantallaPrincipal(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaPrincipal)
    ,hayCsv(false)
{
    ui->setupUi(this);


    this->setAttribute(Qt::WA_StyledBackground, true);

    //Se aplica el estilo al contenedor padre
    this->setStyleSheet("QWidget#PantallaPrincipal { "
                        "border-image: url(:/assets/fondo/fondooverlay.png) 0 0 0 0 stretch stretch; "
                        "} ");

    this->ui->textEditCsv->setReadOnly(true);
    this->ui->textEditAvl->setReadOnly(true);
    this->ui->textEditB->setReadOnly(true);
    this->ui->textEditBMas->setReadOnly(true);
    this->ui->textEditLista->setReadOnly(true);
}

/*Destructor*/
PantallaPrincipal::~PantallaPrincipal()
{
    delete ui;
}


/*Metodo signal que permite guardar el csv*/
void PantallaPrincipal::recibirGuardadoCsv(const QString &contenido) {

    if (contenido.trimmed().isEmpty() || contenido.count('\n') <= 1) {
        QMessageBox::warning(this, "Sin datos para Exportar",
                             "No hay registros validos para guardar. El archivo esta vacio.");
        return;
    }

    QString nombreArchivo = QFileDialog::getSaveFileName(this,
                                                         "Guardar Archivo", "", "Archivos CSV (*.csv)");

    if (nombreArchivo.isEmpty()) return;

    QFile archivo(nombreArchivo);
    if (archivo.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream salida(&archivo);
        salida << contenido;
        archivo.close();

        QMessageBox::information(this, "Exito", "El archivo se ha guardado correctamente en:\n." + nombreArchivo);
        this->limpiarLogs();
        this->hayCsv = false;
        emit solicitarLimpieza();

    } else {
        QMessageBox::critical(this, "Error", "No se pudo escribir en el archivo.");
    }
}


/*Metodo que permite ejecutarse cuando se vuelva a seleccionar la vista de carga del csv*/
void PantallaPrincipal::refrescarPantallaCsv(bool estaCargado){

    if(!estaCargado){
        this->limpiarLogs();
    }
    else{
        this->ui->textEditCsv->clear();
    }
}

/*Metodo que permite limpiar los datos por cada vez que se vuelva a cargar un nuevo csv*/
void PantallaPrincipal::limpiarLogs(){

    this->ui->labelTiempoAvl->setText("Tiempo total: 0 ms");
    this->ui->labelTiempoB->setText("Tiempo total: 0 ms");
    this->ui->labelTiempoBMas->setText("Tiempo total: 0 ms");
    this->ui->labelTiempoLista->setText("Tiempo total: 0 ms");

    this->ui->textEditCsv->clear();
    this->ui->textEditLista->clear();
    this->ui->textEditAvl->clear();
    this->ui->textEditB->clear();
    this->ui->textEditBMas->clear();

}

/*Metodo que permite seleccionar el archivo csv*/
void PantallaPrincipal::on_btnCargar_clicked()
{ 
    QString fileName = QFileDialog::getOpenFileName(
        this,
        "Seleccionar CSV",
        "",
        "CSV Files (*.csv);;All Files (*)"
        );

    if(fileName.isEmpty()){
        return;
    }

    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        this->ui->textEditCsv->append("<span style='color:red;'>Error al abrir archivo</span>");
        return;
    }

    QTextStream in(&file);

    std::vector<QString> buffer;

    this->ui->textEditCsv->clear();


    while (!in.atEnd()) {
        QString line = in.readLine();
        line.remove('"');
        line = line.trimmed();
        buffer.push_back(line);
    }

    file.close();

    this->limpiarLogs();

    emit csvCargado(buffer);

}

/*----Apartado de metodos para verificar el log de errores-----*/

/*Metodo que permite verificar si hay errores para habilitar la opcion de cerrar el csv*/
void PantallaPrincipal::evaluarCierreCsv(bool evaluacion){
    this->ui->btnCerrar->setEnabled(evaluacion);
    this->hayCsv = evaluacion;
}

/*Metodo que permite verificar si hay errores para habilitar la descarga del log*/
void PantallaPrincipal::evaluarErrores(bool evaluacion){
    this->ui->btnErrores->setEnabled(evaluacion);
}

/*Metodo que permite solicitar la lista de errores para poder armar el errors.log*/
void PantallaPrincipal::logListoParaDescargar(const QString &contenido){
    this->descargarLogErrores(contenido);
}

/*Metodo de la clase que permite desplegar el dialog de descarga*/
void PantallaPrincipal::descargarLogErrores(const QString &contenido){

    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Guardar Log de Errores",
        "errors.log",
        "Log Files (*.log);;Text Files (*.txt)"
        );

    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << contenido;
        file.close();

        QMessageBox::information(
            this,
            "Exportación Exitosa",
            "El archivo de log se ha guardado correctamente en:\n" + fileName
            );

    } else {
        QMessageBox::critical(
            this,
            "Error de Archivo",
            "No se pudo crear el archivo. Verifique los permisos de escritura."
            );
    }
}

/*----Fin del apartado de metodos para verificar el log de errores-----*/

/*---***---Apartado de metodos que permiten comunicar a la UI los logs que se van a mostrar----***--*/

void PantallaPrincipal::appendLogCarga(QString mensaje, QString color){

    this->ui->textEditCsv->append(
        "<span style='color:" + color + ";'>" + mensaje + "</span>"
        );
}

void PantallaPrincipal::appendAvlLog(QString mensaje, QString color){

    this->ui->textEditAvl->append(
        "<span style='color:" + color + ";'>" + mensaje + "</span>"
        );
}


void PantallaPrincipal::appendBLog(QString mensaje, QString color){

    this->ui->textEditB->append(
        "<span style='color:" + color + ";'>" + mensaje + "</span>"
        );
}

void PantallaPrincipal::appendBMasLog(QString mensaje, QString color){

    this->ui->textEditBMas->append(
        "<span style='color:" + color + ";'>" + mensaje + "</span>"
        );
}

void PantallaPrincipal::appendListLog(QString mensaje, QString color){

    this->ui->textEditLista->append(
        "<span style='color:" + color + ";'>" + mensaje + "</span>"
        );
}


/*---***--- Fin del Apartado de metodos que permiten comunicar a la UI los logs que se van a mostrar----***--*/


/*Metodo para poder dar el tiempo total en procesar una instruccion
*
* 1 -> AVL
* 2 -> B
* 3 -> B+
* 4 -> LISTA
*
*/
void PantallaPrincipal::mostrarTiempo(int estructura, double milisegundos){

    QString tiempoTexto = "Tiempo total: " + QString::number(milisegundos, 'f', 3) + " ms";

    switch(estructura){

        case 1:
        this->ui->labelTiempoAvl->setText(tiempoTexto);
            break;

        case 2:
            this->ui->labelTiempoB->setText( tiempoTexto);
            break;

        case 3:
            this->ui->labelTiempoBMas->setText( tiempoTexto);
            break;

        case 4:
            this->ui->labelTiempoLista->setText(tiempoTexto);
            break;
    }

}

//Metodo que permite descargar el log de errores
void PantallaPrincipal::on_btnErrores_clicked()
{
    emit solicitarLogErrores();
}


/*Metodo que permite exportar el archivo*/
void PantallaPrincipal::on_btnExportar_clicked()
{
    emit solicitarGuardarCsv();
}

/*Metodo que permite cerrar el archivo csv cargado*/
void PantallaPrincipal::on_btnCerrar_clicked()
{
    if (!this->hayCsv) {
        QMessageBox::warning(this, "Exportar", "No hay datos cargados desde un .csv para exportar.");
        return;
    }

    QMessageBox::StandardButton respuesta;
    respuesta = QMessageBox::question(this,
                                      "Cerrar CSV",
                                      "¿Desea guardar los cambios en el archivo antes de cerrar?"
                                      ,QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

    if (respuesta == QMessageBox::Yes) {
        this->on_btnExportar_clicked();
    }
    else if (respuesta == QMessageBox::No) {
        this->limpiarLogs();
        this->hayCsv = false;
        emit solicitarLimpieza();
    }
}

