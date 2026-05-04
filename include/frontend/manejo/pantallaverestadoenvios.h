#ifndef PANTALLAVERESTADOENVIOS_H
#define PANTALLAVERESTADOENVIOS_H

#include "grafo.h"
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include "conexion.h"
#include "graphicsviewzoom.h"
#include "nodografico.h"
#include "sucursal.h"
#include <QHash>
#include <QList>

namespace Ui {
class PantallaVerEstadoEnvios;
}

class PantallaVerEstadoEnvios : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaVerEstadoEnvios(QWidget *parent = nullptr);
    ~PantallaVerEstadoEnvios();

    /*Metodo que permite inicializar la red de sucursales del grafo*/
    void inicializarRed(Grafo * referenciaGrafo, Sucursal* _sucursal);
private:
    Ui::PantallaVerEstadoEnvios *ui;

    QGraphicsScene *escena = nullptr;

    GraphicsViewZoom *zoomView = nullptr;

    /*Hash utilizado solamente para la union entre nodos*/
    QHash<QString, NodoGrafico*> nodosRenderizados;

    // Metodos que permiten ir construyendo los nodos
    void dibujarNodos(const std::vector<Sucursal*> &sucursales) ;
    void dibujarAristas(const std::vector<Sucursal*> &nodos,
                        const std::vector<std::vector<Conexion*>> &matriz);

    /*Metodo que permite reiniciar el estado de lo seleccionado en el combo*/
    void inicializarDatos(const std::vector<Sucursal*>& sucursales);

    void cargarGrafo(const std::vector<Sucursal *> &nodos,
                     const std::vector<std::vector<Conexion *>> &matriz);

    /*Metodo que permite inicializar el comboBox con el grafo actual*/
    void inicializarCombo(const std::vector<Sucursal*>& sucursales);
};

#endif // PANTALLAVERESTADOENVIOS_H
