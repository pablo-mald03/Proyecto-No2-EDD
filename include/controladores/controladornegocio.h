#ifndef CONTROLADORNEGOCIO_H
#define CONTROLADORNEGOCIO_H

#include "gestorestructuras.h"
#include "gestormapa.h"
#include <QObject>

/*Controlador que permite llevar toda la logica para el manejo principal de las redes de sucursales*/
class ControladorNegocio : public QObject
{
    Q_OBJECT
public:
    explicit ControladorNegocio(QObject *parent = nullptr);
    ~ControladorNegocio();

    /*Metodo que permite obtener la referencia del grafo*/
    Grafo * obtenerGrafo() const;

private:
    /*Instancia que permite manejar toda la logica de negocio de las sucursales*/
    GestorMapa * gestorMapeo = nullptr;

    /*Metodo que verifica si hay errores en la carga de sucursales*/
    void verificarErroresSucursales(int parametro);

public slots:
    void procesarCsvSucursal(const std::vector<std::vector<QString>> & data);
    void procesarCsvConexion(const std::vector<std::vector<QString>> & data);

    void procesarCsvEnvios(const std::vector<std::vector<QString>> & data);

    void procesarCsvProductos(const std::vector<std::vector<QString>> & data);

    /*Metodo que permite obtener los datos para poder descargar el Log de errores de sucursales*/
    void prepararLogParaDescargaSucursales();

    /*Metodo que permite obtener los datos para poder descargar el Log de errores de envios*/
    void prepararLogParaDescargaEnvios();

    /*Metodo que permite obtener los datos para poder descargar el Log de errores de productos*/
    void prepararLogParaDescargaProductos();

    /*Metodo que permite insertar una sucursal*/
    void insercionSucursal(const std::string &_id,const std::string &_nombre, const std::string &_ubicacion, double _ingreso, double _despacho, double _preparacion);

    /*Metodo que permite insertar una sucursal*/
    void conexionSucursal(const std::string &_Origen, const std::string &_Destino,double _tiempo,double _costo);

    /*Metodo que permite insertar una sucursal*/
    void eliminacionSucursal(const std::string &_id);

    /*Metodo que permite modificar una sucursal*/
    void modificacionSucursal(const std::string &_id,const std::string &_nombre, const std::string &_ubicacion, double _ingreso, double _despacho, double _preparacion);

    /*Metodo que permite buscar la informacion de la sucursal en bas al id*/
    void buscarSucursal(const std::string &_id);

    /*Metodo que permite generar el viaje hacia la sucursal*/
    void cargarSucursal(const std::string &id);

    /*Metodo que permite retornar el estado de la pila de envios de una sucursal*/
    void buscarEnvios(std::string id);

    /*Metodo que permite generar el graphviz del grafo*/
    void generarGraphvizGrafo();

signals:

    /*Metodos que permiten agregar enviar informacion sobre los logs de los datos de las sucursales*/
    void logGrafoSucursales(QString mensaje, QString color);
    void logCargaCsvSucursales(QString mensaje, QString color);

    /*Signal que permite setear el tiempo en el label*/
    void tiempoProcesoSucursales(int estructura, double milisegundos);

    /*Signal que permite enviar el log de errores de sucursales*/
    void logDescargarSucursales(QString contenido);
    void evaluarErroresSucursalesLog(bool evaluacion);

    /*Metodos que permiten agregar enviar informacion sobre los logs de los datos de los envios*/
    void logGrafoEnvios(QString mensaje, QString color);
    void logCargaCsvEnvios(QString mensaje, QString color);

    /*Signal que permite enviar el log de errores de envios*/
    void logDescargarEnvios(QString contenido);
    void evaluarErroresEnviosLog(bool evaluacion);

    /*Signal que permite setear el tiempo en el label*/
    void tiempoProcesoEnvios(int estructura, double milisegundos);

    /*Signals que permiten comunicarse con la pantalla del csv de productos */
    void logArbolAvl(QString mensaje, QString color);
    void logArbolB(QString mensaje, QString color);
    void logArbolBMas(QString mensaje, QString color);
    void logLista(QString mensaje, QString color);
    void logHash(QString mensaje, QString color);

    void logCargaCsvProductos(QString mensaje, QString color);

    /*Signal que permite setear el tiempo en el label*/
    void tiempoProcesoProductos(int estructura, double milisegundos);

    /*Signal que permite enviar el log de errores de envios*/
    void logDescargarProductos(QString contenido);
    void evaluarErroresProductosLog(bool evaluacion);


    /*Signals que permiten ir comunicandose con la UI para poder realizar las operaciones de insercion*/
    void logInsertGrafo(QString mensaje, QString color);
    void tiempoProcesoInsercionGrafo(double milisegundos);
    void actualizacionCombos(const std::vector<Sucursal*>& sucursales);
    void mensajeConfirmacionConexion(QString mensaje, bool estado);

    /*Signals que permiten ir comunicandose con la UI para poder realizar las operaciones de eliminacion*/
    void logEliminacionGrafo(QString mensaje, QString color);
    void tiempoProcesoEliminacionGrafo(double milisegundos);

    /*Signals que permiten ir comunicandose con la UI para poder realizar las operaciones de modificacion*/
    void logModificacionGrafo(QString mensaje, QString color);
    void tiempoProcesoModificacionGrafo(double milisegundos);
    /*Metotodo que permite enviar la informacion de la sucursal encontrada*/
    void enviarInformacion(Sucursal* sucursal);
    /*Metotodo que permite enviar un mensaje de error*/
    void mensajeErrorModificar(QString mensaje);

    /*Metodo que permite viajar hacia otra sucursal*/
    void abrirSucursal(Sucursal * _sucursal, Grafo * redGrafo);

    /*Metodo que permite ir refrescando los datos de una sucursal*/
    void actualizarEnvio(QString idEnvio, QStringList idsPasados, QString idSiguiente);

    /*Metodo que permite enviar la descarga del graphviz del grafo*/
    void enviarGraphvizGrafo(std::string graph);
};

#endif // CONTROLADORNEGOCIO_H
