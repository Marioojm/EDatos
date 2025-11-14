#ifndef P1_VECDIN_H
#define P1_VECDIN_H

#include <climits>
#include <algorithm>
#include <cmath>
#include <stdexcept>

/**
 *
 * @brief Clase Plantilla que implementa un vector dinámico.
 *
 * Esta clase proporciona un contenedor dinámico que ajusta
 * automáticamente su tamaño físico al insertar o eliminar elementos.
 * Incluye metodos de ordenación, búsqueda binaria y copia segura.
 *
 * @tparam T Tipo de Dato almacenado en el vector.
 */

template<class T>
class VecDin {
private:

    /**
     * @brief Duplica la memoria reservada para el vector.
     *
     * @post Crea un nuevo array con el doble de la capacidad, copia los elementos
     * existentes y libera la memoria del anterior.
     */
    void duplicaMem();

    /**
     * @brief Reduce la memoria reservada a la mitad.
     *
     * @post Si el tamanio lógico es un tercio menor al físico, reduce la capacidad.
     * No elimina datos validos.
     */
    void divideMem();

    /**
     * @brief Ajusta un valor al siguiente número que sea potencia de dos.
     *
     * @param t Referencia al valor a ajustar.
     */
    void tamabase2(unsigned &t);

    unsigned int tamL;     ///< Tamanio lógico (cantidad de elementos validos)
    unsigned int tamF;     ///< Tamanio físico (capacidad actual reservada)

    T *v;                  ///< Puntero al array dinámico.

public:

    /**
     * @brief Constructor por defecto
     *
     * Inicializa el vector con capacidad 1 y tamanio lógico 0.
     */
    VecDin();

    /**
     * @brief Constructor con tamanio inicial.
     *
     * @param tamLogico Tamanio inicial solicitado. Se ajusta al siguiente
     * número potencia de 2 si es necesario.
     */
    VecDin(unsigned tamLogico);

    /**
     * @brief Constructor de copia.
     *
     * Crea una copia completa del vector pasado como argumento.
     *
     * @param orig Vector a copiar.
     */
    VecDin(const VecDin<T> &orig);

    /**
     * @brief Constructor parcial.
     *
     * Copia una parte del vector original desde una posicion dada.
     *
     * @param orig Vector original.
     * @param posInicial Posicion inicial de la copia.
     * @param numElem Número de elementos a copiar.
     * @throw std::out_of_range Si posInicial es mayor o igual al tamanio lógico.
     */
    VecDin(const VecDin<T>& orig, unsigned posInicial, unsigned numElem);

    /**
     * @brief Destructor.
     *
     * Libera la memoria reservada por el vector.
     */
    ~VecDin();

    /**
     * @brief Operador de asignación.
     *
     * Realiza una copia profunda del vector dado.
     *
     * @param otro Vector dado.
     * @return Referencia al objeto actual.
     */
    VecDin<T>& operator=(const VecDin<T> &otro);

    /**
     * @brief Acceso por índice.
     *
     * Devuelve una referencia al elemento en la posición indicada.
     *
     * @param pos Posición a acceder.
     * @return Referencia al elemento.
     * @throw std::out_of_range Si el índice es inválido.
     */
    T& operator[](unsigned int pos);

    /**
     * @brief Inserta un nuevo elemento en el vector.
     *
     * Si no se indica la posición, inserta al final. Si se indica, desplaza los
     * elementos a la derecha para abrir espacio.
     *
     * @param dato Elemento a insertar.
     * @param pos Posición opcional (por defecto al final).
     * @throw std::out_of_range Si la posición es mayor al tamanio lógico.
     */
    void insertar(const T& dato, unsigned pos=UINT_MAX);

    /**
     * @brief Elimina un elemento del vector.
     *
     * Si no se indica la posición, elimina el último elemento. Ajusta la memoria
     * si queda mucho espacio libre.
     *
     * @param pos Posición opcional (por defecto al final).
     * @return El elemento eliminado.
     * @throw std::out_of_range Si el vector está vacío o la posición es inválida.
     */
    T borrar(unsigned int pos=UINT_MAX);

    /**
     * @brief Devuelve el tamanio lógico (número de elementos válidos).
     *
     * @return Cantidad de elementos almacenados.
     */
    unsigned int TamLogico(); //Para obtener el tamaño logico del vector.

    /**
     * @brief Ordena los elementos del vector de menor a mayor.
     *
     */
    void ordenar();

    /**
     * @brief Realiza una búsqueda binaria de un elemento.
     *
     * El vector debe estar ordenado.
     *
     * @param dato Elemento a buscar.
     * @return Índice del elemento si se encuentra, -1 si no existe.
     */
    unsigned int busquedaDic(const T &dato);
};

/**
 * @brief titulo
 * @param por cada parametro descripcion
 * @post descripcion del efecto que tiene
 * @return si tiene return
 * @throw si tiene alguna excepcion
 */
template<class T>
VecDin<T>::VecDin() {
    tamL=0;
    tamF=1;
    v=new T[tamF];
}

template<class T>
VecDin<T>::VecDin(unsigned tamLogico) {
    tamL = 0;
    tamabase2(tamLogico);
    tamF=tamLogico;
    v=new T[tamF];
}

template<class T>
VecDin<T>::VecDin(const VecDin<T> &orig) {
    tamL = orig.tamL;
    tamF= orig.tamF;
    v = new T[tamF];
    unsigned int i=0;
    while (i < tamL) {
        v[i] = orig.v[i];
        i++;
    }
}

template<class T>
VecDin<T>::VecDin(const VecDin<T>& orig, unsigned posInicial, unsigned numElem) {
    if(posInicial>=orig.tamL)
        throw std::out_of_range("Posicion erronea");

    unsigned int nuevoTam=numElem;
    tamabase2(nuevoTam);
    tamF=nuevoTam;
    tamL=numElem;
    v = new T[tamF];
    for(unsigned int i=0;i<numElem;i++)
        v[i]=orig.v[posInicial+i];
}

template<class T>
VecDin<T>::~VecDin(){
        if (v != nullptr){
            delete[] v;
            v= nullptr;
        }
}

template<class T>
VecDin<T> &VecDin<T>::operator=(const VecDin<T> &otro){
    if (this == &otro)
        return *this;

    delete[] v;
    tamL = otro.tamL;
    tamF = otro.tamF;
    v= new T[tamF];

    unsigned int i=0;
    while (i<tamL) {
        v[i]=otro.v[i];
        i++;
    }
    return *this;
}

template<class T>
T &VecDin<T>::operator[](unsigned pos){
    if (pos>=tamL)
        throw std::out_of_range("Posicion erronea");
    return v[pos];
}

template<class T>
void VecDin<T>::insertar(const T &dato, unsigned pos) {
  if(tamL == tamF)
      duplicaMem();

  if(pos != UINT_MAX && pos > tamL)
      throw std::out_of_range("Posicion fuera de rango");

  if(pos == UINT_MAX){
      v[tamL++] = dato;
      return;
  }

  unsigned int i = tamL;
  while (i > pos) {
      v[i] = v[i-1];
      --i;
  }

  v[pos] = dato;
  ++tamL;
}

template<class T>
T VecDin<T>::borrar(unsigned pos){
    if(tamL == 0)
        throw std::out_of_range("Vector vacio");

    if (pos == UINT_MAX)
        pos = tamL - 1;

    if (pos >= tamL)
        throw std::out_of_range("Posicion fuera de rango");

    T eliminado = v[pos];

    unsigned int i = pos;
    while (i + 1 < tamL){
        v[i] = v[i + 1];
        ++i;
    }
    --tamL;

    if (tamL * 3 < tamF && tamF > 1)
        divideMem();

    return eliminado;
}

template<class T>
unsigned int VecDin<T>::TamLogico() {
    return tamL;
}

template<class T>
void VecDin<T>::ordenar(){
    std::sort(v,v+tamL);
}

template<class T>
unsigned int VecDin<T>::busquedaDic(const T &dato) {
    int inf=0;
    int sup=tamL-1;
    int curIn;

    while (inf <=sup) {
        curIn = (inf+sup)/2;
        if (v[curIn]== dato) {
            return curIn;
        } else if (v[curIn] < dato){
            inf =curIn +1;
        }else sup=curIn - 1;
    }
return -1;
}


template<class T>
void VecDin<T>::duplicaMem() {

  unsigned int nuevoTam= tamF*2;
  T* copia = new T[nuevoTam];

  for (unsigned int i = 0; i < tamL; ++i)
      copia[i] = v[i];

  delete[] v;
  v=copia;
  tamF=nuevoTam;
}

template<class T>
void VecDin<T>::divideMem() {
   unsigned int nuevoTam = tamF/2;
   if (nuevoTam<1)
       nuevoTam =1;

   T* copia = new T[nuevoTam];

   unsigned int i = 0;
   while (i<tamL && i < nuevoTam) {
       copia[i] = v[i];
       i++;
   }

   delete[] v;
   v = copia;
   tamF = nuevoTam;
}

template<class T>
void VecDin<T>::tamabase2(unsigned int &t) {
    if (log2(t) == round(log2(t)))
        t++;
    while(log2(t)!= round(log2(t))) {
        t++;
    }
}


#endif //P1_VECDIN_H