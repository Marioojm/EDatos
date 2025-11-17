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


    Laboratorios();

    Laboratorios(int id, const std::string &nombreLab, const std::string &direccion, const std::string &codPostal,
                 const std::string &localidad);

    Laboratorios(const Laboratorios& orig);

    ~Laboratorios();


    void setId(int id);
    void setNombreLab(std::string &nombreLab);
    void setDireccion(std::string &direccion);
    void setCodPostal( std::string &codPostal);
    void setLocalidad(std::string &localidad);

    int getId() const;
    std::string &getNombreLab();
    std::string &getDireccion();
    std::string &getCodPostal() ;
    std::string &getLocalidad();

};


#endif //PRACTICA2_LABORATORIOS_H
