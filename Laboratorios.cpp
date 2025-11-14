#include "Laboratorios.h"


/**
 * @brief Constructor por defecto
 */
Laboratorios::Laboratorios() {

}

/**
 * @brief Constructor parametrizado
 * @param id Identificador unico del laboratorio
 * @param nombreLab Nombre del laboratorio
 * @param direccion Direccion del laboratorio
 * @param codPostal Codigo postal del laboratorio
 * @param localidad Localidad del laboratorio
 */
Laboratorios::Laboratorios(int id, const std::string &nombreLab, const std::string &direccion,
                           const std::string &codPostal, const std::string &localidad) : _id(id), _nombreLab(nombreLab),
                                                                                         _direccion(direccion),
                                                                                         _codPostal(codPostal),
                                                                                         _localidad(localidad) {}
/**
 * @brief Constructor de copia
 * @param orig Objeto Laboratios original para copia
 */
Laboratorios::Laboratorios(const Laboratorios &orig) : _id(orig._id), _nombreLab(orig._nombreLab), _direccion(orig._direccion), _codPostal(orig._codPostal), _localidad(orig._localidad){

}

/**
 * @brief Destructor de la clase Laboratorios
 */
Laboratorios::~Laboratorios() {

}

/**
 * @brief Obtiene el identificador del laboratorio.
 * @return El ID del laboratorio.
 */
int Laboratorios::getId() const  {
    return _id;
}

/**
 * @brief Establece el identificador del laboratorio.
 * @param id Nuevo ID del laboratorio.
 */
void Laboratorios::setId(int id) {
    _id = id;
}

/**
 * @brief Obtiene el nombre del laboratorio.
 * @return Referencia al nombre del laboratorio.
 */
std::string &Laboratorios::getNombreLab()  {
    return _nombreLab;
}

/**
 * @brief Establece el nombre del laboratorio.
 * @param nombreLab Nuevo nombre del laboratorio.
 */
void Laboratorios::setNombreLab( std::string &nombreLab) {
    _nombreLab = nombreLab;
}

/**
 * @brief Obtiene la dirección del laboratorio.
 * @return Referencia a la dirección del laboratorio.
 */
std::string &Laboratorios::getDireccion() {
    return _direccion;
}

/**
 * @brief Establece la dirección del laboratorio.
 * @param direccion Nueva dirección del laboratorio.
 */
void Laboratorios::setDireccion(std::string &direccion) {
    _direccion = direccion;
}

/**
 * @brief Obtiene el código postal del laboratorio.
 * @return Referencia al código postal.
 */
std::string &Laboratorios::getCodPostal() {
    return _codPostal;
}

/**
 * @brief Establece el código postal del laboratorio.
 * @param codPostal Nuevo código postal.
 */
void Laboratorios::setCodPostal(std::string &codPostal) {
    _codPostal = codPostal;
}

/**
 * @brief Establece el código postal del laboratorio.
 * @param codPostal Nuevo código postal.
 */
std::string &Laboratorios::getLocalidad() {
    return _localidad;
}


/**
 * @brief Establece la localidad del laboratorio.
 * @param localidad Nueva localidad.
 */
 void Laboratorios::setLocalidad(std::string &localidad) {
    _localidad = localidad;
}



