#ifndef PRACTICA4_FARMACIA_H
#define PRACTICA4_FARMACIA_H


#include <iostream>
#include "PaMedicamentos.h"
#include <set>
#include <vector>
#include "Stock.h"


class MediExpress;

class Farmacia {

private:
    std::string cif;
    std::string provincia;
    std::string localidad;
    std::string nombre;
    std::string direcion;
    std::string codPostal;

    std::set<Stock> order;

    MediExpress *linkMedi;

public:


    Farmacia();


    Farmacia(const std::string &cif, const std::string &provincia, const std::string &localidad,
             const std::string &nombre, const std::string &direcion,
             const std::string &codPostal, MediExpress* med);


    Farmacia(const Farmacia &orig);

    virtual ~Farmacia();

    const std::string &getCif() const;
    const std::string &getProvincia() const;
    const std::string &getLocalidad() const;
    const std::string &getNombre() const;
    const std::string &getDirecion() const;
    const std::string &getCodPostal() const;

    void setCif(const std::string &cif);
    void setProvincia(const std::string &provincia);
    void setLocalidad(const std::string &localidad);
    void setNombre(const std::string &nombre);
    void setDirecion(const std::string &direcion);
    void setCodPostal(const std::string &codPostal);

    bool operator==(const Farmacia &rhs) const;
    bool operator<(const Farmacia &rhs) const;
    bool operator>(const Farmacia &other) const;


    int buscaMedicamID(int id_num);

    std::vector<PaMedicamentos*> buscaMedicamentoNombre(const std::string &nombre);

    void nuevoStock(PaMedicamentos* pa, int n);

    int comprarMedicamento(int id_num, int n, PaMedicamentos* &result);

    bool eliminarStock(int id_num);


private:
    void pedidoMedicam(int id_num, int n);

};

#endif //PRACTICA4_FARMACIA_H
