
#ifndef PRACTICA3_AVL_H
#define PRACTICA3_AVL_H

#include <VecDin.h>

template <class T>
class NodoArb
{
public:
    NodoArb<T> *izq;
    NodoArb<T> *der;
    char bal; // -1, 0 , 1 para un árbol avl
    T Dato;

    /**
     * @brief Constructor parametrizado de NodoArb.
     * @param ele Dato a almacenar.
     */
    NodoArb(const T &ele): izq(0), der(0), bal(0), Dato(ele){}

    /**
     * @brief Constructor de copia de NodoArb.
     * @param orig Nodo original a copiar.
     */
    NodoArb(const NodoArb<T> &orig): izq(orig.izq), der(orig.der), bal(orig.bal), Dato(orig.Dato){}
};

template <class T>
class Avl {

    NodoArb<T> *raiz;
    unsigned int tam;

    /**
     * @brief Recorrido inorden recursivo.
     * @param p Nodo actual.
     * @param nivel Nivel actual (no usado en esta implementación).
     * @param v Vector para almacenar punteros a los datos.
     */
    void inorden(NodoArb<T>* p, int nivel, VecDin<T*> &v);

    /**
     * @brief Recorrido preorden recursivo.
     * @param p Nodo actual.
     * @param nivel Nivel actual (no usado).
     * @param v Vector para almacenar los datos.
     */
    void preorden(NodoArb<T> p, int nivel, VecDin<T> &v);

    /**
     * @brief Búsqueda recursiva de una clave.
     * @param dato Dato a buscar.
     * @param p Nodo actual.
     * @return Puntero al nodo si se encuentra, 0 (nullptr) en caso contrario.
     */
    NodoArb<T> *buscaClave (const T &dato, NodoArb<T> *p);

    /**
     * @brief Inserción recursiva de un dato (helper).
     * @param c Referencia al puntero del nodo actual.
     * @param dato Dato a insertar.
     * @return Cambio en la altura (0 si no cambia, 1 si aumenta).
     */
    int insertarDato(NodoArb<T>* &c, const T &dato);

    /**
     * @brief Destructor recursivo del árbol (helper).
     * @param p Nodo actual.
     */
    void destruyeArbol(NodoArb<T>* &p);

    /**
     * @brief Rotación simple a la derecha.
     * @param p Nodo (raíz de subárbol) a rotar.
     */
    void rotDer(NodoArb<T>* &p);

    /**
     * @brief Rotación simple a la izquierda.
     * @param p Nodo (raíz de subárbol) a rotar.
     */
    void rotIzq(NodoArb<T>* &p);

    /**
     * @brief Copia recursiva de un árbol (privado, helper).
     * @param q Referencia al puntero del nuevo nodo (destino).
     * @param p Puntero al nodo original (fuente).
     */
    void copiaAvl(NodoArb<T>* &q, NodoArb<T> *p);

    /**
     * @brief Conteo recursivo de elementos (privado).
     * @param p Nodo actual.
     * @return Número de elementos en el subárbol.
     */
    unsigned int numElementosPr(NodoArb<T>* p);

    /**
     * @brief Cálculo recursivo de la altura (privado).
     * @param p Nodo actual.
     * @param nivel Nivel actual.
     * @param result Referencia a la altura máxima encontrada.
     */
    void alturaPr(NodoArb<T>* p, int nivel, int &result);

public:

    /**
     * @brief Constructor por defecto.
     */
    Avl() : raiz(0), tam(0) {}

    /**
     * @brief Constructor de copia.
     * @param orig Árbol original a copiar.
     */
    Avl(const Avl<T>& orig);

    /**
     * @brief Operador de asignación.
     * @param orig Árbol original a asignar.
     * @return Referencia a this.
     */
    Avl<T>& operator=(const Avl<T>& orig);

    /**
     * @brief Búsqueda recursiva de un dato.
     * @param dato Dato a buscar.
     * @return Puntero al dato si se encuentra, 0 (nullptr) si no.
     */
    T* buscaRec (const T &dato);

    /**
     * @brief Búsqueda iterativa de un dato.
     * @param dato Dato a buscar.
     * @return Puntero al dato si se encuentra, 0 (nullptr) si no.
     */
    T* buscaIt(const T &dato);

    /**
     * @brief Inserta un dato en el árbol.
     * @param dato Dato a insertar.
     * @return true si la inserción tuvo éxito (no duplicado), false si ya existía.
     */
    bool inserta(const T &dato);

    /**
     * @brief Obtiene el número de elementos.
     * @return Número de elementos.
     */
    unsigned int numElementos();

    /**
     * @brief Calcula la altura del árbol.
     * @return Altura (0 si está vacío).
     */
    unsigned int altura();

    /**
     * @brief Obtiene el tamaño (variable tam).
     * @return Valor de tam.
     */
    unsigned int getTam(){ return tam;};

    /**
     * @brief Destructor.
     */
    ~Avl(){
        destruyeArbol(raiz);
    };

    /**
     * @brief Obtiene un vector con los punteros a los datos en recorrido inorden.
     * @return Vector dinámico de punteros a T.
     */
    VecDin<T*> recorreInorden() {
        VecDin<T*> v;
        inorden(raiz,0,v);
        return v;
    };

    /**
     * @brief Obtiene un vector con los datos en recorrido preorden.
     * @return Vector dinámico de T.
     */
    VecDin<T*> recorrePreorden() {
        VecDin<T*> v;
        preorden(raiz,0,v);
        return v;
    };

};

template<class T>
void Avl<T>::copiaAvl(NodoArb<T>* &q, NodoArb<T> *p){
    if (p){
        q= new NodoArb<T> (p->Dato);
        q->bal=p->bal;
        copiaAvl(q->izq,p->izq);
        copiaAvl(q->der,p->der);
    }else
        q=0;
}


template<class T>
Avl<T>::Avl(const Avl<T>& orig){
    copiaAvl(raiz,orig.raiz);
    tam=orig.tam;
    //raiz=copiaAvl2(orig.raiz);  //segunda forma del constructor de copia
}

template<class T>
Avl<T>& Avl<T>::operator=(const Avl<T>& orig){
    if (this!=&orig){
        destruyeArbol(raiz);
        copiaAvl(raiz,orig.raiz);
        tam=orig.tam;
    }
    return *this;
}
template <class T>
void Avl<T>::inorden (NodoArb<T>* p, int nivel, VecDin<T*> &v){
    if (p){
        inorden (p->izq, nivel+1, v);
        v.insertar(&(p->Dato));
        inorden (p->der, nivel+1, v);
    }
}

template <class T>
void Avl<T>::preorden(NodoArb<T> p, int nivel, VecDin<T> &v) {
    if(p) {
        v.insertarVec(&(p->Dato));

        preorden (p -> izq, nivel + 1, v);
        preorden(p->der, nivel + 1, v);
    }
}

template <class T>
NodoArb<T> *Avl<T>::buscaClave (const T &dato, NodoArb<T> *p){
    if (!p)
        return 0;
    else{
        if (dato < p->Dato)
            return buscaClave (dato, p->izq);
        else if (p-> Dato < dato)  //ojo esta cambiado
            return buscaClave (dato, p->der);
        else
            return p;
    }
}

template<class T>
int Avl<T>::insertarDato(NodoArb<T> *&c, const T &dato) {
    NodoArb<T> *p = c;
    int deltaH = 0;
    if (!p) {
        p = new NodoArb<T>(dato);
        c = p;
        deltaH = 1;
    }
    else if (dato > p->Dato) {
        if (insertarDato(p->der, dato)) {
            p->bal--;
            if (p->bal == 0) deltaH = 0;
            else if (p->bal == -1) deltaH = 1;
            else if (p->bal == -2) {
                if ( p->der->bal == 1)
                    rotDer(p->der);
                rotIzq(c);
                deltaH = 0;
            }
        }
    }
    else if (dato < p->Dato) {
        if (insertarDato(p->izq, dato)) {
            p->bal++;
            if (p->bal == 0) deltaH = 0;
            else if (p->bal==1)
                deltaH =1;
            else if (p->bal==2) {
                if (p->izq->bal == -1)
                    rotIzq(p->izq);
                rotDer(c);
                deltaH = 0;
            }
        }
    }
    return deltaH;
}

template <class T>
T* Avl<T>::buscaRec (const T &dato){
    NodoArb<T> *p = buscaClave (dato, raiz);
    T* result;
    if (p){
        result = &(p->Dato);
        return result;
    }
    return 0;
}

template <class T>
T* Avl<T>::buscaIt (const T &dato){
    NodoArb<T> *p = raiz;
    T* result;
    while (p){
        // T d=Dato;
        if (dato < p->Dato)
            p=p->izq;
        else
        if (p-> Dato < dato)
            p=p->der;
        else{
            result = &(p->Dato);
            return result;
        }
    }
    return 0;
}
template <class T>
bool Avl<T>::inserta(const T &dato){
    if (buscaRec(dato))
        return false;
    insertarDato(raiz, dato);
    tam++;
    return true;

}

template <class T>
void Avl<T>::destruyeArbol(NodoArb<T>* &p){
    if (p){
        destruyeArbol(p->izq);
        destruyeArbol(p->der);
        delete p;
        p=0;
    }
}

template<class T>
void Avl<T>::rotDer(NodoArb<T>* &nodo) {
    NodoArb<T> *q= nodo, *l;
    nodo = l = q->izq;
    q->izq = l->der;
    l->der = q;
    q->bal--;
    if(l->bal > 0) q->bal -= l->bal;
    l->bal--;
    if(q->bal < 0) l->bal -= -q->bal;
}

template<class T>
void Avl<T>::rotIzq(NodoArb<T>* &nodo) {
    NodoArb<T> *q= nodo, *r;
    nodo = r = q->der;
    q->der = r->izq;
    r->izq = q;
    q->bal++;
    if(r->bal < 0) q->bal += -r->bal;
    r->bal++;
    if(q->bal > 0) r->bal += q->bal;
}

template<class T>
unsigned int Avl<T>::numElementosPr(NodoArb<T> *p) {
    if (!p) {
        return 0;
    } else {
        return 1 + numElementosPriv(p->izq) + numElementosPriv(p->der);
    }
}

template <class T>
void Avl<T>::alturaPr(NodoArb<T>* p, int nivel, int &result){
    if (p){
        alturaPr(p->izq,nivel+1,result);
        if (nivel>result)
            result=nivel;
        alturaPr(p->der,nivel+1,result);
    }
}

template<class T>
unsigned int Avl<T>::numElementos() {
    return tam; // O getTam(), ya que hacen lo mismo.
}

template <class T>
unsigned int Avl<T>::altura(){
    int result=0;
    alturaPr(raiz,0,result);
    return result;
}


#endif //PRACTICA3_AVL_H
