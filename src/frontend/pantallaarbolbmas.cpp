#include"pantallaarbolbmas.h"
#include "ui_pantallaarbolbmas.h"
#include "graphicsviewzoom.h"

#include"nodobmas.h"
#include <QFileDialog>
#include <QProcess>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDir>
#include <QDesktopServices>
#include <QUrl>


PantallaArbolBMas::PantallaArbolBMas(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaArbolBMas)
{
    ui->setupUi(this);

    this->scene = new QGraphicsScene(this);

    this->zoomView = new GraphicsViewZoom(this);
    this->zoomView->setScene(this->scene);

    this->ui->verticalLayout->replaceWidget(ui->graphicsView, this->zoomView);

    ui->graphicsView->hide();
}

/*Destructor*/
PantallaArbolBMas::~PantallaArbolBMas()
{
    delete ui;
}

/*Metodo que permite generar el graphviz del arbol B*/
void PantallaArbolBMas::generarGraphviz(std::string graph){

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

/*Metodo delegado para poder cargar la vista al momento de moverse*/
void PantallaArbolBMas::setArbol(NodoBMas * _raiz){
    this->raiz = _raiz;
    actualizarVista();
}

/*Metodo que permite actualizar la vista*/
void PantallaArbolBMas::actualizarVista(){

    this->scene->clear();

    if (this->raiz != nullptr) {


        dibujarArbolBMas(this->raiz, 0, 0);

        dibujarConexionesHojas(this->raiz);
    }

    QRectF bounds = scene->itemsBoundingRect();
    scene->setSceneRect(bounds.adjusted(-500, -200, 500, 500));

    if (this->zoomView && !scene->items().isEmpty()) {
        this->zoomView->centerOn(0, 0);
    }
}


/*Metodo que permite dibujar a los nodos*/
int PantallaArbolBMas::dibujarNodoBMas(int x, int y, NodoBMas* nodo) {

    int paddingX = 10;
    int paddingY = 6;
    int separacion = 5;
    int currentX = x;
    int alturaMax = 0;

    std::vector<QGraphicsTextItem*> textos;

    int nClaves = nodo->getClaves().getLongitud();

    for (int i = 0; i < nClaves; i++) {

        Producto p = nodo->getClaves().getValor(i);

        QString etiqueta = QString::fromStdString(p.getCodigoBarra());

        QGraphicsTextItem* text = scene->addText(etiqueta);
        text->setDefaultTextColor(Qt::white);

        QRectF rect = text->boundingRect();
        int ancho = rect.width() + paddingX * 2;
        int alto = rect.height() + paddingY * 2;

        alturaMax = std::max(alturaMax, alto);
        text->setPos(currentX + paddingX, y + paddingY);

        textos.push_back(text);
        currentX += ancho + separacion;
    }

    int anchoTotal = currentX - x - separacion;

    QPen pen(nodo->getEsHoja() ? Qt::green : Qt::white);
    this->scene->addRect(x, y, anchoTotal, alturaMax, pen);

    int lineaX = x;
    for (int i = 0; i < (int)textos.size() - 1; i++) {
        lineaX += textos[i]->boundingRect().width() + paddingX * 2 + separacion;
        this->scene->addLine(lineaX - (separacion/2), y, lineaX - (separacion/2), y + alturaMax, QPen(Qt::white));
    }

    return anchoTotal;
}
/*Metodo que permite dibujar las lineas*/
void PantallaArbolBMas::dibujarLineaBMas(int x1, int y1, int x2, int y2) {
    QPen pen(Qt::white);
    pen.setWidth(1);
    this->scene->addLine(x1, y1, x2, y2, pen);
}

/*Metodo para poder dibujar el arbol B+*/
void PantallaArbolBMas::dibujarArbolBMas(NodoBMas* nodo, int x, int y) {
    if (!nodo){
        return;
    }

    int anchoSubarbol = getAnchoTotal(nodo);
    int anchoNodo = getAnchoNodoReal(nodo);

    int xNodo = x + (anchoSubarbol / 2) - (anchoNodo / 2);

    posicionesX[nodo] = xNodo;
    posicionesY[nodo] = y;

    std::vector<int> puntosDeUnion;
    puntosDeUnion.push_back(xNodo);

    int paddingX = 12, paddingY = 8, currX = xNodo, alturaMax = 0;
    int nClaves = nodo->getClaves().getLongitud();

    for (int i = 0; i < nClaves; i++) {
        Producto p = nodo->getClaves().getValor(i);


        QGraphicsTextItem* text = scene->addText(QString::fromStdString(p.getCategoria()));
        text->setDefaultTextColor(Qt::white);
        text->setPos(currX + paddingX, y + paddingY);

        int anchoCelda = text->boundingRect().width() + (paddingX * 2);
        alturaMax = std::max(alturaMax, (int)text->boundingRect().height() + (paddingY * 2));

        currX += anchoCelda;
        puntosDeUnion.push_back(currX);
    }

    QPen penNodo(nodo->getEsHoja() ? Qt::green : Qt::white);
    scene->addRect(xNodo, y, anchoNodo, alturaMax, penNodo, Qt::NoBrush);


    for(size_t i = 1; i < puntosDeUnion.size() - 1; i++) {
        scene->addLine(puntosDeUnion[i], y, puntosDeUnion[i], y + alturaMax, QPen(Qt::white));
    }

    if (nodo->getEsHoja()) return;

    int yHijos = y + 300;
    int nHijos = nodo->getHijos().getLongitud();
    int xHijoActual = x;

    for (int i = 0; i < nHijos; i++) {
        NodoBMas* hijo = nodo->getHijos().getValor(i);
        int anchoSubHijo = getAnchoTotal(hijo);
        int xCentroHijo = xHijoActual + (anchoSubHijo / 2);

        dibujarLineaBMas(puntosDeUnion[i], y + alturaMax, xCentroHijo, yHijos);

        dibujarArbolBMas(hijo, xHijoActual, yHijos);
        xHijoActual += anchoSubHijo;
    }
}


/* Método que recorre la lista enlazada y dibuja la flecha verde */
void PantallaArbolBMas::dibujarConexionesHojas(NodoBMas* nodoRaiz) {
    if (!nodoRaiz) return;

    NodoBMas* actual = nodoRaiz;
    while (!actual->getEsHoja()) {
        actual = actual->getHijos().getValor(0); // Caer a la primera hoja
    }

    QPen penVerde(Qt::green);
    penVerde.setWidth(2);

    while (actual != nullptr && actual->getSiguiente() != nullptr) {
        NodoBMas* siguiente = actual->getSiguiente();

        int xInicio = posicionesX[actual] + getAnchoNodoReal(actual);
        int yInicio = posicionesY[actual] + 15;

        int xFin = posicionesX[siguiente];
        int yFin = posicionesY[siguiente] + 15;

        this->scene->addLine(xInicio, yInicio, xFin, yFin, penVerde);

        this->scene->addLine(xFin - 5, yFin - 5, xFin, yFin, penVerde);
        this->scene->addLine(xFin - 5, yFin + 5, xFin, yFin, penVerde);

        actual = siguiente;
    }
}

/*Metodo que permite calcular el ancho del nodo real*/
int PantallaArbolBMas::getAnchoNodoReal(NodoBMas* nodo) {
    if (!nodo) return 0;
    int paddingX = 12;
    int anchoTotal = 0;

    int nClaves = nodo->getClaves().getLongitud();

    for (int i = 0; i < nClaves; i++) {
        Producto p = nodo->getClaves().getValor(i);
        QGraphicsTextItem temp(QString::fromStdString(p.getFechaExpiracion()));
        anchoTotal += temp.boundingRect().width() + (paddingX * 2);
    }
    return anchoTotal;
}


/*Metodo que permite obtener el ancho total de la lista para poder generar una mejor distribucion*/
int PantallaArbolBMas::getAnchoTotal(NodoBMas* nodo) {
    if (!nodo) {
        return 0;
    }

    int anchoPropio = getAnchoNodoReal(nodo);
    if (nodo->getEsHoja()) return anchoPropio + 50;

    int anchoHijos = 0;
    int nHijos = nodo->getHijos().getLongitud();
    for (int i = 0; i < nHijos; i++) {
        anchoHijos += getAnchoTotal(nodo->getHijos().getValor(i));
    }
    return std::max(anchoPropio, anchoHijos) + 20;
}



/*Metodo que permite exportar el arbol B+*/
void PantallaArbolBMas::on_btnExportar_clicked()
{
    emit solicitarGraphvizBMas();
}

