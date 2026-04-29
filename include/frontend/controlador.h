#ifndef CONTROLADOR_H
#define CONTROLADOR_H

#include <QObject>

/*Includes de backend*/
#include"gestorestructuras.h"

class Controlador : public QObject
{
    Q_OBJECT
public:
    explicit Controlador(QObject *parent = nullptr);
    ~Controlador();


    /*Metodo que permite evaluar el estado del boton para poder cerrar el archivo csv cargado*/
    void evaluarEstadoCerrarCsv();

    /*Metodo utilizado para poder refrescar los datos directamente de la vista del csv*/
    void verificarRefrescado();


    /*Metodo que permite rellenar los datos actualizados con los de la lista*/
    void actualizarDatosIngresados();

    /*Metodo que permite ordenar a la lista*/
    void ordenarListado(int orden);


private:
    GestorEstructuras * gestorBackend = nullptr;

    /*Metodos para insertar datos desde el csv*/

    void insertarListaCsv(const std::vector<QString> & data);

    void insertarArbolAvlCsv(const std::vector<QString> & data);

    void insertarArbolBCsv(const std::vector<QString> & data);

     void insertarArbolBMasCsv(const std::vector<QString> & data);

    /*Metodo que permite avisar para determinar si dejar o no descargar el log de errores*/
    void verificarErrores();

    /*Apartado de metodos auxiliares para poder insertar datos*/
    void insertarEnListas(const std::string &_nombre,const std::string &_codigoBarra, const std::string &_categoria, const std::string &_fechaExpiracion, const std::string &_marca, double _precio, int _stock);
    void insertarEnArbolAvl(const std::string &_nombre,const std::string &_codigoBarra, const std::string &_categoria, const std::string &_fechaExpiracion, const std::string &_marca, double _precio, int _stock);
    void insertarEnArbolB(const std::string &_nombre,const std::string &_codigoBarra, const std::string &_categoria, const std::string &_fechaExpiracion, const std::string &_marca, double _precio, int _stock);
    void insertarEnArbolBMas(const std::string &_nombre,const std::string &_codigoBarra, const std::string &_categoria, const std::string &_fechaExpiracion, const std::string &_marca, double _precio, int _stock);

    /*Metodos que permiten buscar datos por nombre*/
    void buscarAvlNombre(const std::string &nombre);
    void buscarListasNombre(const std::string &nombre);
    void buscarListasOrdenadaNombre(const std::string &nombre);
    void buscarListasNoOrdenadaNombre(const std::string &nombre);

    /*Metodos que permiten buscar datos por categoria*/
    void buscarListasCategoria(const std::string &categoria);
    void buscarListasOrdenadaCategoria(const std::string &categoria);
    void buscarListasNoOrdenadaCategoria(const std::string &categoria);
    void buscarBMasCategoria(const std::string &categoria);

    /*Metodos que permiten buscar datos por fecha*/
    void buscarBFecha(const std::string &limiteInferior, const std::string &limiteSuperior);
    void buscarListasFecha(const std::string &limiteInferior, const std::string &limiteSuperior);
    void buscarListaOrdenadaFecha(const std::string &limiteInferior, const std::string &limiteSuperior);
    void buscarListaNoOrdenadaFecha(const std::string &limiteInferior, const std::string &limiteSuperior);

    /*Metodos que permiten eliminar un producto*/
    void eliminarEnListas(const std::string &_codigoBarra);
    void eliminarEnArbolAvl(const std::string &_codigoBarra);
    void eliminarEnArbolB(const std::string &_codigoBarra);
    void eliminarEnArbolBMas(const std::string &_codigoBarra);


    /*Metodos que permiten listar los productos en orden alfabetico*/
    void listarAlfabeticoListas();
    void listarAlfabeticoAvl();


public slots:

    /*---METODO QUE ELIMINA POR COMPLETO TODO EL BACKEND CUANDO SE EXPORTA EL CSV---*/
    void limpiarDatos();

    /*Metodo que permite generar la logica de guardado del csv*/
    void guardarArchivoCsv();

    /*Metodo que permite procesar el csv*/
    void procesarCsv(const std::vector<QString> & data);

    /*Metodos que permiten realizar el CRUD de la aplicacion*/
    void insercionProducto(const std::string &_nombre,const std::string &_codigoBarra, const std::string &_categoria, const std::string &_fechaExpiracion, const std::string &_marca, const std::string &_precio, const std::string &_stock);
    void buscarPorNombre(const std::string &nombre);
    void buscarPorCategoria(std::string categoria);
    void buscarPorFecha(const std::string &limiteInferior, const std::string &limiteSuperior);
    void eliminarProducto(const std::string &codigo);
    void listarProductos();


    /*Metodos que permiten obtener las referencias de los arboles*/
    void obtenerArbolAvl();
    void obtenerArbolB();
    void obtenerArbolBMas();

    /*Metodos que permiten obtener el graphviz de los arboles*/
    void generarGraphArbolAvl();
    void generarGraphArbolB();
    void generarGraphArbolBMas();

    /*Metodo que permite obtener los datos para poder descargar el Log de errores*/
    void prepararLogParaDescarga();


    /*Apartado de metodos que permiten generar las pruebas con las busquedas de arboles*/

    /*Metodo que permite generar las consultas aleatorias por rango de fechas*/
    void pruebaAleatoriaFechas(int consultas,int veces, const std::string &limiteInferior, const std::string &limiteSuperior);

    /*Metodo que permite generar las consultas en extremos por rango de fechas*/
    void pruebaExtremosFechas(int consultas,int veces);

    /*Metodo que permite generar las consultas aleatorias por nombre*/
    void pruebaAleatoriaNombre(int consultas,int veces);

    /*Metodo que permite generar las consultas en extremos por nombre*/
    void pruebaExtremosNombre(int consultas,int veces);

    /*Metodo que permite generar las consultas aleatorias por categoria*/
    void pruebaAleatoriaCategoria(int consultas,int veces);

    /*Metodo que permite generar las consultas en extremos por categoria*/
    void pruebaExtremosCategoria(int consultas,int veces);

signals:

    /*Metodos que permiten enviar la informacion para poder generar el graphviz los arboles*/
    void enviarGraphvizArbolAvl(std::string arbol);
    void enviarGraphvizArbolB(std::string arbol);
    void enviarGraphvizArbolBMas(std::string arbol);

    /*Metodo que permite enviar al front el contenido para poder ser guardado*/
    void contenidoCsvListo(QString archivo);

    /*Metodo que permite refrescar los datos de la UI*/
    void refrescarDatos(bool estado);

    /*Metodo que permite activar o desactivar el boton para poder cerrar el csv*/
    void evaluarCerrarCsv(bool estado);

    /*Metodo que da la senial para poder determinar si hay errores y para avisar del csv*/
    void evaluarErroresLog(bool estado);

    /*Metodo utilizado para enviar hacia la UI el contenido a procesar para el errors.log*/
    void logDescargar(const QString &contenido);

    /*Metodos que permiten enviar la informacion para poder graficar los arboles*/
    void enviarArbolAvl(NodoAvl * arbol);
    void enviarArbolB(NodoB * arbol);
    void enviarArbolBMas(NodoBMas * arbol);


    /*Signals que permiten comunicarse con la pantalla del csv */
    void logArbolAvl(QString mensaje, QString color);
    void logArbolB(QString mensaje, QString color);
    void logArbolBMas(QString mensaje, QString color);
    void logLista(QString mensaje, QString color);

    void logCargaCsv(QString mensaje, QString color);

    /*Signal que permite setear el tiempo en el label*/
    void tiempoProceso(int estructura, double milisegundos);

    /*Fin de los Signals que permiten comunicarse con la pantalla del csv */


    /*Signals que permiten comunicarse con la pantalla de agregar */
    void logInsertArbolAvl(QString mensaje, QString color);
    void logInsertArbolB(QString mensaje, QString color);
    void logInsertArbolBMas(QString mensaje, QString color);
    void logInsertListaOrdenada(QString mensaje, QString color);
    void logInsertListaNoOrdenada(QString mensaje, QString color);

    /*Signal que permite setear el tiempo en el label*/
    void tiempoProcesoInsert (int estructura, double milisegundos);

    /*Fin de las Signals que permiten comunicarse con la pantalla de agregar */


    /*Signals que permiten comunicarse con la pantalla de buscar por nombre */
    void logBusquedaNombreArbolAvl(QString mensaje, QString color);
    void logBusquedaNombreListaOrdenada(QString mensaje, QString color);
    void logBusquedaNombreListaNoOrdenada(QString mensaje, QString color);

    /*Signal que permite setear el tiempo en el label*/
    void tiempoProcesoBusquedaNombre (int estructura, double milisegundos);

    /*Fin de las Signals que permiten comunicarse con la pantalla de buscar por nombrer */

    /*Signals que permiten comunicarse con la pantalla de buscar por nombre */
    void logBusquedaCategoriaArbolBMas(QString mensaje, QString color);
    void logBusquedaCategoriaListaOrdenada(QString mensaje, QString color);
    void logBusquedaCategoriaListaNoOrdenada(QString mensaje, QString color);

    /*Signal que permite setear el tiempo en el label*/
    void tiempoProcesoBusquedaCategoria (int estructura, double milisegundos);

    /*Fin de las Signals que permiten comunicarse con la pantalla de buscar por nombre*/


    /*Signals que permiten comunicarse con la pantalla de buscar por rango de fechas */
    void logBusquedaFechasArbolB(QString mensaje, QString color);
    void logBusquedaFechasListaOrdenada(QString mensaje, QString color);
    void logBusquedaFechasListaNoOrdenada(QString mensaje, QString color);

    /*Signal que permite setear el tiempo en el label*/
    void tiempoProcesoBusquedaFechas (int estructura, double milisegundos);

    /*Fin de las Signals que permiten comunicarse con la pantalla de buscar por nombre */



    /*Signals que permiten comunicarse con la pantalla de eliminar productos */
    void logEliminarArbolAvl(QString mensaje, QString color);
    void logEliminarArbolB(QString mensaje, QString color);
    void logEliminarArbolBMas(QString mensaje, QString color);
    void logEliminarListaOrdenada(QString mensaje, QString color);
    void logEliminarListaNoOrdenada(QString mensaje, QString color);

    /*Signal que permite setear el tiempo en el label*/
    void tiempoEliminarProceso(int estructura, double milisegundos);

    /*Fin de los Signals que permiten comunicarse con la pantalla de listar productos */

    /*Signals que permiten comunicarse con la pantalla de buscar por nombre */
    void logListarArbolAvl(QString mensaje, QString color);
    void logListarListaOrdenada(QString mensaje, QString color);
    void logListarListaNoOrdenada(QString mensaje, QString color);

    /*Signal que permite setear el tiempo en el label*/
    void tiempoProcesoListarNombre (int estructura, double milisegundos);

    /*Fin de las Signals que permiten comunicarse con la pantalla de listai productos */

    /*Apartado de metodos que permiten generar las pruebas con las busquedas de arboles*/
    void mostrarTiempoPruebasNombre(double milisegundos);
    void mostrarTiempoPruebasCategoria(double milisegundos);
    void mostrarTiempoPruebasFechas(double milisegundos);

};

#endif // CONTROLADOR_H
