#include "pantallacargaenvios.h"
#include "ui_pantallacargaenvios.h"
#include<QFileDialog>
#include<QFile>
#include<QTextStream>
#include<QMessageBox>

PantallaCargaEnvios::PantallaCargaEnvios(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaCargaEnvios)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_StyledBackground, true);

    //Se aplica el estilo al contenedor padre
    this->setStyleSheet("QWidget#PantallaCargaEnvios { "
                        "border-image: url(:/assets/fondo/GrafosBackground.png) 0 0 0 0 stretch stretch; "
                        "} ");
}

/*Metodo para poder agregar texto al log de carga*/
void PantallaCargaEnvios::appendLogCarga(QString mensaje, QString color){

    this->ui->textEditCsv->append(
        "<span style='color:" + color + ";'>" + mensaje + "</span>"
        );
}

void PantallaCargaEnvios::appendGrafoLog(QString mensaje, QString color){

    this->ui->textGrafo->append(
        "<span style='color:" + color + ";'>" + mensaje + "</span>"
        );
}

void PantallaCargaEnvios::mostrarTiempo(int estructura, double milisegundos){

    QString tiempoTexto = "Tiempo total: " + QString::number(milisegundos, 'f', 3) + " ms";

    this->ui->labelTiempoGrafo->setText(tiempoTexto);
}

/*Metodo que permite verificar si hay errores para habilitar la descarga del log*/
void PantallaCargaEnvios::evaluarErrores(bool evaluacion){
    this->ui->btnErrores->setEnabled(evaluacion);
}

/*Metodo que permite solicitar la lista de errores para poder armar el errors.log*/
void PantallaCargaEnvios::logListoParaDescargar(const QString &contenido){
    this->descargarLogErrores(contenido);
}

/*Metodo de la clase que permite desplegar el dialog de descarga*/
void PantallaCargaEnvios::descargarLogErrores(const QString &contenido){

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

/*Metodo utilizado para cargar archivos .csv*/
std::vector<std::vector<QString>> PantallaCargaEnvios::parsearCSV(const QString &contenido) {
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

/*Metodo que permite limpiar los datos por cada vez que se vuelva a cargar un nuevo csv*/
void PantallaCargaEnvios::limpiarLogs(){

    this->ui->labelTiempoGrafo->setText("Tiempo total: 0 ms");

    this->ui->textEditCsv->clear();
    this->ui->textGrafo->clear();
}


/*Destructor*/
PantallaCargaEnvios::~PantallaCargaEnvios()
{
    delete ui;
}

/*Metodo que permite poder cargar el csv de envios*/
void PantallaCargaEnvios::on_btnCargar_clicked()
{

    QString fileName = QFileDialog::getOpenFileName(this, "Seleccionar CSV", "", "CSV Files (*.csv);;All Files (*)");

    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        ui->textEditCsv->append("<span style='color:red;'>Error al abrir archivo</span>");
        return;
    }

    QString contenido = QTextStream(&file).readAll();
    file.close();

    ui->textEditCsv->clear();
    this->limpiarLogs();

    std::vector<std::vector<QString>> datos = parsearCSV(contenido);

    emit csvEnviosCargado(datos);
}

/*Metodo que permite descargar el log de errores*/
void PantallaCargaEnvios::on_btnErrores_clicked()
{
    emit solicitarLogErrores();
}

