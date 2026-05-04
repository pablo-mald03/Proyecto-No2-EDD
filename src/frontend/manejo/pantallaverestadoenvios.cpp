#include "pantallaverestadoenvios.h"
#include "ui_pantallaverestadoenvios.h"

PantallaVerEstadoEnvios::PantallaVerEstadoEnvios(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaVerEstadoEnvios)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_StyledBackground, true);

    //Se aplica el estilo al contenedor padre
    this->setStyleSheet("QWidget#PantallaVerEstadoEnvios { "
                        "border-image: url(:/assets/fondo/GrafosBackground.png) 0 0 0 0 stretch stretch; "
                        "} ");

    escena = new QGraphicsScene(this);

    this->zoomView = new GraphicsViewZoom(this);
    this->zoomView->setScene(this->escena);

    this->ui->verticalLayout->replaceWidget(ui->graphicsView, this->zoomView);

    ui->graphicsView->hide();
}

/*Metodo que permite inicializar la red del grafo*/
void PantallaVerEstadoEnvios::inicializarRed(Grafo * referenciaGrafo, Sucursal* _sucursal){
    //this->cargarGrafo(referenciaGrafo->getNodos(),referenciaGrafo->getMatriz());
    //this->inicializarDatos(referenciaGrafo->getNodos());
}


/*Destructor*/
PantallaVerEstadoEnvios::~PantallaVerEstadoEnvios()
{
    delete ui;
}

/*Metodo que permite dibujar los nodos*/
void PantallaVerEstadoEnvios::dibujarNodos(const std::vector<Sucursal*> &sucursales) {
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
        //connect(nodo, &NodoGrafico::seleccionado, this, &PantallaVerEstadoEnvios::procesarClicNodo);
    }
}

/*Metodo que permite dibujar las aristas del grafo desde la matriz de adyacencia*/
void PantallaVerEstadoEnvios::dibujarAristas(const std::vector<Sucursal*> &nodos,
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
void PantallaVerEstadoEnvios::cargarGrafo(const std::vector<Sucursal*>& nodos,
                                        const std::vector<std::vector<Conexion*>>& matriz) {
    escena->clear();
    nodosRenderizados.clear();

    if (nodos.empty()) return;

    dibujarNodos(nodos);

    dibujarAristas(nodos, matriz);

    ui->graphicsView->setSceneRect(escena->itemsBoundingRect().adjusted(-50, -50, 50, 50));
}

/*Metodo que permite inicializar el comboBox*/
/*9void PantallaVerEstadoEnvios::inicializarCombo(const std::vector<Sucursal*>& sucursales) {
    ui->comboSu->blockSignals(true);
    ui->comboBox->clear();

    for (Sucursal* suc : sucursales) {
        QString nombreVisible = QString::fromStdString(suc->getNombre());
        QString idOculto = QString::fromStdString(suc->getId());

        ui->comboBox->addItem(nombreVisible, idOculto);
    }

    ui->comboBox->setPlaceholderText("Seleccione una sucursal...");
    ui->comboBox->setCurrentIndex(-1);
    ui->comboBox->blockSignals(false);
}*/

/*Metodo que permite reiniciar el estado de los parametros*/
/*void PantallaVerEstadoEnvios::inicializarDatos(const std::vector<Sucursal*>& sucursales){

    this->codigoSeleccionado = "";
    this->inicializarCombo(sucursales);
}*/
