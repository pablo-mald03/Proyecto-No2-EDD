#include "pantallacargasucursales.h"
#include "ui_pantallacargasucursales.h"
#include<QFileDialog>
#include<QFile>
#include<QTextStream>
#include<QMessageBox>

PantallaCargaSucursales::PantallaCargaSucursales(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaCargaSucursales),
    cargarSucursales(true)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_StyledBackground, true);

    //Se aplica el estilo al contenedor padre
    this->setStyleSheet("QWidget#PantallaCargaSucursales { "
                        "border-image: url(:/assets/fondo/GrafosBackground.png) 0 0 0 0 stretch stretch; "
                        "} ");

    this->setCargaSucursales(true,"Log del Grafo de sucursales");
}


/*Destructor*/
PantallaCargaSucursales::~PantallaCargaSucursales()
{
    delete ui;
}

/*Metodo que permite limpiar los datos por cada vez que se vuelva a cargar un nuevo csv*/
void PantallaCargaSucursales::limpiarLogs(){

    this->ui->labelTiempoGrafo->setText("Tiempo total: 0 ms");

    this->ui->textEditCsv->clear();
    this->ui->textGrafo->clear();
}

/*Metodo que permite ir intercalando entre cargar sucursales y conexiones*/
void PantallaCargaSucursales::setCargaSucursales(bool carga,QString placeHolder){
    this->cargarSucursales = carga;
    this->ui->btnCargaSucursales->setEnabled(!this->cargarSucursales);
    this->ui->btnCargaConexiones->setEnabled(this->cargarSucursales);
    this->ui->textGrafo->setPlaceholderText( placeHolder);
}

/*Boton que permite cargar las sucursales*/
void PantallaCargaSucursales::on_btnCargaSucursales_clicked()
{
    this->setCargaSucursales(true,"Log del Grafo de sucursales");
}

/*Boton que permite cargar las conexiones*/
void PantallaCargaSucursales::on_btnCargaConexiones_clicked()
{

    this->setCargaSucursales(false,"Log de las conexiones entre sucursales");
}

/*Metodo utilizado para cargar archivos .csv*/
std::vector<std::vector<QString>> PantallaCargaSucursales::parsearCSV(const QString &contenido) {
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

/*Metodo para poder agregar texto al log de carga*/
void PantallaCargaSucursales::appendLogCarga(QString mensaje, QString color){

    this->ui->textEditCsv->append(
        "<span style='color:" + color + ";'>" + mensaje + "</span>"
        );
}

void PantallaCargaSucursales::appendGrafoLog(QString mensaje, QString color){

    this->ui->textGrafo->append(
        "<span style='color:" + color + ";'>" + mensaje + "</span>"
        );
}

void PantallaCargaSucursales::mostrarTiempo(int estructura, double milisegundos){

    QString tiempoTexto = "Tiempo total: " + QString::number(milisegundos, 'f', 3) + " ms";

    this->ui->labelTiempoGrafo->setText(tiempoTexto);
}

/*Metodo que permite cargar archivos csv*/
void PantallaCargaSucursales::on_btnCargar_clicked()
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


    if(this->cargarSucursales){
        emit csvSucursalesCargado(datos);
    }else{
        emit csvConexionesCargado(datos);
    }

}

