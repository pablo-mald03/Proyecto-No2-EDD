#include "pantallacargaproductos.h"
#include "ui_pantallacargaproductos.h"
#include<QFileDialog>
#include<QFile>
#include<QTextStream>
#include<QMessageBox>

PantallaCargaProductos::PantallaCargaProductos(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaCargaProductos)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_StyledBackground, true);

    //Se aplica el estilo al contenedor padre
    this->setStyleSheet("QWidget#PantallaCargaProductos { "
                        "border-image: url(:/assets/fondo/GrafosBackground.png) 0 0 0 0 stretch stretch; "
                        "} ");
}




/*Metodo que permite limpiar los datos por cada vez que se vuelva a cargar un nuevo csv*/
void PantallaCargaProductos::limpiarLogs(){

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
/*
/*Metodo que permite seleccionar el archivo csv
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
*/
/*----Apartado de metodos para verificar el log de errores-----*/


/*Metodo que permite verificar si hay errores para habilitar la descarga del log*/
void PantallaCargaProductos::evaluarErrores(bool evaluacion){
    this->ui->btnErrores->setEnabled(evaluacion);
}

/*Metodo que permite solicitar la lista de errores para poder armar el errors.log*/
void PantallaCargaProductos::logListoParaDescargar(const QString &contenido){
    this->descargarLogErrores(contenido);
}

/*Metodo de la clase que permite desplegar el dialog de descarga*/
void PantallaCargaProductos::descargarLogErrores(const QString &contenido){

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

void PantallaCargaProductos::appendLogCarga(QString mensaje, QString color){

    this->ui->textEditCsv->append(
        "<span style='color:" + color + ";'>" + mensaje + "</span>"
        );
}

void PantallaCargaProductos::appendAvlLog(QString mensaje, QString color){

    this->ui->textEditAvl->append(
        "<span style='color:" + color + ";'>" + mensaje + "</span>"
        );
}


void PantallaCargaProductos::appendBLog(QString mensaje, QString color){

    this->ui->textEditB->append(
        "<span style='color:" + color + ";'>" + mensaje + "</span>"
        );
}

void PantallaCargaProductos::appendBMasLog(QString mensaje, QString color){

    this->ui->textEditBMas->append(
        "<span style='color:" + color + ";'>" + mensaje + "</span>"
        );
}

void PantallaCargaProductos::appendListLog(QString mensaje, QString color){

    this->ui->textEditLista->append(
        "<span style='color:" + color + ";'>" + mensaje + "</span>"
        );
}

void PantallaCargaProductos::appendHashLog(QString mensaje, QString color){

    this->ui->textTablaHash->append(
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
* 5 -> HASH
*
*/
void PantallaCargaProductos::mostrarTiempo(int estructura, double milisegundos){

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
    case 5:
        this->ui->labelTiempoHash->setText(tiempoTexto);
        break;
    }

}

/*Metodo utilizado para cargar archivos .csv*/
std::vector<std::vector<QString>> PantallaCargaProductos::parsearCSV(const QString &contenido) {
    std::vector<std::vector<QString>> matrizDatos;
    const QStringList lineas = contenido.split('\n');

    for (const QString &linea : lineas) {
        if (linea.trimmed().isEmpty()) continue;

        std::vector<QString> fila;
        QString celda;
        bool dentroDeComillas = false;

        for (int i = 0; i < linea.length(); ++i) {
            QChar caracterActual = linea[i];

            if (caracterActual == '"') {
                dentroDeComillas = !dentroDeComillas;
            } else if (caracterActual == ',' && !dentroDeComillas) {
                fila.push_back(celda.trimmed());
                celda.clear();
            } else {
                celda.append(caracterActual);
            }
        }
        fila.push_back(celda.trimmed());
        matrizDatos.push_back(fila);
    }
    return matrizDatos;
}


/*Destructor*/
PantallaCargaProductos::~PantallaCargaProductos()
{
    delete ui;
}

/*Metodo que permite solicitar el log de errores*/
void PantallaCargaProductos::on_btnErrores_clicked()
{
    emit solicitarLogErrores();
}

