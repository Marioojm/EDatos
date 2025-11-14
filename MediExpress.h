#ifndef PRACTICA2_MEDIEXPRESS_H
#define PRACTICA2_MEDIEXPRESS_H


#include <iostream>
#include "PaMedicamentos.h"
#include "Laboratorios.h"
#include "Farmacia.h"
#include "vector"
#include "list"
#include "map"

using namespace std;


class MediExpress {
public:
    MediExpress();
    MediExpress(const std::string &nomFichPaMed, const std::string &nomFichLab, const std::string &nomFichFar);
    MediExpress(const MediExpress &orig);
    virtual ~MediExpress();

    void suministrarMed(PaMedicamentos *pa, Laboratorios *l);

    void suministrarFarmacia(Farmacia* f, int id_num, int n);


    Laboratorios* buscarLab(std::string nombreLab);
    vector<Laboratorios*> buscarLabCiudad(const std::string &nombreCiudad);
    vector<Laboratorios*> buscarLabs(const std::string &nombrePA);


    PaMedicamentos* buscarCompuesto(int id_num);
    vector<PaMedicamentos*> buscarCompuesto(const std::string &nombrePA);
    vector<PaMedicamentos*> PaMedSinLab();


    vector<PaMedicamentos*> buscarMedicamentoNombre(const string &nombre);


    Farmacia* buscarFarmacia(const std::string &cif);
    vector<Farmacia*> buscarFarmacias(const std::string &provincia);

    void eliminaLaboratorio(const std::string &localidad);

    bool eliminaMedicamento(int id_num);



private:
    map<int,PaMedicamentos> medication;
    list<Laboratorios> labs;
    vector<Farmacia> pharmacy;




};

#endif //PRACTICA2_MEDIEXPRESS_H
