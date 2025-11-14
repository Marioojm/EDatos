//
// Created by Alba on 10/10/2025.
//


#ifndef PRACTICA2_LISTASENLAZADAS_H
#define PRACTICA2_LISTASENLAZADAS_H

#include <iostream>
#include <stdexcept>

/**
 * @brief Estructura de un nodo para la lista simplemente enlazada.
 * @tparam T Tipo de Dato que almacena el nodo.
 */
template<class T>
class Nodo {

public:
    T dato;
    Nodo *sig;

    /**
     * @brief Constructor del nodo.
     * @param aDato El Dato a almacenar.
     * @param asig Puntero al siguiente nodo (por defecto, nullptr).
     */
    Nodo(const T &aDato, Nodo *asig = nullptr) : dato(aDato), sig(asig) {}

    /**
     * @brief Destructor del nodo.
     */
    ~Nodo() {}
};

/**
 * @brief Implementación de una lista simplemente enlazada.
 *
 * Utiliza nodos con puntero al siguiente y mantiene punteros a la cabecera y a la cola.
 * @tparam T Tipo de Dato que almacena la lista.
 */
template<class T>
class listasEnlazadas {

private:
    Nodo<T> *cabecera, *cola;
    unsigned tama;

public:
    /**
     * @brief Clase Iterador para recorrer la lista.
     * @tparam U Tipo del Dato, debe coincidir con T.
     */
    template<class U>
    class Iterador {
    private:
        Nodo<U> *nodo;

    public:
        friend class listasEnlazadas<U>;

        /**
         * @brief Constructor del iterador.
         * @param aNodo Puntero al nodo inicial (por defecto, nullptr).
         */
        Iterador(Nodo<U> *aNodo = nullptr) : nodo(aNodo) {}

        /**
         * @brief Comprueba si el iterador ha llegado al final de la lista.
         * @return \c true si el puntero es nulo (fin de la lista), \c false en caso contrario.
         */
        bool fin() const { return nodo == nullptr; }

        /**
         * @brief Avanza el iterador al siguiente nodo.
         */
        void siguiente() { nodo = nodo->sig; }

        /**
         * @brief Obtiene una referencia al Dato almacenado en el nodo actual.
         */
        T &dato() { return nodo->dato; }


        /**
         * @brief Destructor del iterador.
         */
        ~Iterador() {}
    };

    /**
     * @brief Constructor por defecto. Inicializa la lista vacía.
     */
    listasEnlazadas() : cabecera(nullptr), cola(nullptr), tama(0) {}

    /**
     * @brief Destructor de la lista enlazada. Libera todos los nodos.
     */
    ~listasEnlazadas();

    /**
     * @brief Constructor de copia profunda.
     * @param l Lista enlazada original para copiar.
     */
    listasEnlazadas(const listasEnlazadas<T> &l);

    /**
     * @brief Operador de asignación (copia profunda).
     * @param l Lista enlazada a asignar.
     * @return Referencia al objeto actual después de la asignación.
     */
    listasEnlazadas &operator=(const listasEnlazadas<T> &l);


    /**
     * @brief Obtiene un iterador que comienza en la cabecera.
     * @return Un objeto \c Iterador<T>.
     */
    Iterador<T> iterador() const;

    /**
     * @brief Inserta un Dato al principio de la lista.
     * @param dato El Dato constante a insertar.
     * @post El tamaño de la lista aumenta en uno. El nuevo nodo es la cabecera.
     */
    void insertarInicio(const T &dato);

    /**
     * @brief Inserta un Dato al final de la lista.
     * @param dato El Dato constante a insertar.
     * @post El tamaño de la lista aumenta en uno. El nuevo nodo es la cola.
     */
    void insertarFin(const T &dato);

    /**
     * @brief Inserta un Dato delante de la posición marcada por el iterador.
     * @param p Iterador que marca la posición **después** de la cual se buscará el nodo anterior.
     * @param dato El Dato constante a insertar.
     * @note Si el iterador \c p apunta a la cabecera, se llama a \c insertarInicio. Si es \c fin(), se llama a \c insertarFin.
     */
    void insertaDelante(Iterador<T> &p, const T &dato);

    /**
     * @brief Inserta un Dato detrás de la posición marcada por el iterador.
     * @param p Iterador que apunta al nodo **antes** del cual se insertará el nuevo nodo.
     * @param dato El Dato constante a insertar.
     */
    void insertaDetras( Iterador<T> &p, const T &dato);

    /**
     * @brief Elimina el nodo de la cabecera.
     * @post El tamaño de la lista se reduce en uno (si no estaba vacía).
     */
    void borrarInicio();

    /**
     * @brief Elimina el nodo de la cola.
     * @post El tamaño de la lista se reduce en uno (si no estaba vacía).
     */
    void borrarFinal();

    /**
     * @brief Elimina el nodo apuntado por el iterador.
     * @param i Iterador que apunta al nodo a borrar.
     * @post El nodo es eliminado y liberado. El iterador queda **invalidado** (apunta a \c nullptr).
     */
    void borra(Iterador<T> &i);

    /**
     * @brief Devuelve el tamaño lógico (número de elementos) de la lista.
     * @return El número de elementos.
     */
    int tam() const { return tama; }

    /**
     * @brief Libera toda la memoria de la lista.
     * @deprecated Se recomienda usar el destructor o una llamada explícita si se necesita limpiar la lista sin destruirla.
     */
    void destruyeLista();

    /**
     * @brief Concatena la lista actual con otra lista.
     * @param l La lista constante a concatenar al final.
     * @return Una nueva lista enlazada que es el resultado de la concatenación (copia profunda).
     */
    listasEnlazadas<T> concatena(const listasEnlazadas<T> &l) const;

    /**
     * @brief Sobrecarga del operador de suma para concatenar dos listas.
     * @param l La lista constante a concatenar.
     * @return Una nueva lista enlazada resultado de la concatenación.
     */
    listasEnlazadas<T> operator+(const listasEnlazadas<T> &l) const;

    /**
     * @brief Obtiene una referencia al Dato de la cabecera de la lista.
     * @return Referencia al Dato de la cabecera.
     * @throw std::invalid_argument Si la lista está vacía.
     */
    T &inicio(){
        if (cabecera)
            return cabecera->dato;
        throw std::invalid_argument("Error: La lista está vacía. No existe elemento inicial.");
    };

    /**
     * @brief Obtiene una referencia al Dato de la cola de la lista.
     * @return Referencia al Dato de la cola.
     * @throw std::invalid_argument Si la lista está vacía.
     */
    T &fin(){
        if (cola)
            return cola->dato;
        throw std::invalid_argument("Error: La lista está vacía. No existe elemento final.");
    };
};

// ==============================================================================
//                  IMPLEMENTACIÓN DE MÉTODOS
// ==============================================================================

template<class T>
typename listasEnlazadas<T>::template Iterador<T> listasEnlazadas<T>::iterador() const {
    return Iterador<T> (cabecera);
}

template<class T>
listasEnlazadas<T>::~listasEnlazadas() {
    destruyeLista();
}

template<class T>
listasEnlazadas<T> &listasEnlazadas<T>::operator=(const listasEnlazadas<T> &l) {
    if (this != &l){
        // 1. Limpieza del objeto actual
        destruyeLista(); // Usamos el método de limpieza

        // 2. Copia profunda del objeto 'l'
        for (Nodo<T> *i = l.cabecera; i != nullptr; i = i->sig)
        {
            Nodo<T> *nuevo = new Nodo<T> (i->dato, nullptr);
            if (cola != nullptr)
                cola->sig = nuevo;

            if(cabecera == nullptr )
                cabecera = nuevo;

            cola = nuevo;
            tama++;
        }
    }
    return *this;
}

template<class T>
listasEnlazadas<T>::listasEnlazadas(const listasEnlazadas<T> &l) : cabecera(nullptr), cola(nullptr), tama(0) {
    for (Nodo<T>* actual = l.cabecera; actual != nullptr; actual = actual->sig) {
        Nodo<T> *nuevo = new Nodo<T>(actual->dato);

        if (cabecera == nullptr) {
            cabecera = nuevo;
            cola = nuevo;
        } else {
            cola->sig = nuevo;
            cola = nuevo;
        }
        tama++;
    }
}


template<class T>
void listasEnlazadas<T>::insertarInicio(const T &dato) {
    Nodo<T> *nuevo = new Nodo<T>(dato, cabecera);

    if (cola == nullptr) // Si la lista estaba vacía
        cola = nuevo;

    cabecera = nuevo;
    ++tama;
}

template<class T>
void listasEnlazadas<T>::insertarFin(const T &dato) {
    Nodo<T> *nuevo = new Nodo<T>(dato, nullptr);

    if (cola != nullptr)
        cola->sig = nuevo;

    if (cabecera == nullptr) // Si la lista estaba vacía
        cabecera = nuevo;

    cola = nuevo;
    ++tama;
}

template<class T>
void listasEnlazadas<T>::insertaDelante(listasEnlazadas::Iterador<T> &p, const T &dato) {
    if (p.fin()) {
        insertarFin(dato); // La inserción se realiza al final.
        return;
    }

    if (p.nodo == cabecera) {
        insertarInicio(dato);
        return;
    }

    ++tama;

    // Buscar el nodo anterior
    Nodo<T> *anterior = cabecera;
    for (; anterior->sig != p.nodo; anterior = anterior->sig) {
        // La condición de parada asegura que anterior->sig es p.nodo
    }

    Nodo<T> *nuevo = new Nodo<T>(dato, p.nodo);
    anterior->sig = nuevo;
}

template<class T>
void listasEnlazadas<T>::insertaDetras(listasEnlazadas::Iterador<T> &p, const T &dato) {
    if(!p.fin()){
        ++tama;
        Nodo<T> *nuevo = new Nodo<T>(dato, p.nodo->sig);
        p.nodo->sig = nuevo;

        if(p.nodo == cola)
            cola = nuevo;
    }
}

template<class T>
void listasEnlazadas<T>::borrarInicio() {
    if(cabecera != nullptr){
        --tama;
        Nodo<T> *borrado = cabecera;
        cabecera = cabecera->sig;
        delete borrado;

        if(cabecera == nullptr) // Si la lista queda vacía
            cola = nullptr;
    }
}

template<class T>
void listasEnlazadas<T>::borrarFinal() {
    if (cabecera == nullptr) {
        return;
    }

    if (cabecera == cola) {
        delete cabecera;
        cabecera = cola = nullptr;
        tama = 0;
        return;
    }

    // Caso lista con 2 o más elementos
    --tama;
    Nodo<T> *anterior = cabecera;

    // Búsqueda del nodo anterior a la cola
    for (; anterior->sig != cola; anterior = anterior->sig) {
        // La condición de parada asegura que anterior->sig es cola
    }

    delete cola;

    cola = anterior;
    cola->sig = nullptr;
}

template<class T>
void listasEnlazadas<T>::borra(Iterador<T> &p) {
    if (p.fin()) {
        return; // No se puede borrar si el iterador está al final
    }

    if (p.nodo == cabecera) {
        borrarInicio();
        p.nodo = nullptr;
        return;
    }
    if (p.nodo == cola) {
        borrarFinal();
        p.nodo = nullptr;
        return;
    }

    // Caso Elemento Intermedio
    --tama;

    // Búsqueda del nodo anterior
    Nodo<T> *anterior = cabecera;
    for (; anterior->sig != p.nodo; anterior = anterior->sig) {
        // La condición de parada asegura que anterior->sig es p.nodo
    }

    Nodo<T> *nodo_a_borrar = p.nodo;

    // Desvinculación y re-enlazamiento
    anterior->sig = nodo_a_borrar->sig;

    delete nodo_a_borrar; // Liberación de la memoria
    p.nodo = nullptr; // Invalida el iterador
}

template<class T>
listasEnlazadas<T> listasEnlazadas<T>::concatena(const listasEnlazadas<T> &l) const {

    listasEnlazadas<T> ret(*this); // Utiliza el constructor de copia para clonar *this

    // Recorrido de la lista 'l' e inserción en 'ret'
    for (Nodo<T>* p = l.cabecera; p != nullptr; p = p->sig) {
        Nodo<T> *nuevo = new Nodo<T>(p->dato, nullptr);
        ret.tama++;

        if (ret.cola != nullptr) {
            ret.cola->sig = nuevo;
        }

        if (ret.cabecera == nullptr) { // Solo ocurre si *this estaba vacía
            ret.cabecera = nuevo;
        }

        ret.cola = nuevo;
    }

    return ret;
}

template<class T>
listasEnlazadas<T> listasEnlazadas<T>::operator+(const listasEnlazadas<T> &l) const {
    return this->concatena(l);
}

template<class T>
void listasEnlazadas<T>::destruyeLista(){
    Nodo<T> *actual = cabecera;
    // La forma de iterar se reestructura en un 'for' con inicialización nula y condición simple.
    for ( ; actual != nullptr; actual = cabecera ) {
        cabecera = cabecera->sig;
        delete actual;
    }
    cola = nullptr;
    tama = 0;
}

#endif //PRACTICA2_LISTASENLAZADAS_H