#include "pantallacargaenvios.h"
#include "ui_pantallacargaenvios.h"

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


/*Destructor*/
PantallaCargaEnvios::~PantallaCargaEnvios()
{
    delete ui;
}

void PantallaCargaEnvios::on_btnCargar_clicked()
{

}

