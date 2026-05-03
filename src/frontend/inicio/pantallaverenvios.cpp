#include "pantallaverenvios.h"
#include "ui_pantallaverenvios.h"
#include <QDebug>
#include <QtMath>
#include<QMessageBox>

PantallaVerEnvios::PantallaVerEnvios(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaVerEnvios)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_StyledBackground, true);

    //Se aplica el estilo al contenedor padre
    this->setStyleSheet("QWidget#PantallaVerEnvios { "
                        "border-image: url(:/assets/fondo/GrafosBackground.png) 0 0 0 0 stretch stretch; "
                        "} ");

    escena = new QGraphicsScene(this);

    this->zoomView = new GraphicsViewZoom(this);
    this->zoomView->setScene(this->escena);

    this->ui->verticalLayout->replaceWidget(ui->graphicsView, this->zoomView);

    ui->graphicsView->hide();
}

/*Metodo que permite procesar el click y emitir el signal hacia el controlador*/
void PantallaVerEnvios::procesarClicNodo(QString id) {
    emit navegarASucursal(id.toStdString());
}

/*Destructor*/
PantallaVerEnvios::~PantallaVerEnvios()
{
    delete ui;
}

/*Metodo que permite dibujar los nodos*/
void PantallaVerEnvios::dibujarNodos(const QList<SucursalMock2> &sucursales, QString idEnvio, int xOffset){
    int totalNodos = sucursales.size();
    int radioCirculo = 200;

    for (int i = 0; i < totalNodos; ++i) {
        SucursalMock2 suc = sucursales[i];
        NodoGrafico *nodo = new NodoGrafico(suc.id, suc.nombre, QColor(0x3d5afe), false);

        double angulo = (2.0 * M_PI * i) / totalNodos;
        double x = (radioCirculo * qCos(angulo)) + xOffset;
        double y = radioCirculo * qSin(angulo);
        nodo->setPos(x, y);

        escena->addItem(nodo);

        mapaNodosPorEnvio[idEnvio].insert(suc.id, nodo);

        connect(nodo, &NodoGrafico::seleccionado, this, &PantallaVerEnvios::procesarClicNodo);
    }
}

/*Metodo que permite dibujar las aristas del grafo*/
void PantallaVerEnvios::dibujarAristas(const QList<ConexionMock2> &conexiones, QString idEnvio) {
    QPen penArista(Qt::lightGray, 3, Qt::SolidLine);

    QHash<QString, NodoGrafico*> &nodosDeEsteEnvio = mapaNodosPorEnvio[idEnvio];

    for (const ConexionMock2 &conexion : conexiones) {
        if (nodosDeEsteEnvio.contains(conexion.origenId) && nodosDeEsteEnvio.contains(conexion.destinoId)) {

            NodoGrafico *origen = nodosDeEsteEnvio[conexion.origenId];
            NodoGrafico *destino = nodosDeEsteEnvio[conexion.destinoId];

            QGraphicsLineItem *linea = new QGraphicsLineItem(
                origen->pos().x(), origen->pos().y(),
                destino->pos().x(), destino->pos().y()
                );

            linea->setPen(penArista);
            linea->setZValue(0);
            escena->addItem(linea);
        }
    }
}

/*Metodo que permite dibujar los envios que se van haciendo*/
void PantallaVerEnvios::dibujarEnviosHorizontal(QList<Envio> enviosActivos) {
    escena->clear();
    mapaNodosPorEnvio.clear();

    QList<SucursalMock2> listaSucursales = {
        {"101", "Central"}, {"102", "Norte"}, {"103", "Sur"}, {"104", "Este"}
    };
    QList<ConexionMock2> listaConexiones = {
        {"101", "102"}, {"101", "103"}, {"102", "104"}, {"103", "104"}
    };

    int xOffset = 0;
    int espaciado = 800;

    for (const Envio &e : enviosActivos) {
        QGraphicsTextItem *titulo = escena->addText(e.id);
        titulo->setFont(QFont("Arial", 20, QFont::Bold));
        titulo->setDefaultTextColor(Qt::yellow);
        titulo->setPos(xOffset - 100, -300);

        dibujarNodos(listaSucursales, e.id, xOffset);

        dibujarAristas(listaConexiones, e.id);

        actualizarTrayectoria(e.id, e.rutaPasada, e.siguienteParada);

        xOffset += espaciado;
    }

    escena->setSceneRect(escena->itemsBoundingRect());
}


/* Método que limpia todos los nodos al color azul original */
void PantallaVerEnvios::resetearColoresEnvio(QString idEnvio) {
    if (mapaNodosPorEnvio.contains(idEnvio)) {
        for (NodoGrafico* nodo : mapaNodosPorEnvio[idEnvio].values()) {
            nodo->actualizarColor(QColor(0x3d5afe));
        }
    }
}

/*Metodo que permite ir actualizando la trayectoria de los envios*/
void PantallaVerEnvios::actualizarTrayectoria(QString idEnvio, QStringList idsPasados, QString idSiguiente) {

    if (!mapaNodosPorEnvio.contains(idEnvio)) return;

    QHash<QString, NodoGrafico*> &nodosDelEnvio = mapaNodosPorEnvio[idEnvio];

    for (NodoGrafico* n : nodosDelEnvio.values()) {
        n->actualizarColor(QColor(0x3d5afe));
    }

    for (const QString& id : idsPasados) {
        if (nodosDelEnvio.contains(id)) {
            nodosDelEnvio[id]->actualizarColor(QColor(Qt::green));
        }
    }


    if (nodosDelEnvio.contains(idSiguiente)) {
        nodosDelEnvio[idSiguiente]->actualizarColor(QColor(Qt::yellow));
    }

    escena->update();
}

/*Metodo que permite inicializar el comboBox*/
void PantallaVerEnvios::inicializarCombo() {

    ui->comboBox->blockSignals(true);
    ui->comboBox->clear();

    ui->comboBox->addItem("Sucursal Central - Ciudad", "ID_001");
    ui->comboBox->addItem("Sucursal Norte - Petén", "ID_002");
    ui->comboBox->addItem("Sucursal Occidente - Xela", "ID_003");

    ui->comboBox->setCurrentIndex(-1);

    ui->comboBox->blockSignals(false);
}

/*METODO PROVISIONAL*/
SucursalMock2 PantallaVerEnvios::buscarEnHashHardcoded(QString id) {
    SucursalMock2 s;
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
void PantallaVerEnvios::inicializarDatos(){

    this->codigoSeleccionado = "";
    this->inicializarCombo();
}

/*Permite actualizar el estado de envios de las sucursales*/
void PantallaVerEnvios::on_comboBox_currentIndexChanged(int index)
{

    if (index == -1) return;

    QString idSeleccionado = ui->comboBox->currentData().toString().trimmed();

    QList<Envio> enviosDeEstaSucursal;

    if(idSeleccionado == "ID_001") {
        enviosDeEstaSucursal << Envio{"ENVÍO 1:", {"101"}, "102"};
        enviosDeEstaSucursal << Envio{"ENVÍO 2:", {"101", "102"}, "104"};
        enviosDeEstaSucursal << Envio{"ENVÍO 3:", {}, "101"};
    } else {
        enviosDeEstaSucursal << Envio{"ENVÍO 1:", {"103"}, "104"};
    }

    dibujarEnviosHorizontal(enviosDeEstaSucursal);

    this->ui->lblInfoEnvio->setText("Mostrando " + QString::number(enviosDeEstaSucursal.size()) + " envíos activos.");

    emit verificarEnvios(idSeleccionado.toStdString());
}


