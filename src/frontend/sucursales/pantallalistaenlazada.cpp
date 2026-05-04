#include "pantallalistaenlazada.h"
#include "ui_pantallalistaenlazada.h"

#include <QFileDialog>
#include <QProcess>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDir>
#include <QDesktopServices>
#include <QUrl>
#include <QPainterPath>

/*Pantalla que permite representar graficamente a la lista enlazada ordenada*/
PantallaListaEnlazada::PantallaListaEnlazada(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaListaEnlazada)
{
    ui->setupUi(this);
    this->scene = new QGraphicsScene(this);

    this->zoomView = new GraphicsViewZoom(this);
    this->zoomView->setScene(this->scene);

    this->ui->verticalLayout->replaceWidget(ui->graphicsView, this->zoomView);

    ui->graphicsView->hide();
}

/*Destructor*/
PantallaListaEnlazada::~PantallaListaEnlazada()
{
    delete ui;
}

/*Metodo delegado para poder cargar la vista al momento de moverse
 * PARAMETROS DE ORDEN:
* 1 -> nombre
* 2 -> categoria
* 3 -> fecha
* 4 -> codigo
*/
void PantallaListaEnlazada::setCabeza(NodoLista<Producto> * _cabeza, int parametro){
    this->cabeza = _cabeza;
    this->parametroOrden = parametro;
    this->actualizarVista();
}

/*Metodo que permite actualizar la vista*/
void PantallaListaEnlazada::actualizarVista() {
    this->scene->clear();

    if (this->cabeza != nullptr) {
        dibujarListaEnlazada();
    }

    QRectF bounds = scene->itemsBoundingRect();
    scene->setSceneRect(bounds.adjusted(-100, -100, 200, 200));

    if (this->zoomView && !scene->items().isEmpty()) {
        this->zoomView->centerOn(100, 0);
    }
}

/* Metodo para graficar la lista de forma horizontal */
void PantallaListaEnlazada::dibujarListaEnlazada() {

    int posX = 50;
    int posY = 0;
    int anchoNodo = 160;
    int altoNodo = 50;
    int separacionX = 90;

    QColor colorCianNeon(6, 183, 207);
    QColor colorTexto(250, 250, 250);

    QPen penNodo(colorCianNeon, 3);
    QPen penFlecha(colorCianNeon, 2);
    QFont fuente("Segoe UI", 9, QFont::Bold);

    NodoLista<Producto>* actual = this->cabeza;
    int contador = 0;

    while (actual != nullptr) {

        Producto product = actual->getDato();
        QString textoAMostrar = obtenerTexto(product);

        QRectF rect(posX, posY, anchoNodo, altoNodo);

        QPainterPath path;

        path.addRoundedRect(rect, 10.0, 10.0);

        scene->addPath(path, penNodo, QBrush(Qt::transparent));

        if(textoAMostrar.length() > 18) textoAMostrar = textoAMostrar.left(15) + "...";

        QGraphicsTextItem* itemTexto = scene->addText(textoAMostrar, fuente);
        itemTexto->setDefaultTextColor(colorTexto);
        itemTexto->setPos(posX + 10, posY + 12);

        if (actual->getSiguiente() != nullptr) {
            int inicioLineaX = posX + anchoNodo;
            int finLineaX = posX + anchoNodo + separacionX;
            int medioY = posY + (altoNodo / 2);

            scene->addLine(inicioLineaX, medioY, finLineaX, medioY, penFlecha);

            QPolygonF puntaFlecha;
            puntaFlecha << QPointF(finLineaX, medioY)
                        << QPointF(finLineaX - 10, medioY - 5)
                        << QPointF(finLineaX - 10, medioY + 5);
            scene->addPolygon(puntaFlecha, penFlecha, QBrush(colorCianNeon));
        } else {
            QGraphicsTextItem* nullText = scene->addText("NULL", fuente);
            nullText->setDefaultTextColor(Qt::red);
            nullText->setPos(posX + anchoNodo + 5, posY + 12);
        }

        actual = actual->getSiguiente();
        posX += (anchoNodo + separacionX);
        contador++;
    }
}


/*Metodo auxiliar para ilustrar la lista acorde al parametro de orden*/
QString PantallaListaEnlazada::obtenerTexto(Producto & product){
    switch(this->parametroOrden) {
    case 1:
        return QString::fromStdString(product.getNombre());

    case 2:
        return QString::fromStdString(product.getCategoria());

    case 3:
        return QString::fromStdString(product.getFechaExpiracion());

    case 4:
        return QString::fromStdString(product.getCodigoBarra());

    default:
        return QString::fromStdString(product.getNombre());

    }

}

/*Metodo que permite generar el graphviz del arbol B*/
void PantallaListaEnlazada::generarGraphviz(std::string graph){

    QString rutaImagen = QFileDialog::getSaveFileName(
        this,
        "Guardar Tabla Hash como imagen",
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

/*Metodo que permite solicitar el graphviz de la lista*/
void PantallaListaEnlazada::on_btnExportar_clicked()
{
    emit solicitarGraphvizListaOrdenada();
}

