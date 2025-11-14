#include "PaMedicamentos.h"
#include "Laboratorios.h"

/**
 * @brief Constructor por defecto
 */
PaMedicamentos::PaMedicamentos() {

}

/**
 * @brief Constructor parametrizado.
 * @param id_num ID numérico del principio activo.
 * @param id_alpha ID alfanumérico del principio activo.
 * @param nombre Nombre del principio activo.
 */
PaMedicamentos::PaMedicamentos(int id_num, std::string id_alpha, std::string nombre) {
_id_num=id_num;
_id_alpha=id_alpha;
_nombre=nombre;
_laboratorio=nullptr;
}

/**
 * @brief Constructor de copia.
 * @param orig Objeto PaMedicamentos original para copiar.
 */
PaMedicamentos::PaMedicamentos(const PaMedicamentos &orig) {
    _id_num = orig._id_num;
    _id_alpha = orig._id_alpha;
    _nombre = orig._nombre;
    _laboratorio = orig._laboratorio;
}

/**
 * @brief Destructor de la clase PaMedicamentos.
 */
PaMedicamentos::~PaMedicamentos() {
}

/**
 * @brief Obtiene el ID numérico.
 * @return El ID numérico.
 */
int PaMedicamentos::getIdNum() {
    return _id_num;
}

/**
 * @brief Obtiene el ID alfanumérico.
 * @return El ID alfanumérico.
 */
const std::string &PaMedicamentos::getIdAlpha() const {
    return _id_alpha;
}

/**
 * @brief Obtiene el nombre del principio activo.
 * @return El nombre.
 */
const std::string &PaMedicamentos::getNombre() const {
    return _nombre;
}

/**
 * @brief Establece el ID numérico.
 * @param id_num Nuevo ID numérico.
 */
 void PaMedicamentos::setIdNum(int id_num) {
    _id_num=id_num;
}

/**
 * @brief Establece el ID alfanumérico.
 * @param id_alpha Nuevo ID alfanumérico.
 */
 void PaMedicamentos::setIdAlpha(std::string id_alpha) {
    _id_alpha=id_alpha;
}

/**
 * @brief Establece el nombre del principio activo.
 * @param nombre Nuevo nombre.
 */
void PaMedicamentos::setNombre(std::string nombre) {
    _nombre=nombre;
}

/**
 * @brief Operador de igualdad.
 * @param otro El otro objeto PaMedicamentos a comparar.
 * @return true si los ID numéricos son iguales, false en caso contrario.
 */
bool PaMedicamentos::operator==(const PaMedicamentos &otro) {
    return _id_num == otro._id_num;
}

/**
 * @brief Operador "menor que".
 * @param otro El otro objeto PaMedicamentos a comparar.
 * @return true si este objeto es menor que 'otro', false en caso contrario.
 */
bool PaMedicamentos::operator<(const PaMedicamentos &otro) {
    if (_id_num != otro._id_num)
        return _id_num < otro._id_num;
    if (_id_alpha != otro._id_alpha)
        return _id_alpha < otro._id_alpha;
    return _nombre < otro._nombre;
}

/**
 * @brief Asigna el laboratorio que sirve este principio activo.
 * @param lab Puntero al objeto Laboratorios.
 */
void PaMedicamentos::servidoPor(Laboratorios *lab) {
    _laboratorio = lab; 
}

/**
 * @brief Obtiene el puntero al laboratorio que sirve este principio activo.
 * @return Puntero al objeto Laboratorios.
 */
Laboratorios* PaMedicamentos::servidoPor() {
    return _laboratorio;
}


