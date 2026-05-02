#include "pantallaversucursales.h"
#include "ui_pantallaversucursales.h"
#include <QDebug>
#include <QtMath>
#include<QMessageBox>

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

    renderizarGrafoPrueba();
}

/*Metodo que permite procesar el click y emitir el signal hacia el controlador*/
void PantallaVerSucursales::procesarClicNodo(QString id) {
    qDebug() << "Navegando hacia los inventarios de la sucursal:" << id;
    emit navegarASucursal(id.toStdString());
}

/*Destructor*/
PantallaVerSucursales::~PantallaVerSucursales()
{
    delete ui;
}

/*Metodo que permite dibujar los nodos*/
void PantallaVerSucursales::dibujarNodos(const QList<SucursalMock> &sucursales) {
    int totalNodos = sucursales.size();
    int radioCirculo = 150; // Qué tan separadas estarán las bolitas

    for (int i = 0; i < totalNodos; ++i) {
        SucursalMock suc = sucursales[i];

        NodoGrafico *nodo = new NodoGrafico(suc.id, suc.nombre, QColor(0x3d5afe), false);

        double angulo = (2.0 * M_PI * i) / totalNodos;
        double x = radioCirculo * qCos(angulo);
        double y = radioCirculo * qSin(angulo);
        nodo->setPos(x, y);

        escena->addItem(nodo);
        nodosRenderizados.insert(suc.id, nodo);
        connect(nodo, &NodoGrafico::seleccionado, this, &PantallaVerSucursales::procesarClicNodo);
    }
}

/*Metodo que permite dibujar las aristas del grafo*/
void PantallaVerSucursales::dibujarAristas(const QList<ConexionMock> &conexiones) {
    QPen penArista(Qt::lightGray, 3, Qt::SolidLine);

    for (const ConexionMock &conexion : conexiones) {
        if (nodosRenderizados.contains(conexion.origenId) && nodosRenderizados.contains(conexion.destinoId)) {

            NodoGrafico *origen = nodosRenderizados[conexion.origenId];
            NodoGrafico *destino = nodosRenderizados[conexion.destinoId];

            QGraphicsLineItem *linea = new QGraphicsLineItem(
                origen->pos().x(), origen->pos().y(),
                destino->pos().x(), destino->pos().y()
                );

            linea->setPen(penArista);
            linea->setZValue(0);
            escena->addItem(linea);
        } else {
            qDebug() << "Error: Se intentó conectar un nodo que no está renderizado.";
        }
    }
}

// Método temporal para probar todo
void PantallaVerSucursales::renderizarGrafoPrueba() {
    escena->clear();
    nodosRenderizados.clear();

    QList<SucursalMock> listaSucursales = {
        {"101", "Central"}, {"102", "Norte"}, {"103", "Sur"}, {"104", "Este"}
    };

    QList<ConexionMock> listaConexiones = {
        {"101", "102"}, {"101", "103"}, {"102", "104"}, {"103", "104"}
    };

    dibujarNodos(listaSucursales);
    dibujarAristas(listaConexiones);
}

/*Metodo que permite inicializar el comboBox*/
void PantallaVerSucursales::inicializarCombo() {

    ui->comboBox->blockSignals(true);
    ui->comboBox->clear();

    ui->comboBox->addItem("Sucursal Central - Ciudad", "ID_001");
    ui->comboBox->addItem("Sucursal Norte - Petén", "ID_002");
    ui->comboBox->addItem("Sucursal Occidente - Xela", "ID_003");

    ui->comboBox->setCurrentIndex(-1);

    ui->comboBox->blockSignals(false);
}

/*METODO PROVISIONAL*/
SucursalMock PantallaVerSucursales::buscarEnHashHardcoded(QString id) {
    SucursalMock s;
    if (id == "ID_001") {
        s = {"ID_001", "Sucursal Central"};
    } else if (id == "ID_002") {
        s = {"ID_002", "Sucursal Norte"};
    } else {
        s = {"ID_003", "Sucursal Occidente"};
    }
    return s;
}

/*Metodo que permite reiniciar el estado de los parametros*/
void PantallaVerSucursales::inicializarDatos(){

    this->codigoSeleccionado = "";
    this->inicializarCombo();
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

    SucursalMock datos = buscarEnHashHardcoded(idSeleccionado);

    this->codigoSeleccionado = idSeleccionado.toStdString();

}

