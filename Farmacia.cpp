//
// Created by mario on 01/11/2025.
//


#include "Farmacia.h"
#include "MediExpress.h"

/**
 * @brief Constructor por defecto.
 */
Farmacia::Farmacia() :
        cif("-"),
        provincia("-"),
        localidad("-"),
        nombre("-"),
        direcion("-"),
        codPostal("-"),
        //dispense(),
        linkMedi(0){}


/**
 * @brief Constructor parametrizado.
 * @param cif CIF de la farmacia.
 * @param provincia Provincia.
 * @param localidad Localidad.
 * @param nombre Nombre comercial.
 * @param direcion Dirección.
 * @param codPostal Código Postal.
 * @param med Puntero al sistema MediExpress.
 */
Farmacia::Farmacia(const std::string &cif, const std::string &provincia, const std::string &localidad,
                   const std::string &nombre, const std::string &direcion,
                   const std::string &codPostal, MediExpress* med) :
        cif(cif),
        provincia(provincia),
        localidad(localidad),
        nombre(nombre),
        direcion(direcion),
        codPostal(codPostal),
        //dispense(),
        linkMedi(med){}

/**
 * @brief Constructor de copia.
 * @param orig Objeto Farmacia original.
 */
Farmacia::Farmacia(const Farmacia &orig):
        cif(orig.cif),
        provincia(orig.provincia),
        localidad(orig.localidad),
        nombre(orig.nombre),
        direcion(orig.direcion),
        codPostal(orig.codPostal),
        //dispense(orig.dispense),
        linkMedi(orig.linkMedi){}

/**
 * @brief Destructor virtual.
 */
Farmacia::~Farmacia() {

}

/**
 * @brief Obtiene el CIF.
 * @return CIF.
 */
const std::string &Farmacia::getCif() const {
    return cif;
}

/**
 * @brief Obtiene la Provincia.
 * @return provincia.
 */
const std::string &Farmacia::getProvincia() const {
    return provincia;
}

/**
 * @brief Obtiene la localidad.
 * @return Localidad.
 */
const std::string &Farmacia::getLocalidad() const {
    return localidad;
}

/**
 * @brief Obtiene el nombre.
 * @return Nombre.
 */
const std::string &Farmacia::getNombre() const {
    return nombre;
}

/**
 * @brief Obtiene la dirección.
 * @return Dirección.
 */
const std::string &Farmacia::getDirecion() const {
    return direcion;
}

/**
 * @brief Obtiene el Codigo postal.
 * @return codPostal.
 */
const std::string &Farmacia::getCodPostal() const {
    return codPostal;
}

/**
 * @brief Establece el CIF.
 * @param cif Nuevo CIF.
 */
void Farmacia::setCif(const std::string &cif) {
    Farmacia::cif = cif;
}

/**
 * @brief Establece la provincia.
 * @param provincia Nueva provincia.
 */
void Farmacia::setProvincia(const std::string &provincia) {
    Farmacia::provincia = provincia;
}

void Farmacia::setLocalidad(const std::string &localidad) {
    Farmacia::localidad = localidad;
}

/**
 * @brief Establece el nombre.
 * @param nombre Nuevo nombre.
 */
void Farmacia::setNombre(const std::string &nombre) {
    Farmacia::nombre = nombre;
}

/**
 * @brief Establece la dirección.
 * @param direcion Nueva dirección.
 */
void Farmacia::setDirecion(const std::string &direcion) {
    Farmacia::direcion = direcion;
}

/**
 * @brief Establece el código postal.
 * @param codPostal Nuevo código postal.
 */
void Farmacia::setCodPostal(const std::string &codPostal) {
    Farmacia::codPostal = codPostal;
}

/**
 * @brief Operador de igualdad (basado en CIF).
 * @param rhs Farmacia a comparar.
 * @return true si los CIF son iguales.
 */
bool Farmacia::operator==(const Farmacia &rhs) const {
    return this->cif == rhs.cif;
}

/**
 * @brief Operador menor que (basado en CIF).
 * @param rhs Farmacia a comparar.
 * @return true si el CIF de this es menor que el de rhs.
 */
bool Farmacia::operator<(const Farmacia &rhs) const {
    return this->cif < rhs.cif;
}

/**
 * @brief Operador mayor que (basado en CIF).
 * @param other Farmacia a comparar.
 * @return true si el CIF de this es mayor que el de other.
 */
bool Farmacia::operator>(const Farmacia &rhs) const {
    return this->cif > rhs.cif;
}

/**
 * @brief Realiza un pedido de un medicamento a MediExpress.
 * @param id_num ID numérico del medicamento a pedir.
 * @param n Cantidad a pedir
 */
void Farmacia::pedidoMedicam(int id_num, int n){
    if (linkMedi){
        linkMedi->suministrarFarmacia(this, id_num,n);
    }
}

/**
 * @brief Busca un medicamento en el stock local (dispense).
 * @param id_num ID numérico del medicamento.
 * @return Puntero al PaMedicamentos si se encuentra, 0 (nullptr) si no.
 */
int Farmacia::buscaMedicamID(int id_num) {
    Stock st;
    st.setIdPaMed(id_num);
    std::set<Stock>::iterator it=order.find(st);
    if(it!=order.end())
        return it->getNumStock();

    return 0;
}

void Farmacia::nuevoStock(PaMedicamentos *pa, int n) {
    if (pa == nullptr || n <= 0) return;

    Stock st_buscar;
    st_buscar.setIdPaMed(pa->getIdNum());

    auto it = order.find(st_buscar);

    if (it != order.end()) {
        // El elemento existe. Lo copiamos, actualizamos, borramos el viejo e insertamos el nuevo.
        Stock st_actualizado = *it; // Copiamos el stock
        st_actualizado.setNumStock(it->getNumStock() + n); // Actualizamos la cantidad

        order.erase(it); // Borramos el viejo
        order.insert(st_actualizado); // Insertamos el nuevo
    } else {
        // El elemento no existe, lo creamos nuevo
        st_buscar.setNumStock(n);
        order.insert(st_buscar);
    }
}


/**
 * @brief Compra (reduce) el stock de un medicamento.
 * @param id_num ID del medicamento.
 * @param n Cantidad que se desea comprar.
 * @param result (Parámetro de salida) No se utiliza en esta implementación.
 * @return Cantidad real comprada (0 si no se encuentra o no hay stock).
 */
int Farmacia::comprarMedicamento(int id_num, int n, PaMedicamentos* &result) {
    // Parámetro de salida 'result' no se usa según la cabecera
    result = nullptr;

    // 1. Crear un objeto 'Stock' temporal solo para la búsqueda
    Stock st_buscar;
    st_buscar.setIdPaMed(id_num);

    // 2. Buscar el Stock en el set 'order'
    auto it = order.find(st_buscar);

    // 3. Caso: El medicamento no está en el inventario
    if (it == order.end()) {
        return 0; // No se compró nada
    }

    // 4. Caso: El medicamento sí existe
    int stock_actual = it->getNumStock();
    int cantidad_comprada = 0;

    if (stock_actual > n) {
        // --- Hay stock de sobra ---
        cantidad_comprada = n; // Se vende la cantidad pedida

        // Para actualizar el set: copiar, modificar, borrar el viejo, insertar el nuevo
        Stock st_actualizado = *it;
        st_actualizado.setNumStock(stock_actual - n); // Reducir stock

        order.erase(it); // Borrar el viejo
        order.insert(st_actualizado); // Insertar el actualizado

    } else {
        // --- No hay stock de sobra (o es justo) ---
        cantidad_comprada = stock_actual; // Se vende todo lo que queda

        // Como el stock llega a 0 (o ya era 0), simplemente eliminamos la entrada
        order.erase(it);
    }

    return cantidad_comprada;
}


/**
 * @brief Elimina un medicamento del stock (lo borra del set).
 * @param id_num ID del medicamento a eliminar.
 * @return true si se encontró y eliminó, false si no se encontró.
 */
bool Farmacia::eliminarStock(int id_num) {
    // 1. Crear un objeto 'Stock' temporal solo para la búsqueda y borrado
    Stock st_buscar;
    st_buscar.setIdPaMed(id_num);

    // Este método busca el elemento y, si lo encuentra, lo borra.
    // Devuelve el número de elementos borrados (0 o 1 en un set).
    size_t elementos_borrados = order.erase(st_buscar);

    // 3. Devolver true si se borró 1 elemento, false si se borraron 0
    return (elementos_borrados > 0);
}

/**
 * @brief Busca medicamentos en el stock local por coincidencia de nombre.
 * @param nombre Nombre (o parte del nombre) a buscar.
 * @return Vector dinámico con punteros a los medicamentos encontrados.
 */
std::vector<PaMedicamentos*> Farmacia::buscaMedicamentoNombre(const std::string &nombre) {
    std::vector<PaMedicamentos*> v_final;

    if (linkMedi == nullptr) {
        return v_final;
    }

    // 1. Pedir a MediExpress TODOS los medicamentos que coincidan con el nombre
    std::vector<PaMedicamentos*> v_resultados_globales = buscaMedicamentoNombre(nombre);

    // 2. Filtrar esa lista: ¿cuáles de estos tengo YO (la farmacia) en stock?
    for (PaMedicamentos* pa_med : v_resultados_globales) {

        // Creamos un Stock temporal (solo con ID) para buscar en el set 'order'
        Stock st_buscar;
        st_buscar.setIdPaMed(pa_med->getIdNum());

        // 3. Comprobar si existe en el set 'order'
        if (order.find(st_buscar) != order.end()) {
            v_final.push_back(pa_med);
        }
    }

    return v_final;
}