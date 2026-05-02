#ifndef PANTALLAVERSUCURSALES_H
#define PANTALLAVERSUCURSALES_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include "graphicsviewzoom.h"
#include "nodografico.h"

#include <QHash>
#include <QList>

//SUCURSALES HARDCODEADAS PENDIENTE INTEGRACION REAL
struct SucursalMock {
    QString id;
    QString nombre;
};

//CONEXIONES HARDCODEADAS PENDIENTE INTEGRACION REAL
struct ConexionMock {
    QString origenId;
    QString destinoId;
};

namespace Ui {
class PantallaVerSucursales;
}

class PantallaVerSucursales : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaVerSucursales(QWidget *parent = nullptr);
    ~PantallaVerSucursales();

    std::string codigoSeleccionado;

    /*Metodo que permite reiniciar el estado de lo seleccionado en el combo*/
    void inicializarDatos();

private:
    Ui::PantallaVerSucursales *ui;
    QGraphicsScene *escena = nullptr;

    GraphicsViewZoom *zoomView = nullptr;

    /*Hash utilizado solamente para la union entre nodos*/
    QHash<QString, NodoGrafico*> nodosRenderizados;

    // Metodos que permiten ir construyendo los nodos
    void dibujarNodos(const QList<SucursalMock> &sucursales);
    void dibujarAristas(const QList<ConexionMock> &conexiones);
    void renderizarGrafoPrueba();

    /*Metodo que permite inicializar el comboBox con el grafo actual*/
    void inicializarCombo();

    /*METODO HARDCODEADO*/
    SucursalMock buscarEnHashHardcoded(QString id);

private slots:
    void on_btnViajar_clicked();
    void procesarClicNodo(QString id);

    void on_comboBox_currentIndexChanged(int index);

signals:
    void navegarASucursal(std::string id);

    /*Signal que permite buscar la informacion de una susucral*/

};

#endif // PANTALLAVERSUCURSALES_H
