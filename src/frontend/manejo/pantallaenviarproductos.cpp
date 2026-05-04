#include "pantallaenviarproductos.h"
#include "ui_pantallaenviarproductos.h"

#include<QMessageBox>

PantallaEnviarProductos::PantallaEnviarProductos(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaEnviarProductos)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_StyledBackground, true);

    //Se aplica el estilo al contenedor padre
    this->setStyleSheet("QWidget#PantallaEnviarProductos { "
                        "border-image: url(:/assets/fondo/GrafosBackground.png) 0 0 0 0 stretch stretch; "
                        "} ");

    escena = new QGraphicsScene(this);

    this->zoomView = new GraphicsViewZoom(this);
    this->zoomView->setScene(this->escena);

    this->ui->verticalLayout->replaceWidget(ui->graphicsView, this->zoomView);

    ui->graphicsView->hide();

}


/*Metodo que permite inicializar la red del grafo*/
void PantallaEnviarProductos::inicializarRed(Grafo * referenciaGrafo, Sucursal* _sucursal){
    this->cargarGrafo(referenciaGrafo->getNodos(),referenciaGrafo->getMatriz());
    this->inicializarDatos(referenciaGrafo->getNodos());

    this->inicializarComboProdutos(_sucursal);
}

/*Metodo que permite inicializar el comboBox de los productos disponibles en la sucursal*/
void PantallaEnviarProductos::inicializarComboProdutos(Sucursal* _sucursal){

    GestorEstructuras * gestor = _sucursal->getAlmacen();
    ListaEnlazada<Producto> listaProductos = gestor->listarProductosAvl();

    ui->comboProducto->blockSignals(true);
    ui->comboProducto->clear();

    for(int i = 0; i < listaProductos.getLongitud(); i++) {
        Producto product = listaProductos.getValor(i);

        QString nombreVisible = QString::fromStdString(product.getNombre());
        QString idOculto = QString::fromStdString(product.getCodigoBarra());

        ui->comboProducto->addItem(nombreVisible, idOculto);
    }

    ui->comboProducto->setPlaceholderText("Seleccione una sucursal...");
    ui->comboProducto->setCurrentIndex(-1);
    ui->comboProducto->blockSignals(false);
}


/*Metodo que permite procesar el click y emitir el signal hacia el controlador*/
void PantallaEnviarProductos::procesarClicNodo(QString id) {

}

/*Destructor*/
PantallaEnviarProductos::~PantallaEnviarProductos()
{
    delete ui;
}


/*Metodo que permite dibujar los nodos*/
void PantallaEnviarProductos::dibujarNodos(const std::vector<Sucursal*> &sucursales) {
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
        connect(nodo, &NodoGrafico::seleccionado, this, &PantallaEnviarProductos::procesarClicNodo);
    }
}

/*Metodo que permite dibujar las aristas del grafo desde la matriz de adyacencia*/
void PantallaEnviarProductos::dibujarAristas(const std::vector<Sucursal*> &nodos,
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

/*Metodo que permite dar mensaje */
void PantallaEnviarProductos::darMensaje(QString mensaje, bool exito){

    if (!exito) {
        QMessageBox::warning(this, "Ha ocurrido un error",
                             mensaje);
        return;
    }

    QMessageBox::information(this, "Producto enviado con exito",
                         mensaje);
}

//Metodo que permite mostrar el grafo
void PantallaEnviarProductos::cargarGrafo(const std::vector<Sucursal*>& nodos,
                                        const std::vector<std::vector<Conexion*>>& matriz) {
    escena->clear();
    nodosRenderizados.clear();

    if (nodos.empty()) return;

    dibujarNodos(nodos);

    dibujarAristas(nodos, matriz);

    ui->graphicsView->setSceneRect(escena->itemsBoundingRect().adjusted(-50, -50, 50, 50));
}

/*Metodo que permite inicializar el comboBox*/
void PantallaEnviarProductos::inicializarCombo(const std::vector<Sucursal*>& sucursales) {
    ui->comboDestino->blockSignals(true);
    ui->comboDestino->clear();

    for (Sucursal* suc : sucursales) {
        QString nombreVisible = QString::fromStdString(suc->getNombre());
        QString idOculto = QString::fromStdString(suc->getId());

        ui->comboDestino->addItem(nombreVisible, idOculto);
    }

    ui->comboDestino->setPlaceholderText("Seleccione una sucursal...");
    ui->comboDestino->setCurrentIndex(-1);
    ui->comboDestino->blockSignals(false);
}

/*Metodo que permite reiniciar el estado de los parametros*/
void PantallaEnviarProductos::inicializarDatos(const std::vector<Sucursal*>& sucursales){

    this->codigoSeleccionado = "";
    this->inicializarCombo(sucursales);
}
