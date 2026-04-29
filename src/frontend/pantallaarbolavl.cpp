#include "pantallaarbolavl.h"


/*Includes de la clase*/
#include "nodoavl.h"
#include "ui_pantallaarbolavl.h"
#include"graphicsviewzoom.h"

#include <QFileDialog>
#include <QProcess>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDir>
#include <QDesktopServices>
#include <QUrl>
#include<QGraphicsView>
#include <QGraphicsTextItem>

PantallaArbolAvl::PantallaArbolAvl(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaArbolAvl)
{
    ui->setupUi(this);

    this->scene = new QGraphicsScene(this);

    auto view = new GraphicsViewZoom(this);
    view->setScene(scene);

    this->ui->verticalLayout->replaceWidget(ui->graphicsView, view);

    delete ui->graphicsView;

    this->ui->graphicsView = view;
}

/*Destructor*/
PantallaArbolAvl::~PantallaArbolAvl()
{
    delete ui;
}

/*Metodo que permite generar el graphviz del arbol*/
void PantallaArbolAvl::generarGraphviz(std::string graph){

    QString rutaImagen = QFileDialog::getSaveFileName(
        this,
        "Guardar arbol AVL como imagen",
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
void PantallaArbolAvl::setArbol(NodoAvl * _arbol){
    this->arbol = _arbol;
    actualizarVista();
}

/*Metodo que permite poder actualizar la vista del arbol*/
void PantallaArbolAvl::actualizarVista(){

    this->scene->clear();

    if (this->arbol != nullptr) {
        int alturaTotal = this->arbol->getAltura();


        int offsetInicial = alturaTotal * 1000;

        dibujarArbol(this->arbol, 0, 0, offsetInicial);
    }
    scene->setSceneRect(scene->itemsBoundingRect().adjusted(-500, -200, 500, 500));
}

/*Metodo utilizado para poder dibujar a la esecena*/
QRectF PantallaArbolAvl::dibujarNodo(int x, int y, QString texto, int altura) {

    int paddingH = 20;
    int paddingV = 15;

    if (texto.length() > 25) texto = texto.left(22) + "...";

    QGraphicsTextItem* text = scene->addText(texto);
    text->setDefaultTextColor(Qt::white);
    text->setZValue(10);
    QFont font = text->font();
    font.setPointSize(10);
    font.setBold(true);
    text->setFont(font);

    QGraphicsTextItem* heightText = scene->addText(QString("Alt: %1").arg(altura));
    heightText->setDefaultTextColor(QColor(161, 161, 170));
    heightText->setZValue(10);
    QFont hFont = heightText->font();
    hFont.setPointSize(8);
    heightText->setFont(hFont);

    QRectF textRect = text->boundingRect();
    QRectF hRect = heightText->boundingRect();

    int ancho = std::max({(int)textRect.width() + paddingH * 2, (int)hRect.width() + paddingH * 2, 160});
    int alto = textRect.height() + hRect.height() + paddingV;

    this->scene->addEllipse(x, y, ancho, alto, QPen(Qt::white, 2), QBrush(QColor(30, 30, 35)));

    text->setPos(x + (ancho - textRect.width()) / 2, y + (alto / 2) - textRect.height() + 5);

    heightText->setPos(x + (ancho - hRect.width()) / 2, text->y() + textRect.height() - 5);

    return QRectF(x, y, ancho, alto);
}

/*Metodo que permite dibujar las lineas de trazo*/
void PantallaArbolAvl::dibujarLinea(int x1, int y1, int x2, int y2) {
    QPen pen(Qt::white);
    pen.setWidth(1);
    scene->addLine(x1, y1, x2, y2, pen);
}

/*Metodo que permite dibujar el arbol con sus n odos dandole el estilo de arbol descendente*/
void PantallaArbolAvl::dibujarArbol(NodoAvl* nodo, int x, int y, int offset) {

    if (!nodo){
        return;
    }

    QString nombre = QString::fromStdString(nodo->getDato().getNombre());
    QRectF nodoRect = dibujarNodo(x, y, nombre,nodo->getAltura());

    int centerX = x + nodoRect.width() / 2;
    int bottomY = y + nodoRect.height();

    int distanciaVertical = 400;

    float factor = 0.5 + (nodo->getAltura() * 0.04);
    if (factor > 0.8) factor = 0.8;

    int nuevoOffset = offset * factor;

    if (nuevoOffset < 110) nuevoOffset = 110;


    if (nodo->getIzquierda()) {
        int childX = centerX - nuevoOffset - nodoRect.width() / 2;
        int childY = y + distanciaVertical;
        dibujarLinea(centerX, bottomY, childX + nodoRect.width() / 2, childY);
        dibujarArbol(nodo->getIzquierda(), childX, childY, nuevoOffset);
    }

    if (nodo->getDerecha()) {
        int childX = centerX + nuevoOffset - nodoRect.width() / 2;
        int childY = y + distanciaVertical;
        dibujarLinea(centerX, bottomY, childX + nodoRect.width() / 2, childY);
        dibujarArbol(nodo->getDerecha(), childX, childY, nuevoOffset);
    }
}

/*Metodo que permite exportar el .dot*/
void PantallaArbolAvl::on_btnExportar_clicked()
{
    emit solicitarGraphvizAvl();
}

