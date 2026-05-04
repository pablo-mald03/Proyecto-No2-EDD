#ifndef PANTALLAENVIARPRODUCTOS_H
#define PANTALLAENVIARPRODUCTOS_H

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
class PantallaEnviarProductos;
}

class PantallaEnviarProductos : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaEnviarProductos(QWidget *parent = nullptr);
    ~PantallaEnviarProductos();


    std::string codigoSeleccionado;

    /*Metodo que permite inicializar la red del grafo*/
    void inicializarRed(Grafo * referenciaGrafo, Sucursal* _sucursal);

private:
    Ui::PantallaEnviarProductos *ui;

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

    void inicializarComboProdutos(Sucursal* _sucursal);

public slots:
    void darMensaje(QString mensaje, bool exito);

private slots:
    void procesarClicNodo(QString id);

signals:
    void enviarProductoSucursal(const std::string &id);

};

#endif // PANTALLAENVIARPRODUCTOS_H
