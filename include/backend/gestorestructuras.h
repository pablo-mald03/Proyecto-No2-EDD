#ifndef GESTORESTRUCTURAS_H
#define GESTORESTRUCTURAS_H

//Includes de la clase
#include "arbolavl.h"
#include "arbolb.h"
#include "arbolbmas.h"
#include "erroreslectura.h"
#include"listaenlazada.h"
#include"producto.h"
#include <QStringList>
#include <QDate>

/*Arboles*/
//#include"arbolavl.h"

class GestorEstructuras
{
public:
    GestorEstructuras();
    ~GestorEstructuras();

    /*Metodos para insertar datos en las estructuras provinientes del csv*/
    void insertarListasCsv(const std::string &nombre,const std::string &key,const std::string &categoria, const std::string &fecha, const std::string &marca, double precio, int stock);

    /*Metodo que permite insertar datos en el arbol AVL*/
    void insertarArbolAvl(const std::string &nombre, const std::string &key, const std::string &categoria, const std::string &fecha, const std::string &marca, double precio, int stock);

    /*Metodo que permite insertar datos en el arbol B*/
    void insertarArbolB(const std::string &nombre, const std::string &key, const std::string &categoria, const std::string &fecha, const std::string &marca, double precio, int stock);

    /*Metodo que permite insertar datos en el arbol B+*/
    void insertarArbolBMas(const std::string &nombre, const std::string &key, const std::string &categoria, const std::string &fecha, const std::string &marca, double precio, int stock);


    /*Metodo que permite eliminar datos en el arbol AVL*/
    void eliminarArbolAvl(const std::string &key);

    /*Metodo que permite eliminar datos en el arbol B*/
    void eliminarArbolB(const std::string &key);

    /*Metodo que permite eliminar datos en el arbol B+*/
    void eliminarArbolBMas(const std::string &key);

    /*Metodo que permite eliminar los datos en la lista ordenada*/
    void eliminarListaOrdenada(const std::string &key);

    /*Metodo que permite eliminar los datos en la lista no ordenada*/
    void eliminarListaNoOrdenada(const std::string &key);

    /*Metodo para insertar en lista no ordenada*/
    void insertarListaNoOrdenada(const std::string &nombre,const std::string &key,const std::string &categoria, const std::string &fecha, const std::string &marca, double precio, int stock);

    /*Metodo para insertar en lista no ordenada*/
    void insertarListaOrdenada(const std::string &nombre,const std::string &key,const std::string &categoria, const std::string &fecha, const std::string &marca, double precio, int stock);

    /*Metodo de validacion del csv delegado para validar*/
    void validarCsv(const QStringList& columnas, int fila);

    /*Metodo para agregar errores al log*/
    void agregarErrorLista(const std::string mensaje, int fila);

    /*Metodo que retorna el contenido del log de errores*/
    QString generarContenidoLog();

    /*Metodo que permite obtener la lista de errores*/
    ListaEnlazada<ErroresLectura>* getListaErrores();

    /*Metodo para saber si tiene errores la lista*/
    bool tieneErrores() const;

    /*Metodo utilizado para poder ordenar las listas acorde a los diferentes parametros*/
    void generarListaOrdenada(int criterio);

    /*Metodo que permite ordenar la lista acorde a un parametro (solo orden)*/
    void ordenarLista(int criterio);

    /*Metodos getter y setter de la flag*/
    void setCargoArchivo(bool carga);
    bool getCargoArchivo();

    /*Metodo que retorna a la lista No ordenada*/
    ListaEnlazada<Producto> * getListaNoOrdenada();

    /*Metodo que permite exportar la lista al csv*/
    std::string serializarListaCsv();

    /*Metodo que permite obtener la raiz del arbol AVL*/
    NodoAvl * getRaizArbolAvl();

    /*Metodo que permite obtener la raiz del arbol B*/
    NodoB * getRaizArbolB();

    /*Metodo que permite obtener la raiz del arbol B+*/
    NodoBMas * getRaizArbolBMas();

    /*Metodo que permite obtener el graphviz del arbol AVL*/
    std::string obtenerGraphvizAvl();

    /*Metodo que permite obtener el graphviz del arbol B*/
    std::string obtenerGraphvizB();

    /*Metodo que permite obtener el graphviz del arbol B+*/
    std::string obtenerGraphvizBMas();

    /*Metodo que permite validar la insercion*/
    void validarInsercion(const std::string &_nombre,
                          const std::string &_codigoBarra,
                          const std::string &_categoria,
                          const std::string &_fechaExpiracion,
                          const std::string &_marca, const std::string &_precio,
                          const std::string &_stock);


    /*Metodos de busqueda de datos por nombre*/
    ListaEnlazada<Producto> buscarProductoAvl(const std::string& nombre);
    ListaEnlazada<Producto> buscarProductoListaOrdenada(const std::string& nombre);
    ListaEnlazada<Producto> buscarProductoListaNoOrdenada(const std::string& nombre);

    /*Metodos de busqueda de datos por categoria*/
    ListaEnlazada<Producto> buscarProductoBMas(const std::string& categoria);
    ListaEnlazada<Producto> buscarProductoCategoriaListaOrdenada(const std::string& categoria);
    ListaEnlazada<Producto> buscarProductoCategoriaListaNoOrdenada(const std::string& categoria);

    /*Metodos de busqueda de datos por fecha*/
    ListaEnlazada<Producto> buscarProductoB(const std::string &limiteInferior, const std::string &limiteSuperior);
    ListaEnlazada<Producto> buscarProductoFechasListaOrdenada(const std::string &limiteInferior, const std::string &limiteSuperior);
    ListaEnlazada<Producto> buscarProductoFechasListaNoOrdenada(const std::string &limiteInferior, const std::string &limiteSuperior);


    /*Metodo que permite listar en orden alfabetico los productos almacenados en el arbol AVL*/
    ListaEnlazada<Producto> listarProductosAvl();
    ListaEnlazada<Producto> listarProductosOrdenados();
    ListaEnlazada<Producto> listarProductosNoOrdenados();

    /*Metodo que permite obtener los productos en los extremos de la lista*/
    ListaEnlazada<Producto> getProductosExtremos();

    /*Metodo que permite obtener los productos aleatoriamente en un intervalo de productos*/
    ListaEnlazada<Producto> getProductosIntervalo(const Producto &productoInferior,const Producto &productoSuperior, int orden);

    /*Metodo que permite obtener dos rangos aleatoriamente*/
    ListaEnlazada<Producto> getRangosAleatorios();

    /*Metodo que permite obtener los extremos por intevalos (especializados para el arbol B)*/
    ListaEnlazada<Producto> getProductosExtremosIntervalo();

private:

    /*Arbol AVL*/
    ArbolAvl * arbolAvl = nullptr;

    /*Arbol B*/
    ArbolB * arbolB = nullptr;

    /*Arbol B+*/
    ArbolBMas * arbolBMas = nullptr;

    /*Atributos de la clase gestor*/
    ListaEnlazada<Producto> *listaNoOrdenada = nullptr;
    ListaEnlazada<Producto> * listaOrdenada = nullptr;

    /*Lista de errores*/
    ListaEnlazada<ErroresLectura> * listaErrores = nullptr;

    /*Atributo flag de carga de csv para saber si guardar o refrescar*/
    bool cargoArchivo;

    /*Metodo delegado para poder validar la fecha*/
    bool esFechaISO(const QString& fecha);

    /*Metodo que permite verificar la integridad de la listaEnlazada no ordenada*/
    bool existeProductoListaNoOrdenada(const std::string &codigo);

    /*Metodo que permite verificar la integridad de la listaEnlazada ordenada*/
    bool existeProductoListaOrdenada(const std::string &codigo);

};

#endif // GESTORESTRUCTURAS_H
