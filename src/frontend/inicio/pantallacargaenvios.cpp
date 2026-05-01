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

