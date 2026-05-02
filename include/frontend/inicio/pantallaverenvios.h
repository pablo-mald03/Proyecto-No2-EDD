#ifndef PANTALLAVERENVIOS_H
#define PANTALLAVERENVIOS_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include "graphicsviewzoom.h"
#include "nodografico.h"

#include <QHash>
#include <QList>
#include <qlabel.h>

//SUCURSALES HARDCODEADAS PENDIENTE INTEGRACION REAL
struct SucursalMock2 {
    QString id;
    QString nombre;
};

//CONEXIONES HARDCODEADAS PENDIENTE INTEGRACION REAL
struct ConexionMock2 {
    QString origenId;
    QString destinoId;
};

/*LISTA DE ENVIOS HARDCODEADOS*/
struct Envio {
    QString id;
    QStringList rutaPasada;
    QString siguienteParada;
};

namespace Ui {
class PantallaVerEnvios;
}

class PantallaVerEnvios : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaVerEnvios(QWidget *parent = nullptr);
    ~PantallaVerEnvios();

    std::string codigoSeleccionado;

    /*Metodo que permite reiniciar el estado de lo seleccionado en el combo*/
    void inicializarDatos();

private:
    Ui::PantallaVerEnvios *ui;

    QGraphicsScene *escena = nullptr;

    GraphicsViewZoom *zoomView = nullptr;

    /*Hash utilizado solamente para la union entre nodos*/
    QHash<QString, QHash<QString, NodoGrafico*>> mapaNodosPorEnvio;

    // Metodos que permiten ir construyendo los nodos
    void dibujarNodos(const QList<SucursalMock2> &sucursales, QString idEnvio, int xOffset);
    void dibujarAristas(const QList<ConexionMock2> &conexiones, QString idEnvio);
    void renderizarGrafoPrueba();

    /*Metodo que permite inicializar el comboBox con el grafo actual*/
    void inicializarCombo();

    /*Metodo que permite resetear colores*/
    void resetearColoresEnvio(QString idEnvio);

    /*LISTA DE ENVIOS HARDCODEADOS*/
    QList<Envio> listaEnviosActu;

    void dibujarEnviosHorizontal(QList<Envio> enviosActivos);

    /*METODO HARDCODEADO*/
    SucursalMock2 buscarEnHashHardcoded(QString id);

private slots:
    void procesarClicNodo(QString id);

    void on_comboBox_currentIndexChanged(int index);

    void on_btnEnvios_clicked();

public slots:
    void actualizarTrayectoria(QString idEnvio, QStringList idsPasados, QString idSiguiente);

signals:
    void verificarEnvios(std::string id);
    void navegarASucursal(std::string id);

};

#endif // PANTALLAVERENVIOS_H
