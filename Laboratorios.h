#ifndef PRACTICA2_LABORATORIOS_H
#define PRACTICA2_LABORATORIOS_H

#include "string"


class Laboratorios {
private:
    int _id=0;
    std::string _nombreLab;
    std::string _direccion;
    std::string _codPostal;
    std::string _localidad;

public:

    /**
     * @brief Constructor por defecto.
     */
    Laboratorios();

    /**
     * @brief Constructor parametrizado.
     * @param id ID único.
     * @param nombreLab Nombre del laboratorio.
     * @param direccion Dirección.
     * @param codPostal Código Postal.
     * @param localidad Localidad.
     */
    Laboratorios(int id, const std::string &nombreLab, const std::string &direccion, const std::string &codPostal,
                 const std::string &localidad);

    /**
     * @brief Constructor de copia.
     * @param orig Objeto Laboratorios original.
     */
    Laboratorios(const Laboratorios& orig);

    /**
     * @brief Destructor.
     */
    ~Laboratorios();

    /**
     * @brief Obtiene el ID.
     * @return ID.
     */
    int getId();

    /**
     * @brief Establece el ID.
     * @param id Nuevo ID.
     */
    void setId(int id);

    /**
     * @brief Obtiene el nombre del laboratorio.
     * @return Referencia al nombre.
     */
    std::string &getNombreLab();

    /**
     * @brief Establece el nombre del laboratorio.
     * @param nombreLab Nuevo nombre.
     */
    void setNombreLab(std::string &nombreLab);

    /**
     * @brief Obtiene la dirección.
     * @return Referencia a la dirección.
     */
    std::string &getDireccion();

    /**
     * @brief Establece la dirección.
     * @param direccion Nueva dirección.
     */
    void setDireccion(std::string &direccion);

    /**
     * @brief Obtiene el código postal.
     * @return Referencia al código postal.
     */
    std::string &getCodPostal() ;

    /**
     * @brief Establece el código postal.
     * @param codPostal Nuevo código postal.
     */
    void setCodPostal( std::string &codPostal);

    /**
     * @brief Obtiene la localidad.
     * @return Referencia a la localidad.
     */
    std::string &getLocalidad();

    /**
     * @brief Establece la localidad.
     * @param localidad Nueva localidad.
     */
    void setLocalidad(std::string &localidad);
};


#endif //PRACTICA2_LABORATORIOS_H
