#include "arbolbmas.h"
#include "deleteexception.h"
#include "insertexception.h"

/*Constructor del arbol B+*/
ArbolBMas::ArbolBMas(int _orden):
    orden(_orden),
    raiz(nullptr)
{

}

/*Destructor*/
ArbolBMas::~ArbolBMas(){
    if(raiz != nullptr){
        delete this->raiz;
    }
}

/*Metodo que permite generar el graphviz del arbol B+*/
std::string ArbolBMas::generarDot(){

    std::stringstream sStream;
    sStream << "digraph ArbolBMas {\n";
    sStream << "    rankdir=TB;\n";
    sStream << "    ranksep=2.5;\n";
    sStream << "    nodesep=0.5;\n";
    sStream << "    node [shape=record, style=filled, fillcolor=\"#dbeafe\", fontcolor=black, color=\"#1e40af\", fontname=\"Arial\"];\n";
    sStream << "    edge [color=\"#1e40af\"];\n\n";

    if (this->raiz != nullptr) {
        generarDotRecursivo(this->raiz, sStream);
    } else {
        sStream << "    nodoVacio [label=\" El arbol esta vacio \", fillcolor=\"#fee2e2\", shape=note];\n";
    }

    sStream << "}\n";
    return sStream.str();
}

/*--****------Apartado de metodos para poder generar el graphviz del arbol B+------****--*/
/*Metodo que permite generar el .dot recursivo*/
void ArbolBMas::generarDotRecursivo(NodoBMas* nodo, std::stringstream& sStream){

    if(!nodo){
        return;
    }

    sStream << "    \"nodo" << nodo << "\" [label=\"";

    int nClaves = nodo->getClaves().getLongitud();

    for (int i = 0; i < nClaves; i++) {
        /*Hijo izquierdo*/
        sStream << "<f" << i << "> | ";

        /*Valor del producto*/
        sStream << nodo->getClaves().getValor(i).getCategoria();
        sStream << " | ";
    }

    sStream << "<f" << nClaves << ">\"";

    /*Permite representar las hojas del arbol*/
    if (nodo->getEsHoja()) {
        sStream << ", color=\"#16a34a\", fillcolor=\"#f0fdf4\", penwidth=2";
    }

    sStream << "];\n"; // Cerramos la configuración del nodo

    /*Se conecta con los hijos o con la siguiente hoja*/
    if(!nodo->getEsHoja())
    {
        for (int i = 0; i < nodo->getHijos().getLongitud(); i++) {
            NodoBMas* hijo = nodo->getHijos().getValor(i);
            if (hijo != nullptr) {
                // Conectamos Padre -> Hijo
                sStream << "    \"nodo" << nodo << "\":f" << i
                        << " -> \"nodo" << hijo << "\";\n";

                generarDotRecursivo(hijo, sStream);
            }
        }
    }
    else
    {
        /*Genera el puntero hacia las hojas para la busqueda (el viaje de lado a lado)*/
        if (nodo->getSiguiente() != nullptr) {
            sStream << "    \"nodo" << nodo << "\""
                    << " -> \"nodo" << nodo->getSiguiente() << "\""
                    << " [color=\"#16a34a\", constraint=false, style=dashed, tailport=e, headport=w];\n";
        }
    }
}


/*--****------Apartado de metodos para poder generar el graphviz del arbol B+------****--*/

/*Metodo que permite obtener la raiz del arbol*/
NodoBMas* ArbolBMas::getRaiz(){
    return this->raiz;
}

/*Metodo que permite buscar por categoria (lista de productos por categoria)*/
/*
* La estrategia utilizada es transportarse por las conexiones que este arbol genera hacia los hijos
* de esta forma se puede bajar demasiado rapido sin recursividad y empezar a subir hasta toparse con algo que no esta
* ordenado alfabeticamente y rompe
*/
ListaEnlazada<Producto>  ArbolBMas::buscarPorCategoria(const std::string &categoriaBuscada){
    ListaEnlazada<Producto> resultados;

    if (this->raiz == nullptr) {
        return resultados;
    }

    NodoBMas* actual = this->raiz;

    /*Fase 1: Busqueda vertical. Directamente se baja por las rutas conectadas*/

    while (!actual->getEsHoja()) {
        int i = 0;
        int nClave = actual->getClaves().getLongitud();

        while (i < nClave) {
            Producto pActual = actual->getClaves().getValor(i);

            /*Se busca solo por la categoria para poder listar*/
            if (categoriaBuscada <= pActual.getCategoria()) {
                break;
            }

            i++;
        }

        actual = actual->getHijos().getValor(i);
    }

    /*Fase 2: recorrido horizontal. Se va buscando la hoja donde podria estar la categoria*/
    bool continuarBuscando = true;

    while (actual != nullptr && continuarBuscando) {
        int nClave = actual->getClaves().getLongitud();

        for (int i = 0; i < nClave; i++) {
            Producto pActual = actual->getClaves().getValor(i);

            if (pActual.getCategoria() == categoriaBuscada) {
                resultados.insertar(resultados.getLongitud(), pActual);
            }
            else if (pActual.getCategoria() > categoriaBuscada) {

                /*Ya que los datos estan ordenados por categoria alfabeticamente se termina*/

                continuarBuscando = false;
                break;
            }
        }

        if (continuarBuscando) {
            actual = actual->getSiguiente();
        }
    }

    return resultados;
}

/*Metodo que permite insertar un producto*/
void ArbolBMas::insertar(const Producto &producto){

    if (yaExiste(this->raiz, producto)) {
        throw InsertException("El codigo de barras { " +
                              producto.getCodigoBarra() + " } ya existe para el producto: " +
                              producto.getNombre() + " [ARBOL B+]");
    }

    /*Caso base arbol vacio*/
    if(raiz == nullptr){
        this->raiz = new NodoBMas(true);
        insertarEnNodo(raiz, producto);
        return;
    }

    /*Validacion si la raiz del arbol esta llena este crece de altura*/
    if (this->raiz->getClaves().getLongitud() >= orden) {

        NodoBMas* nuevaRaiz = new NodoBMas(false);

        /*Raiz mas antigua es el primer hijo*/
        nuevaRaiz->getHijos().insertar(0, this->raiz);

        if (this->raiz->getEsHoja()) {
            dividirHoja(this->raiz, nuevaRaiz, 0);
        } else {
            dividirInterno(this->raiz, nuevaRaiz, 0);
        }

        this->raiz = nuevaRaiz;

    }

    insertarRecursivo(this->raiz, nullptr, producto, -1);
}

/*--****----Apartado de metodos que permiten insertar en el arbol B+---****--*/

/*Metodo que permite insertar datos en un nodo del arbol*/
/*
* Para el caso de este arbol lo que pasa es que inserta en las hojas y conserva referencias arriba es decir genera duplicidad
* pero es mas apto para poder almacenar datos y remover datos
*/
void ArbolBMas::insertarEnNodo(NodoBMas* nodo, const Producto &producto){

    int i = 0;

    int nClave = nodo->getClaves().getLongitud();

    while (i < nClave) {
        Producto actual = nodo->getClaves().getValor(i);

        if (producto.getCategoria() < actual.getCategoria()) {
            break;
        }

        if (producto.getCategoria() == actual.getCategoria() &&
            producto.getCodigoBarra() < actual.getCodigoBarra()){
            break;
        }

        i++;

    }

    nodo->getClaves().insertar(i, producto);
}

/*Metodo que permite generar la recursividad para poder insertar en el lugar correcto*/
void ArbolBMas::insertarRecursivo(NodoBMas *nodo, NodoBMas *padre, Producto producto, int indiceEnPadre) {

    /*Si es hoja simplemente manda a insertar dentro de la lista*/
    if (nodo->getEsHoja()) {
        insertarEnNodo(nodo, producto);
    } else {

        /*Sino busca por que hijo bajar*/
        int i = 0;
        int nClave = nodo->getClaves().getLongitud();

        while (i < nClave) {
            Producto actual = nodo->getClaves().getValor(i);
            if (producto.getCategoria() < actual.getCategoria()) {
                break;
            }

            if (producto.getCategoria() == actual.getCategoria() &&
                producto.getCodigoBarra() < actual.getCodigoBarra()) {
                break;
            }
            i++;
        }

        NodoBMas* hijo = nodo->getHijos().getValor(i);

        /*Division si el hijo esta lleno se divide antes de entrar*/
        /*Fue como yo lo pense para evitar andar haciendo tanto merge descontrolado*/
        if (hijo->getClaves().getLongitud() >= orden) {
            if (hijo->getEsHoja()) {
                dividirHoja(hijo, nodo, i);
            } else {
                dividirInterno(hijo, nodo, i);
            }

            // Re-evaluar por cuál hijo bajar tras la división
            Producto claveSubida = nodo->getClaves().getValor(i);
            if (producto.getCategoria() > claveSubida.getCategoria() ||
                (producto.getCategoria() == claveSubida.getCategoria() &&
                 producto.getCodigoBarra() >= claveSubida.getCodigoBarra())) {
                hijo = nodo->getHijos().getValor(i + 1);
            }
        }

        insertarRecursivo(hijo, nodo, producto, i);
    }
}


/*Metodo que permite generar la division de las hojas cuando se sobrepasa el limite*/
void ArbolBMas::dividirHoja(NodoBMas* hoja, NodoBMas* padre, int indiceEnPadre) {

    NodoBMas* nuevaHoja = new NodoBMas(true);
    int mitad = orden / 2;

    /*Se conecta la nueva hoja a la lista enlazada*/
    nuevaHoja->setSiguiente(hoja->getSiguiente());
    hoja->setSiguiente(nuevaHoja);

    /*Se mueve la mitad derecha de productos a la nueva hoja*/
    while (hoja->getClaves().getLongitud() > mitad) {

        Producto product = hoja->getClaves().getValor(mitad);

        nuevaHoja->getClaves().insertar(nuevaHoja->getClaves().getLongitud(), product);

        hoja->getClaves().eliminar(mitad);
    }

    /*El primer elemento de la nueva hoja sube al padre es decir que se copia*/
    padre->getClaves().insertar(indiceEnPadre, nuevaHoja->getClaves().getValor(0));
    padre->getHijos().insertar(indiceEnPadre + 1, nuevaHoja);
}

/*Metodo que permite dividir las claves a la mitad para poder generar la integracion*/

void ArbolBMas::dividirInterno(NodoBMas* interno, NodoBMas* padre, int indiceEnPadre) {
    NodoBMas* nuevoInterno = new NodoBMas(false);

    /*Se obteniene la mitad de la lista de claves*/
    int mitad = orden / 2;

    Producto subido = interno->getClaves().getValor(mitad);
    interno->getClaves().eliminar(mitad);


    /*Se mueven las llaves restantes al nuevo nodo*/
    while (interno->getClaves().getLongitud() > mitad) {
        Producto product = interno->getClaves().getValor(mitad);
        nuevoInterno->getClaves().insertar(nuevoInterno->getClaves().getLongitud(), product);
        interno->getClaves().eliminar(mitad);
    }

    /*Se mueven a los hijos al nuevo nodo*/
    /*Se genera una limpieza en la parte derehca del nodo y se le pasa la carga al hermano*/
    while (interno->getHijos().getLongitud() > mitad + 1) {
        NodoBMas* hijo = interno->getHijos().getValor(mitad + 1);
        nuevoInterno->getHijos().insertar(nuevoInterno->getHijos().getLongitud(), hijo);
        interno->getHijos().eliminar(mitad + 1);
    }

    padre->getClaves().insertar(indiceEnPadre, subido);
    padre->getHijos().insertar(indiceEnPadre + 1, nuevoInterno);
}

/*Metodo que permite conservar la integridad del arbol ya que hace que el codigo de barras sea unico*/
/*
*La tactica de busqueda es simple ya que se aprovecha la caracteristica de este arbol de ser super rapido
*de esta forma se permite lograr buscar super rapido gracias al nodo siguiente que interconecta
*
*/
bool ArbolBMas::yaExiste(NodoBMas* nodoRaiz, const Producto &producto){

    if (nodoRaiz == nullptr) {
        return false;
    }

    NodoBMas* actual = nodoRaiz;

    /*Se baja en linea recta hasta llegar a la primera hoja (EFICIENCIA)*/
    while (!actual->getEsHoja()) {
        actual = actual->getHijos().getValor(0);
    }

    /*Si no esta directamente en una hoja se tiene que seguir recorriendo el arbol buscando una clave*/
    /*
    * La tactica esta en que se siguen recorriendo las hojas usando la lista enlazada conectada
    */
    while (actual != nullptr) {
        int nClaves = actual->getClaves().getLongitud();

        for (int i = 0; i < nClaves; i++) {
            if (actual->getClaves().getValor(i).getCodigoBarra() == producto.getCodigoBarra()) {
                return true;
            }
        }

        // Se salta a la siguiente hoja esto es lo que lo hace super rapido
        actual = actual->getSiguiente();
    }

    return false;
}

/*--****----Fin del Apartado de metodos que permiten insertar en el arbol B+---****--*/



/*--****----Apartado de metodos que permiten eliminar en el arbol B+---****--*/

/*----Metodo que permite eliminar un dato del arbol-----*/
void ArbolBMas::eliminar(const std::string& codigoBarra){

    if (this->raiz == nullptr) {
        throw DeleteException("El arbol esta vacio. No hay datos para eliminar.");
    }

    /*Es el producto a ubicar para poderlo ubicar*/
    Producto productoAEliminar;
    bool encontrado = false;


    NodoBMas* actual = this->raiz;


    /* Bajamos en linea recta hasta la primera hoja (extremo izquierdo) */
    while (!actual->getEsHoja()) {
        actual = actual->getHijos().getValor(0);
    }

    /* Recorremos las hojas horizontalmente buscando el codigo de barras */
    while (actual != nullptr && !encontrado) {
        int nClaves = actual->getClaves().getLongitud();
        for (int i = 0; i < nClaves; i++) {
            if (actual->getClaves().getValor(i).getCodigoBarra() == codigoBarra) {
                productoAEliminar = actual->getClaves().getValor(i);
                encontrado = true;
                break;
            }
        }
        if (!encontrado) {
            actual = actual->getSiguiente();
        }
    }

    /* Si terminamos de buscar y no estaba, lanzamos la excepcion */
    if (!encontrado) {
        throw DeleteException("El producto con el codigo de barra {" + codigoBarra + "} no existe. [ARBOL B+]");
    }

    /* Ahora con el producto completo se determina por donde bajar */
    eliminarRecursivo(this->raiz, nullptr, -1, productoAEliminar);

    /*Caso especial: En el que la raiz se queda sin claves despues de rebalancear*/

    /*Este aco ocurre si no es una hoja. Asi su hijo unico se convierte en la nueva raiz*/

    if (this->raiz->getClaves().getLongitud() == 0 && !this->raiz->getEsHoja()) {
        NodoBMas* viejaRaiz = this->raiz;

        /* Se rescata al ultimo hijo para mantener las referencias activas */
        this->raiz = viejaRaiz->getHijos().getValor(0);

        /*Se desvincula al hijo de la lista de la vieja raiz.
        *
        * Este problema surge por mi forma de eliminar los nodos ya que estos borran recursivamente los nodos
        * por lo tanto estoy obligando a eliminar antes todo
        */
        viejaRaiz->getHijos().eliminar(0);

        delete viejaRaiz;
    }

}

/*Metodo que ptermie eliminar de forma recursiva. Propagando hacia arriba el rebalanceo del arbol*/
bool ArbolBMas::eliminarRecursivo(NodoBMas* nodo, NodoBMas* padre, int indiceEnPadre, const Producto& producto) {

    int nClaves = nodo->getClaves().getLongitud();
    int i = 0;

    /*Se busca el indice a eliminar*/
    while (i < nClaves) {
        Producto actual = nodo->getClaves().getValor(i);
        if (producto.getCategoria() < actual.getCategoria() ||
            (producto.getCategoria() == actual.getCategoria() && producto.getCodigoBarra() < actual.getCodigoBarra())) {
            break;
        }
        i++;
    }

    /*Caso 1: se esta en una hoja*/
    if (nodo->getEsHoja()) {

        /*Verificacion si el producto esta en las hojas*/
        for (int j = 0; j < nClaves; j++) {
            if (nodo->getClaves().getValor(j).getCodigoBarra() == producto.getCodigoBarra()) {
                nodo->getClaves().eliminar(j);
                break;
            }
        }

        /*Al regresar el padre revisara si la hoja necesita rebalanceo*/
        return false;
    }

    /*En el caso de no ser hoja se sigue bajando por el hijo*/
    /*Verificacion de desbordamiento tras eliminar (recursion)*/
    NodoBMas* hijo = nodo->getHijos().getValor(i);

    /*Se captura lo que esta hasta abajo*/
    bool eliminadoAbajo = eliminarRecursivo(hijo, nodo, i, producto);

    /*Solo se intenta rebalancear si se elimino algo realmente*/
    if (eliminadoAbajo) {
        int minimoClaves = orden / 2;
        if (hijo->getClaves().getLongitud() < minimoClaves) {
            balancearNodo(nodo, hijo, i);
        }
    }

    /*Se pasa el mensaje hacia arriba para que el padre sepa y se propague*/
    return eliminadoAbajo;
}

/*Metodo que maneja la forma en prestar y fusiones cuando un nodo se queda sin el minimo de claves*/
void ArbolBMas::balancearNodo(NodoBMas* padre, NodoBMas* hijo, int indiceHijo){

    /*Localizacion de los hermanos*/
    int minimoClaves = orden / 2;

    NodoBMas* hermanoIzquierdo = (indiceHijo > 0) ? padre->getHijos().getValor(indiceHijo - 1) : nullptr;
    NodoBMas* hermanoDerecho = (indiceHijo < padre->getHijos().getLongitud() - 1) ? padre->getHijos().getValor(indiceHijo + 1) : nullptr;

    /*Caso 1: Intento de prestar del hermano izquierdo*/
    if (hermanoIzquierdo != nullptr && hermanoIzquierdo->getClaves().getLongitud() > minimoClaves) {

        /*Se toma la ultima clave de izquierdo*/
        int ultimaPosicion = hermanoIzquierdo->getClaves().getLongitud() - 1;
        Producto prestado = hermanoIzquierdo->getClaves().getValor(ultimaPosicion);
        hermanoIzquierdo->getClaves().eliminar(ultimaPosicion);

        /*Se busca al principio del hijo que tiene desborde*/
        hijo->getClaves().insertar(0, prestado);

        /*En el dado caso de que no sean hojas se le pasa el hijo correspondiente*/
        if (!hijo->getEsHoja()) {
            NodoBMas* hijoPrestado = hermanoIzquierdo->getHijos().getValor(hermanoIzquierdo->getHijos().getLongitud() - 1);
            hermanoIzquierdo->getHijos().eliminar(hermanoIzquierdo->getHijos().getLongitud() - 1);
            hijo->getHijos().insertar(0, hijoPrestado);
        }

        /*Se actualiza la clave del padre que se divide en dos*/
        padre->getClaves().insertar(indiceHijo - 1, hijo->getClaves().getValor(0));
        padre->getClaves().eliminar(indiceHijo);
        return;
    }

    /*Caso 2: En el que se intenta prestar al hermano derecho*/
    if (hermanoDerecho != nullptr && hermanoDerecho->getClaves().getLongitud() > minimoClaves) {

        /*Se toma la primera clave del derecho*/
        Producto prestado = hermanoDerecho->getClaves().getValor(0);
        hermanoDerecho->getClaves().eliminar(0);

        /*Se inserta al final del hijo*/
        hijo->getClaves().insertar(hijo->getClaves().getLongitud(), prestado);

        if (!hijo->getEsHoja()) {
            NodoBMas* hijoPrestado = hermanoDerecho->getHijos().getValor(0);
            hermanoDerecho->getHijos().eliminar(0);
            hijo->getHijos().insertar(hijo->getHijos().getLongitud(), hijoPrestado);
        }

        /*Se actualiza la clave del padre*/
        padre->getClaves().insertar(indiceHijo, hermanoDerecho->getClaves().getValor(0));
        padre->getClaves().eliminar(indiceHijo + 1);
        return;
    }

    /*Caso 3: Si nadie puede prestar se opta por fusionar*/
    /*Camino elegido de primero es intentar fusionar el hermano izquierdo*/
    if (hermanoIzquierdo != nullptr) {
        fusionarNodos(padre, indiceHijo - 1, hermanoIzquierdo, hijo);
    } else if (hermanoDerecho != nullptr) {
        fusionarNodos(padre, indiceHijo, hijo, hermanoDerecho);
    }
}

/*---Metodo que permite unir dos nodos hermanos y eliminar la clave separadora del padre---*/
void ArbolBMas::fusionarNodos(NodoBMas* padre, int indiceSeparador, NodoBMas* izquierdo, NodoBMas* derecho) {

    /*Si no son hojas se baja a la clave del padre*/
    if (!izquierdo->getEsHoja()) {
        Producto clavePadre = padre->getClaves().getValor(indiceSeparador);
        izquierdo->getClaves().insertar(izquierdo->getClaves().getLongitud(), clavePadre);
    }

    /*Se pasan todas las claves del nodo derecho al izquierdo*/
    int nClavesDerecho = derecho->getClaves().getLongitud();
    for (int i = 0; i < nClavesDerecho; i++) {
        izquierdo->getClaves().insertar(izquierdo->getClaves().getLongitud(), derecho->getClaves().getValor(0));
        derecho->getClaves().eliminar(0);
    }

    /*Si no son hijos, se pasan los hijos tambien*/
    if (!izquierdo->getEsHoja()) {

        int nHijosDerecho = derecho->getHijos().getLongitud();
        for (int i = 0; i < nHijosDerecho; i++) {
            izquierdo->getHijos().insertar(izquierdo->getHijos().getLongitud(), derecho->getHijos().getValor(0));
            derecho->getHijos().eliminar(0);
        }

    } else {
        izquierdo->setSiguiente(derecho->getSiguiente());
    }

    /*Se elimina la clave separada del padre al puntero del nodo derecho*/
    padre->getClaves().eliminar(indiceSeparador);
    padre->getHijos().eliminar(indiceSeparador + 1);

    delete derecho;
}


/*--****----Fin del Apartado de metodos que permiten eliminar en el arbol B+---****--*/

