#ifndef PANTALLAVERSUCURSALES_H
#define PANTALLAVERSUCURSALES_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include "conexion.h"
#include "grafo.h"
#include "graphicsviewzoom.h"
#include "nodografico.h"

#include <QHash>
#include <QList>
#include "sucursal.h"


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

    /*Metodo que permite inicializar la red del grafo*/
    void inicializarRed(Grafo * referenciaGrafo);

private:
    Ui::PantallaVerSucursales *ui;
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


private slots:
    void on_btnViajar_clicked();
    void procesarClicNodo(QString id);

    void on_comboBox_currentIndexChanged(int index);

signals:
    void navegarASucursal(std::string id);

    /*Signal que permite buscar la informacion de una susucral*/

};

#endif // PANTALLAVERSUCURSALES_H
