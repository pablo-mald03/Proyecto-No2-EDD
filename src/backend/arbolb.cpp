#include "arbolb.h"
#include "deleteexception.h"
#include "insertexception.h"

/*Constructor del arbol se deja el grado minimo del arbol a eleccion*/
ArbolB::ArbolB(int _t):
    raiz(nullptr),
    t(_t)
{

}

/*Destructor*/
ArbolB::~ArbolB(){

    /*Limpieza recursiva*/
    if(this->raiz != nullptr){
        delete this->raiz;
        this->raiz = nullptr;
    }
}

/*Metodo que permite retornar la raiz del arbol B*/
NodoB * ArbolB::getRaiz(){
    return this->raiz;
}

/*Metodo que permite generar el graphviz del arbol B*/
std::string ArbolB::generarDot(){

    std::stringstream sStream;
    sStream << "digraph ArbolB {\n";
    sStream << "    rankdir=TB;\n";
    sStream << "    ranksep=2.5;\n";
    sStream << "    nodesep=0.8;\n";
    sStream << "    node [shape=record, style=filled, fillcolor=\"#dbeafe\", fontcolor=black, color=black, fontname=\"Arial\"];\n";
    sStream << "    edge [color=black];\n\n";

    if (this->raiz != nullptr) {
        generarDotRecursivo(this->raiz, sStream);
    }
    else{
        sStream << "    nodoVacio [label=\" El árbol está vacío \", fillcolor=\"#fee2e2\", shape=note];\n";
    }

    sStream << "}\n";
    return sStream.str();
}

/*Metodo que permite generar el .dot recursivo para el arbol y que se pueda graficar*/
void ArbolB::generarDotRecursivo(NodoB* nodo, std::stringstream& sStream){
    if(nodo == nullptr){
        return;
    }

    sStream << "    nodo" << nodo << " [label=\"";

    int n = nodo->getClaves().getLongitud();
    for (int i = 0; i < n; ++i) {
        sStream << "<f" << i << "> |";

        Producto p = nodo->getClaves().getValor(i);
        sStream << " " << p.getFechaExpiracion()<< " ";

        sStream << "|";
    }
    sStream << "<f" << n << ">\"];\n";

    if (!nodo->getEsHoja()) {
        for (int i = 0; i <= n; ++i) {
            if (i < nodo->getHijos().getLongitud()) {
                NodoB* hijo = nodo->getHijos().getValor(i);
                if (hijo != nullptr) {

                    sStream << "    \"nodo" << nodo << "\":f" << i << " -> \"nodo" << hijo << "\";\n";
                    generarDotRecursivo(hijo, sStream);
                }
            }
        }
    }
}


/*Metodo que permite insertar un nuevo producto en un arbol. Maneja la integridad*/
void ArbolB::insertar(const Producto &producto){

    if (existeCodigo(this->raiz, producto.getCodigoBarra())) {
        throw InsertException("El codigo de barras { " +
                              producto.getCodigoBarra() + " } ya existe para el producto: " +
                              producto.getNombre() + " [ARBOL B]");
    }

    /*Insercion normal*/
    this->insertarNuevo(producto);
}


/*Metodo que permite dividir a los hijos del arbol para ir generando la funcionalidad de ir prestando hijos*/
void ArbolB::dividirHijo(NodoB* padre, int i, NodoB* lleno){

    /*Nuevo nodo que recibe la mitad*/
    NodoB* nuevo = new NodoB(lleno->getEsHoja());

    /*Se pasan las ultimas claves al nuevo nodo*/
    for (int j = 0; j < this->t - 1; j++) {
        Producto p = lleno->getClaves().getValor(this->t);
        nuevo->getClaves().insertarAtras(p);
        lleno->getClaves().eliminar(this->t);
    }

    /*Si no es hoja tambien se mueven los hijos*/
    if (!lleno->getEsHoja()) {
        for (int j = 0; j < this->t; j++) {
            NodoB* h = lleno->getHijos().getValor(this->t);
            nuevo->getHijos().insertarAtras(h);
            lleno->getHijos().eliminar(this->t);
        }
    }


    /*Se inserta el nuevo hermano en la lista de hijos del padre*/
    padre->getHijos().insertar(i + 1, nuevo);


    /*Se sube la clave que quedo en el centro (Hacia el padre)*/
    Producto mediana = lleno->getClaves().getValor(t - 1);
    padre->getClaves().insertar(i, mediana);
    lleno->getClaves().eliminar(t - 1);
}

/*Metodo que permite insertar en la lista de claves que tienen los nodos del arbol*/
/*
*  Se busca de derecha a izquierda (para mantener orden)
*/
void ArbolB::insertarNoLleno(NodoB* nodo, const Producto &producto){
    int i = nodo->getClaves().getLongitud() - 1;

    /*Evaluacion si el nodo es hoja*/
    if(nodo->getEsHoja()){

        /*Es la simple evaluacion para saber donde se ordena por menor fecha*/
        while (i >= 0) {

            Producto actual = nodo->getClaves().getValor(i);

            if (producto.getFechaExpiracion() < actual.getFechaExpiracion() ||
                (producto.getFechaExpiracion() == actual.getFechaExpiracion() && producto.getCodigoBarra() < actual.getCodigoBarra())) {
                i--;
            } else {
                break;
            }
        }

        nodo->getClaves().insertar(i + 1, producto);
    }
    else{
        /*Caso en el que el nodo no es hoja*/


        /*Caso de busqueda por cual nodo bajar*/
        while (i >= 0) {

            Producto actual = nodo->getClaves().getValor(i);
            if (producto.getFechaExpiracion() < actual.getFechaExpiracion() ||
                (producto.getFechaExpiracion() == actual.getFechaExpiracion() && producto.getCodigoBarra() < actual.getCodigoBarra())) {
                i--;
            } else {
                break;
            }
        }

        i++; //Este es el indice ya del hijito

        /*Se evalua si el hijo esta lleno se divide primero*/

        if (nodo->getHijos().getValor(i)->getClaves().getLongitud() == (2 * (this->t) - 1)) {

            dividirHijo(nodo, i, nodo->getHijos().getValor(i));

            Producto medianaSubida = nodo->getClaves().getValor(i);

            if (producto.getFechaExpiracion() > medianaSubida.getFechaExpiracion() ||
                (producto.getFechaExpiracion() == medianaSubida.getFechaExpiracion() && producto.getCodigoBarra() > medianaSubida.getCodigoBarra())) {
                i++;
            }
        }

        insertarNoLleno(nodo->getHijos().getValor(i), producto);
    }
}



/*Metodo que permite insertar datos al arbol B*/
void ArbolB::insertarNuevo(const Producto &producto){

    if(this->raiz == nullptr){
        this->raiz = new NodoB(true);
        this->raiz->getClaves().insertarAtras(producto);
        return;
    }

    /*Verificacion si la lista esta llena (supero el limite de claves)*/
    if (raiz->getClaves().getLongitud() == (2 * t - 1)) {

        NodoB* nuevaRaiz = new NodoB(false);
        nuevaRaiz->getHijos().insertarAtras(this->raiz);

        /*Se divide la raiz y se busca hacia donde hacer el merge*/
        dividirHijo(nuevaRaiz, 0, this->raiz);

        int i = 0;

        Producto mediana = nuevaRaiz->getClaves().getValor(0);

        /*Mi parametro es la fecha y la primary key*/
        if (producto.getFechaExpiracion() > mediana.getFechaExpiracion() ||
            (producto.getFechaExpiracion() == mediana.getFechaExpiracion() && producto.getCodigoBarra() > mediana.getCodigoBarra())) {
            i++;
        }

        /*Se actualiza la raiz del arbol*/
        insertarNoLleno(nuevaRaiz->getHijos().getValor(i), producto);
        this->raiz = nuevaRaiz;
    }
    else{
        /*Si no esta lleno simplemente se inserta*/
        insertarNoLleno(this->raiz, producto);
    }
}


/*----***---Metodos de busqueda---***----*/

/*Metodo que permite validar la integridad*/

bool ArbolB::existeCodigo(NodoB* nodo, const std::string &codigo){
    if(nodo == nullptr){
        return false;
    }

    /*Se revisan las claves del nodo raiz actual*/
    for (int i = 0; i < nodo->getClaves().getLongitud(); i++) {
        if (nodo->getClaves().getValor(i).getCodigoBarra() == codigo) {
            return true;
        }
    }

    /*Se busca en los hijos de forma recursiva*/
    if (!nodo->getEsHoja()) {
        for (int i = 0; i < nodo->getHijos().getLongitud(); i++) {
            if (existeCodigo(nodo->getHijos().getValor(i), codigo)) {
                return true;
            }
        }
    }

    return false;
}


/*----***---Metodos de busqueda---***----*/

/* Metodo publico que inicializa la busqueda y retorna la lista de productos en el rago de fechas */
ListaEnlazada<Producto> ArbolB::buscarRango(const std::string& inicio, const std::string& fin) {
    ListaEnlazada<Producto> resultados;
    buscarRangoAux(this->raiz, inicio, fin, resultados);
    return resultados;
}

/*Metodo auxiliar recursivo que permite buscar los productos en el rango de fechas establecido*/
/*Es un recorrido inorden*/

void ArbolB::buscarRangoAux(NodoB* nodo, const std::string& inicio, const std::string& fin, ListaEnlazada<Producto>& resultados) {
    if (nodo == nullptr) {
        return;
    }

    int i = 0;
    int numClaves = nodo->getClaves().getLongitud();

    for (i = 0; i < numClaves; i++) {
        Producto product = nodo->getClaves().getValor(i);

        /*Evalua si no es hoja y si la fecha es mayor al nodo inicial*/
        if (!nodo->getEsHoja() && product.getFechaExpiracion() >= inicio) {
            buscarRangoAux(nodo->getHijos().getValor(i), inicio, fin, resultados);
        }

        /*Evalua si la clave esta dentro del rango y se agrega */
        if (product.getFechaExpiracion() >= inicio && product.getFechaExpiracion() <= fin) {
            resultados.insertarAtras(product);
        }

        /*Alternativa efectiva*/
        /*Conciste en cortar la ejecucion si se sale del rango para evitar que se recorra todo el arbol*/
        if (product.getFechaExpiracion() > fin) {
            return;
        }
    }

    /*si el ciclo termino se revisa el ultimo a la derecha*/
    if (!nodo->getEsHoja()) {
        buscarRangoAux(nodo->getHijos().getValor(i), inicio, fin, resultados);
    }

}


/*----***---Fin de los Metodos de busqueda---***----*/


/*----*****--METODO DE ELIMINACION TOTAL--*****----*/

/*
*
*NOTA IMPORTANTE: Este metodo esta muy recortado ya que la eliminacion de los nodos se delego directamente al Nodo
*por lo tanto este ya se encarga de llevarse todo por delante
*
*/
void ArbolB::eliminar(const std::string& codigo) {

    if (this->raiz == nullptr) {
        throw DeleteException("El arbol esta vacio. [ARBOL B]");
    }

    /*Fase de buscar el producto completo para obtener su fecha para poder generar los rebalanceos */
    bool encontrado = false;
    Producto productoAEliminar = buscarPorCodigoExhaustivo(this->raiz, codigo, encontrado);

    if (!encontrado) {
        throw DeleteException("El producto con el codigo de barra {" + codigo + "} no existe. [ARBOL B]");
    }

    /*Se extrae la fecha del producto encontrado para poder generar el rebalanceo*/
    std::string fechaEncontrada = productoAEliminar.getFechaExpiracion();

    /* Se hace el llamado al metodo recursivo de eliminacion para evitar tocar la logica del parametro de orden*/
    this->eliminarAux(this->raiz, fechaEncontrada, codigo);

    /* Se evalua si la raiz se quedo vacia tras el rebalanceo para eliminar el nodo restante */
    if (this->raiz->getClaves().getLongitud() == 0) {

        NodoB* temporal = this->raiz;

        /*Caso en el que la raiz es hoja*/
        if (this->raiz->getEsHoja()) {
            this->raiz = nullptr;
        }
        else{

            /*Caso en el que el hijo sera la nueva raiz*/

            this->raiz = this->raiz->getHijos().getValor(0);

            /*Elimina a el hijo y lo remueve para que el destructor no lo encuentre*/
            temporal->getHijos().eliminar(0);
        }

        /*El destructor borra el nodo vacio*/
        delete temporal;
    }
}


/*Metodo auxiliar que permite buscar la clave del producto que se va a eliminar en base a su llave primaria de integridad*/
Producto ArbolB::buscarPorCodigoExhaustivo(NodoB* nodo, const std::string& codigo, bool& encontrado) {

    /*Retorna un producto vacio si no hay nada en el nodo*/

    if (nodo == nullptr) {
        return Producto();
    }

    int nClaves = nodo->getClaves().getLongitud();

    //Caso 1: e busca en las claves principales del arbol
    for (int i = 0; i < nClaves; i++) {
        if (nodo->getClaves().getValor(i).getCodigoBarra() == codigo) {
            encontrado = true;
            return nodo->getClaves().getValor(i);
        }
    }

    //Caso 2: Si el nodo no es hoja y no se encontro en las claves. Se empieza a buscar en los hijos
    if (!nodo->getEsHoja()) {
        for (int i = 0; i <= nClaves; i++) {
            Producto product = buscarPorCodigoExhaustivo(nodo->getHijos().getValor(i), codigo, encontrado);
            if (encontrado) {

                /*Si lo encontro en algun hijo,se retorna hacia arriba.*/
                return product;
            }
        }
    }

    /*Caso en el que no se encontro*/
    return Producto();
}


/*----*****--APARTADO DE LOS METODOS DE ELIMINACION--*****----*/

/*Metodo clave. ESTE PERMITE MANTENER EL BALANCE ES DE LOS MAS IMPORTANTES YA QUE MANEJA TODOS LOS CASOS*/
void ArbolB::eliminarDeNodoInterno(NodoB* nodo, int idx){

    Producto clave = nodo->getClaves().getValor(idx);
    NodoB* hijoIzq = nodo->getHijos().getValor(idx);
    NodoB* hijoDer = nodo->getHijos().getValor(idx + 1);

    /*Caso en el que el hijo izquierdo tiene lo suficiente para poder prestar*/
    if (hijoIzq->getClaves().getLongitud() >= t) {
        Producto predecesor = getPredecesor(nodo, idx);
        nodo->getClaves().setValor(idx, predecesor); // Reemplazamos
        eliminarAux(hijoIzq, predecesor.getFechaExpiracion(), predecesor.getCodigoBarra());
    }
    else if (hijoDer->getClaves().getLongitud() >= t) {

        /*Caso en el que el hijo derecho tiene lo necesario para poder prestar*/
        Producto sucesor = getSucesor(nodo, idx);
        nodo->getClaves().setValor(idx, sucesor); // Reemplazamos
        eliminarAux(hijoDer, sucesor.getFechaExpiracion(), sucesor.getCodigoBarra());
    }
    else {
        /*Caso en el que ambos se desbordaron (MOMENTO CRITICO) aca es donde se fusionan los arboles y se genera la accion en cadena*/
        fusionar(nodo, idx);
        eliminarAux(hijoIzq, clave.getFechaExpiracion(), clave.getCodigoBarra());
    }

}

// Encuentra la clave más a la derecha del subárbol izquierdo
Producto ArbolB::getPredecesor(NodoB* nodo, int idx) {
    NodoB* actual = nodo->getHijos().getValor(idx);
    while (!actual->getEsHoja()) {
        actual = actual->getHijos().getValor(actual->getHijos().getLongitud() - 1);
    }
    return actual->getClaves().getValor(actual->getClaves().getLongitud() - 1);
}

// Encuentra la clave más a la izquierda del subárbol derecho
Producto ArbolB::getSucesor(NodoB* nodo, int idx) {
    NodoB* actual = nodo->getHijos().getValor(idx + 1);
    while (!actual->getEsHoja()) {
        actual = actual->getHijos().getValor(0);
    }
    return actual->getClaves().getValor(0);
}


/*Metodo recursivo principal para poder ir recorriendo el arbol durante la eliminacion*/
void ArbolB::eliminarAux(NodoB* nodo, const std::string& fecha, const std::string& codigo){

    int idx = buscarClave(nodo, fecha, codigo);
    int nClaves = nodo->getClaves().getLongitud();

    /*Caso en el que la clave esta en el nodo a buscar*/

    if (idx < nClaves && nodo->getClaves().getValor(idx).getFechaExpiracion() == fecha && nodo->getClaves().getValor(idx).getCodigoBarra() == codigo) {

        /*Caso donde solo es una hoja (nivel bajo)*/
        if (nodo->getEsHoja()) {

            nodo->getClaves().eliminar(idx);
        } else {
            eliminarDeNodoInterno(nodo, idx);
        }

    }else{

        //La clave no esta en el arbol ultima instancia
        if (nodo->getEsHoja()) {
            throw DeleteException("El producto con el codigo de barra {"+codigo+"} no existe. [ARBOL B]");
        }

        bool esUltimoHijo = (idx == nClaves);
        NodoB* hijo = nodo->getHijos().getValor(idx);

        /*Caso en el que el hijo tiene el minimo de claves*/
        if (hijo->getClaves().getLongitud() < t) {
            llenar(nodo, idx);
        }

        /*Si al llenar se desborda se propaga un merge*/
        if (esUltimoHijo && idx > nodo->getClaves().getLongitud()) {
            eliminarAux(nodo->getHijos().getValor(idx - 1), fecha, codigo);
        } else {
            eliminarAux(nodo->getHijos().getValor(idx), fecha, codigo);
        }

    }
}

/*Metodo que encuentra el indice de la clave en el nodo evaluado*/
int ArbolB::buscarClave(NodoB* nodo, const std::string& fecha, const std::string& codigo){

    int indice = 0;
    int nClave = nodo->getClaves().getLongitud();

    /*Merge de la key y la fecha para poder agilizar la busqueda*/
    std::string actual = fecha + codigo;

    while (indice < nClave && (nodo->getClaves().getValor(indice).getFechaExpiracion() + nodo->getClaves().getValor(indice).getCodigoBarra()) < actual) {
        indice++;
    }
    return indice;
}

/*Metodo llamado cuando el hijo por el que se baja tiene t-1 claves y lo lleva a t*/
void ArbolB::llenar(NodoB* nodo, int indice){

    /*Caso en el que el hermano anterior tiene mas claves. Se presta*/
    if (indice != 0 && nodo->getHijos().getValor(indice - 1)->getClaves().getLongitud() >= t) {
        prestarDeAnterior(nodo, indice);
    }
    else if (indice != nodo->getClaves().getLongitud() && nodo->getHijos().getValor(indice + 1)->getClaves().getLongitud() >= t) {

        /*Si el hermano siguiente tiene mas de t-1 claves. Se presta*/
        prestarDeSiguiente(nodo, indice);
    }
    else {
        /*Caso en el que no se puede prestar. Se Suben los arboles para hacer merges*/
        if (indice != nodo->getClaves().getLongitud()) {
            fusionar(nodo, indice);
        } else {
            fusionar(nodo, indice - 1);
        }
    }
}

/*Metodo que permite prestar desde el anterior (Padre) al hijo CASO 1*/
void ArbolB::prestarDeAnterior(NodoB* nodo, int indice){

    NodoB* hijo = nodo->getHijos().getValor(indice);
    NodoB* hermano = nodo->getHijos().getValor(indice - 1);

    /*La clave del padre baja al hijo directamente*/
    hijo->getClaves().insertar(0, nodo->getClaves().getValor(indice - 1));

    if (!hijo->getEsHoja()) {
        hijo->getHijos().insertar(0, hermano->getHijos().getValor(hermano->getHijos().getLongitud() - 1));
        hermano->getHijos().eliminar(hermano->getHijos().getLongitud() - 1);
    }

    /*La ultima clave del hermano sube al padre*/
    nodo->getClaves().setValor(indice - 1, hermano->getClaves().getValor(hermano->getClaves().getLongitud() - 1));
    hermano->getClaves().eliminar(hermano->getClaves().getLongitud() - 1);

}

/*Metodo que permite prestar desde el siguiente al hermano de la par CASO 2*/
void ArbolB::prestarDeSiguiente(NodoB* nodo, int indice){

    NodoB* hijo = nodo->getHijos().getValor(indice);
    NodoB* hermano = nodo->getHijos().getValor(indice + 1);

    hijo->getClaves().insertar(hijo->getClaves().getLongitud(), nodo->getClaves().getValor(indice));

    if (!hijo->getEsHoja()) {
        hijo->getHijos().insertar(hijo->getHijos().getLongitud(), hermano->getHijos().getValor(0));
        hermano->getHijos().eliminar(0);
    }

    /*las claves se fusionan del lado derecho desde el hermano de la lista*/
    nodo->getClaves().setValor(indice, hermano->getClaves().getValor(0));
    hermano->getClaves().eliminar(0);

}

/*Metodo CASO 3. Donde se desbordan las listas y se tiene que subir y subir haciendo merges*/
void ArbolB::fusionar(NodoB* nodo, int indice){

    NodoB* hijo = nodo->getHijos().getValor(indice);
    NodoB* hermano = nodo->getHijos().getValor(indice + 1);


    /*Se baja la clave del padre al hijo*/
    hijo->getClaves().insertar(hijo->getClaves().getLongitud(), nodo->getClaves().getValor(indice));

    /*Pasa todas las claves del hermano al hijo*/
    for (int i = 0; i < hermano->getClaves().getLongitud(); ++i) {
        hijo->getClaves().insertar(hijo->getClaves().getLongitud(), hermano->getClaves().getValor(i));
    }

    /*Pasa los hijos del hermano en el caso de que no sea hoja*/
    if (!hijo->getEsHoja()) {
        for (int i = 0; i < hermano->getHijos().getLongitud(); ++i) {
            hijo->getHijos().insertar(hijo->getHijos().getLongitud(), hermano->getHijos().getValor(i));
        }
    }

    /*Eliminar el puntero al hermano del nodo padre*/
    nodo->getClaves().eliminar(indice);
    nodo->getHijos().eliminar(indice + 1);

    /*Se vacia la lista de los hijos para que este no los mate al momento de eliminarse y evitar desbordes de RAM*/
    while (!hermano->getHijos().esVacia()) {
        hermano->getHijos().removerFrente();
    }

    /*Se borra el nodo pero los demas ya estan en el padre*/
    delete hermano;

}

/*----*****--FIN DEL APARTADO DE LOS METODOS DE ELIMINACION--*****----*/

