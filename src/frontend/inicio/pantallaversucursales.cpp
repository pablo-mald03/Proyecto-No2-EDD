#include "pantallaversucursales.h"

#include "ui_pantallaversucursales.h"
#include <QDebug>
#include <QtMath>
#include<QMessageBox>
#include <QFileDialog>
#include <QProcess>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QDesktopServices>
#include <QUrl>

PantallaVerSucursales::PantallaVerSucursales(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaVerSucursales)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_StyledBackground, true);

    //Se aplica el estilo al contenedor padre
    this->setStyleSheet("QWidget#PantallaVerSucursales { "
                        "border-image: url(:/assets/fondo/GrafosBackground.png) 0 0 0 0 stretch stretch; "
                        "} ");

    escena = new QGraphicsScene(this);

    this->zoomView = new GraphicsViewZoom(this);
    this->zoomView->setScene(this->escena);

    this->ui->verticalLayout->replaceWidget(ui->graphicsView, this->zoomView);

    ui->graphicsView->hide();
}

/*Metodo que permite inicializar la red del grafo*/
void PantallaVerSucursales::inicializarRed(Grafo * referenciaGrafo){
    this->cargarGrafo(referenciaGrafo->getNodos(),referenciaGrafo->getMatriz());
    this->inicializarDatos(referenciaGrafo->getNodos());
}

/*Metodo que permite procesar el click y emitir el signal hacia el controlador*/
void PantallaVerSucursales::procesarClicNodo(QString id) {
    emit navegarASucursal(id.toStdString());
}

/*Destructor*/
PantallaVerSucursales::~PantallaVerSucursales()
{
    delete ui;
}

/*Metodo que permite dibujar los nodos*/
void PantallaVerSucursales::dibujarNodos(const std::vector<Sucursal*> &sucursales) {
    int totalNodos = sucursales.size();
    if (totalNodos == 0) return;

    double factorExpansion = 220.0;
    double anguloPaso = 1.3;

    for (int i = 0; i < totalNodos; ++i) {
        Sucursal* suc = sucursales[i];
        QString idQt = QString::fromStdString(suc->getId());
        QString nombreQt = QString::fromStdString(suc->getNombre());

        NodoGrafico *nodo = new NodoGrafico(idQt, nombreQt, QColor(0x3d5afe), false);

        double angulo = i * anguloPaso;
        double radio = factorExpansion * angulo;

        double x = radio * qCos(angulo);
        double y = radio * qSin(angulo);

        nodo->setPos(x, y);
        escena->addItem(nodo);
        nodosRenderizados.insert(idQt, nodo);
        connect(nodo, &NodoGrafico::seleccionado, this, &PantallaVerSucursales::procesarClicNodo);
    }
}

/*Metodo que permite dibujar las aristas del grafo desde la matriz de adyacencia*/
void PantallaVerSucursales::dibujarAristas(const std::vector<Sucursal*> &nodos,
                                           const std::vector<std::vector<Conexion*>> &matriz) {
    QPen penArista(Qt::lightGray, 2, Qt::SolidLine);

    int n = nodos.size();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            Conexion* conexion = matriz[i][j];

            if (conexion != nullptr && conexion->getExiste()) {
                QString idOrigen = QString::fromStdString(nodos[i]->getId());
                QString idDestino = QString::fromStdString(nodos[j]->getId());

                if (nodosRenderizados.contains(idOrigen) && nodosRenderizados.contains(idDestino)) {
                    NodoGrafico *u = nodosRenderizados[idOrigen];
                    NodoGrafico *v = nodosRenderizados[idDestino];

                    QGraphicsLineItem *linea = new QGraphicsLineItem(
                        u->pos().x(), u->pos().y(),
                        v->pos().x(), v->pos().y()
                        );

                    linea->setPen(penArista);
                    linea->setZValue(-1);
                    escena->addItem(linea);
                }
            }
        }
    }
}

//Metodo que permite mostrar el grafo
void PantallaVerSucursales::cargarGrafo(const std::vector<Sucursal*>& nodos,
                                            const std::vector<std::vector<Conexion*>>& matriz) {
    escena->clear();
    nodosRenderizados.clear();

    if (nodos.empty()) return;

    dibujarNodos(nodos);

    dibujarAristas(nodos, matriz);

    ui->graphicsView->setSceneRect(escena->itemsBoundingRect().adjusted(-50, -50, 50, 50));
}

/*Metodo que permite inicializar el comboBox*/
void PantallaVerSucursales::inicializarCombo(const std::vector<Sucursal*>& sucursales) {
    ui->comboBox->blockSignals(true);
    ui->comboBox->clear();

    for (Sucursal* suc : sucursales) {
        QString nombreVisible = QString::fromStdString(suc->getNombre());
        QString idOculto = QString::fromStdString(suc->getId());

        ui->comboBox->addItem(nombreVisible, idOculto);
    }

    ui->comboBox->setPlaceholderText("Seleccione una sucursal...");
    ui->comboBox->setCurrentIndex(-1);
    ui->comboBox->blockSignals(false);
}

/*Metodo que permite reiniciar el estado de los parametros*/
void PantallaVerSucursales::inicializarDatos(const std::vector<Sucursal*>& sucursales){

    this->codigoSeleccionado = "";
    this->inicializarCombo(sucursales);
}


/*Metodo que permite viajar a una sucursal*/
void PantallaVerSucursales::on_btnViajar_clicked()
{
    if(this->codigoSeleccionado.empty()){

        QMessageBox::warning(this, "Sucursal no seleccionada",
                             "Por favor selecciona la sucursal a la que quieres viajar.");
        return;
    }

    emit navegarASucursal(this->codigoSeleccionado );
}

/*Metodo que permite viajar a la sucursal*/
void PantallaVerSucursales::on_comboBox_currentIndexChanged(int index)
{
    if (index == -1) return;

    QString idSeleccionado = ui->comboBox->currentData().toString();

    if (idSeleccionado.isEmpty()) return;

    this->codigoSeleccionado = idSeleccionado.toStdString();

}

/*Metodo que permite generar el graphviz del arbol B*/
void PantallaVerSucursales::generarGraphviz(std::string graph){

    QString rutaImagen = QFileDialog::getSaveFileName(
        this,
        "Guardar arbol como imagen",
        "",
        "Imagen PNG (*.png)"
        );

    if (rutaImagen.isEmpty()) return;

    QFileInfo info(rutaImagen);
    QString rutaBase = info.absolutePath() + "/" + info.baseName();
    QString dotPath = rutaBase + ".dot";

    QFile file(dotPath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "No se pudo crear el archivo fuente (.dot) temporal.");
        return;
    }

    QTextStream out(&file);

    out << QString::fromStdString(graph);

    file.close();

#ifdef Q_OS_WIN
    QString programa = "C:/Program Files/Graphviz/bin/dot.exe";
#else
    QString programa = "dot";
#endif

    QProcess proceso;
    QStringList argumentos;
    argumentos << "-Tpng" << dotPath << "-o" << rutaImagen;

    proceso.start(programa, argumentos);

    if (!proceso.waitForFinished()) {
        QMessageBox::critical(this, "Error", "No se pudo ejecutar Graphviz.");
        return;
    }

    if (QFile::exists(rutaImagen)) {

        QMessageBox::information(this, "Exito",
                                 "Archivos generados correctamente:\n" +
                                     info.baseName() + ".png\n" +
                                     info.baseName() + ".dot");
        QDesktopServices::openUrl(QUrl::fromLocalFile(rutaImagen));

    } else {
        QString errorGraphviz = proceso.readAllStandardError();
        QMessageBox::critical(this, "Error", "Fallo la generacion de la imagen.\nDetalle:\n" + errorGraphviz);
    }
}

/*Metodo que permite descargar el graphviz del grafo*/
void PantallaVerSucursales::on_btnDescargar_clicked()
{
    emit solicitarGraphvizGrafo();
}

