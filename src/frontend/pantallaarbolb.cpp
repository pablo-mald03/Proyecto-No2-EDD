#include "pantallaarbolb.h"

/*Includes de la clase*/
#include"nodob.h"
#include "ui_pantallaarbolb.h"

#include <QFileDialog>
#include <QProcess>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDir>
#include <QDesktopServices>
#include <QUrl>

PantallaArbolB::PantallaArbolB(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaArbolB)
{
    ui->setupUi(this);

    this->scene = new QGraphicsScene(this);

    this->zoomView = new GraphicsViewZoom(this);
    this->zoomView->setScene(this->scene);

    this->ui->verticalLayout->replaceWidget(ui->graphicsView, this->zoomView);

    ui->graphicsView->hide();
}

/*Destructor*/
PantallaArbolB::~PantallaArbolB()
{
    delete ui;
}

/*Metodo que permite generar el graphviz del arbol B*/
void PantallaArbolB::generarGraphviz(std::string graph){

    QString rutaImagen = QFileDialog::getSaveFileName(
        this,
        "Guardar arbol B como imagen",
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

        QString errorDetalle = proceso.readAllStandardError();
        QMessageBox::critical(this, "Error", "No se creo la imagen.\n" + errorDetalle);
    }

}

/*Metodo delegado para poder cargar la vista al momento de moverse*/
void PantallaArbolB::setArbol(NodoB * _arbol){
    this->raiz = _arbol;
    actualizarVista();
}

/*Metodo que permite actualizar la vista*/
void PantallaArbolB::actualizarVista(){

    this->scene->clear();

    if (this->raiz != nullptr) {
        dibujarArbolB(this->raiz, 0, 0);
    }

    QRectF bounds = scene->itemsBoundingRect();
    scene->setSceneRect(bounds.adjusted(-500, -200, 500, 500));

    if (this->zoomView && !scene->items().isEmpty()) {
        this->zoomView->centerOn(0, 0);
    }
}

/*Metodo que permite dibujar a los nodos*/
int PantallaArbolB::dibujarNodoB(int x, int y, NodoB* nodo) {

    int paddingX = 12;
    int paddingY = 8;
    int currentX = x;
    int alturaMax = 0;

    // Guardaremos los anchos de cada celda para dibujar las líneas divisorias después
    std::vector<int> anchosCeldas;

    int nClaves = nodo->getClaves().getLongitud();
    for (int i = 0; i < nClaves; i++) {
        Producto product = nodo->getClaves().getValor(i);
        QString etiqueta = QString::fromStdString(product.getFechaExpiracion());

        QGraphicsTextItem* text = scene->addText(etiqueta);
        text->setDefaultTextColor(Qt::white);

        QRectF rect = text->boundingRect();
        int ancho = rect.width() + paddingX * 2;
        int alto = rect.height() + paddingY * 2;

        alturaMax = std::max(alturaMax, alto);
        text->setPos(currentX + paddingX, y + paddingY);

        anchosCeldas.push_back(ancho);
        currentX += ancho;
    }

    int anchoTotal = currentX - x;

    scene->addRect(x, y, anchoTotal, alturaMax, QPen(Qt::white), Qt::NoBrush);

    int lineaX = x;
    for (int i = 0; i < (int)anchosCeldas.size() - 1; i++) {
        lineaX += anchosCeldas[i];
        scene->addLine(lineaX, y, lineaX, y + alturaMax, QPen(Qt::white));
    }

    return anchoTotal;
}

/*Metodo que permite dibujar las lineas*/
void PantallaArbolB::dibujarLineaB(int x1, int y1, int x2, int y2) {
    QPen pen(Qt::white);
    pen.setWidth(1);
    this->scene->addLine(x1, y1, x2, y2, pen);
}

/*Metodo que permite dibujar el arbol B*/
void PantallaArbolB::dibujarArbolB(NodoB* nodo, int x, int y) {

    if (!nodo){
        return;
    }

    int anchoSubarbol = getAnchoTotal(nodo);
    int anchoNodo = getAnchoNodoReal(nodo);

    int xNodo = x + (anchoSubarbol / 2) - (anchoNodo / 2);

    std::vector<int> puntosDeUnion;
    puntosDeUnion.push_back(xNodo);

    int paddingX = 12, paddingY = 8, currX = xNodo, alturaMax = 0;
    int nClaves = nodo->getClaves().getLongitud();

    for (int i = 0; i < nClaves; i++) {
        Producto p = nodo->getClaves().getValor(i);
        QGraphicsTextItem* text = scene->addText(QString::fromStdString(p.getFechaExpiracion()));
        text->setDefaultTextColor(Qt::white);
        text->setPos(currX + paddingX, y + paddingY);

        int anchoCelda = text->boundingRect().width() + (paddingX * 2);
        alturaMax = std::max(alturaMax, (int)text->boundingRect().height() + (paddingY * 2));

        currX += anchoCelda;
        puntosDeUnion.push_back(currX);
    }

    scene->addRect(xNodo, y, anchoNodo, alturaMax, QPen(Qt::white), Qt::NoBrush);
    for(size_t i = 1; i < puntosDeUnion.size() - 1; i++) {
        scene->addLine(puntosDeUnion[i], y, puntosDeUnion[i], y + alturaMax, QPen(Qt::white));
    }

    if (nodo->getEsHoja()) return;


    int yHijos = y + 420;
    int nHijos = nodo->getHijos().getLongitud();
    int xHijoActual = x;

    for (int i = 0; i < nHijos; i++) {
        NodoB* hijo = nodo->getHijos().getValor(i);
        int anchoSubHijo = getAnchoTotal(hijo);
        int xCentroHijo = xHijoActual + (anchoSubHijo / 2);

        dibujarLineaB(puntosDeUnion[i], y + alturaMax, xCentroHijo, yHijos);

        dibujarArbolB(hijo, xHijoActual, yHijos);
        xHijoActual += anchoSubHijo;
    }
}

/*Metodo que permite calcular el ancho del nodo real*/
int PantallaArbolB::getAnchoNodoReal(NodoB* nodo) {
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
int PantallaArbolB::getAnchoTotal(NodoB* nodo) {
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


/*Metodo que permite exportar el arbol B*/
void PantallaArbolB::on_btnExportar_clicked()
{
    emit solicitarGraphvizB();
}

