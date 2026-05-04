#include "pantallatablahash.h"
#include "ui_pantallatablahash.h"

#include <QFileDialog>
#include <QProcess>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDir>
#include <QDesktopServices>
#include <QUrl>

PantallaTablaHash::PantallaTablaHash(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaTablaHash)
{
    ui->setupUi(this);
    this->scene = new QGraphicsScene(this);

    this->zoomView = new GraphicsViewZoom(this);
    this->zoomView->setScene(this->scene);

    this->ui->verticalLayout->replaceWidget(ui->graphicsView, this->zoomView);

    ui->graphicsView->hide();
}

/*Destructor*/
PantallaTablaHash::~PantallaTablaHash()
{
    delete ui;
}

/*Metodo delegado para poder cargar la vista al momento de moverse*/
void PantallaTablaHash::setTabla(ListaEnlazada<Producto>**  _tabla, int capacidad){
    this->tabla = _tabla;
    this->capacidadTabla = capacidad;
    actualizarVista();
}

/*Metodo que permite actualizar la vista*/
void PantallaTablaHash::actualizarVista(){

    this->scene->clear();

    if (this->tabla != nullptr && this->capacidadTabla > 0) {
        dibujarTablaHash();
    }

    QRectF bounds = scene->itemsBoundingRect();
    scene->setSceneRect(bounds.adjusted(-100, -100, 200, 200));

    if (this->zoomView && !scene->items().isEmpty()) {
        this->zoomView->centerOn(0, 0);
    }
}

/* Metodo que permite dar la representacion grafica de la Tabla Hash */
void PantallaTablaHash::dibujarTablaHash() {
    int anchoBucket = 70;
    int anchoNodo = 140;
    int altoCaja = 45;

    int separacionY = 20;
    int separacionX = 90;

    int offsetX = 200;

    QColor colorBordeBucket(180, 180, 180);
    QColor colorBordePrincipal(169, 223, 191);
    QColor colorBordeColision(245, 176, 65);
    QColor colorTexto(240, 240, 240);
    QColor colorLinea(200, 200, 200, 150);

    QPen penBucket(colorBordeBucket, 2);
    QPen penPrincipal(colorBordePrincipal, 3);
    QPen penColision(colorBordeColision, 3);
    QPen penConexion(colorLinea, 2);

    QBrush brushTransparente(Qt::transparent);

    QFont fuente("Segoe UI", 10, QFont::Bold);

    for (int i = 0; i < this->capacidadTabla; i++) {
        int posY = i * (altoCaja + separacionY);

        scene->addRect(offsetX, posY, anchoBucket, altoCaja, penBucket, brushTransparente);

        QGraphicsTextItem* textoIndex = scene->addText("[" + QString::number(i) + "]", fuente);
        textoIndex->setDefaultTextColor(colorTexto);
        textoIndex->setPos(offsetX + 10, posY + 10);

        if (this->tabla[i] != nullptr && this->tabla[i]->getLongitud() > 0) {

            int cantidadNodos = this->tabla[i]->getLongitud();
            int posXPrevio = offsetX + anchoBucket;

            for (int j = 0; j < cantidadNodos; j++) {
                int posXNodo = posXPrevio + separacionX;

                QPen penActual = (j == 0) ? penPrincipal : penColision;

                scene->addRect(posXNodo, posY, anchoNodo, altoCaja, penActual, brushTransparente);

                Producto prodActual = this->tabla[i]->getValor(j);
                QString codigo = QString::fromStdString(prodActual.getCodigoBarra());

                QGraphicsTextItem* textoCodigo = scene->addText(codigo, fuente);
                textoCodigo->setDefaultTextColor(colorTexto);
                textoCodigo->setPos(posXNodo + 15, posY + 10);

                scene->addLine(posXPrevio, posY + (altoCaja / 2), posXNodo, posY + (altoCaja / 2), penConexion);

                posXPrevio = posXNodo + anchoNodo;
            }
        }
    }
}


/*Metodo que permite generar el graphviz del arbol B*/
void PantallaTablaHash::generarGraphviz(std::string graph){

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

/*Metodo que permite solicitar el graphviz de a tabla hash*/
void PantallaTablaHash::on_btnExportar_clicked()
{
    emit solicitarGraphvizHash();

}

