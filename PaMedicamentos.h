#ifndef P1_PAMEDICAMENTOS_H
#define P1_PAMEDICAMENTOS_H


#include <string>
#include "Laboratorios.h"

class PaMedicamentos {
private:
    int _id_num;
    std::string _id_alpha;
    std::string _nombre;

    Laboratorios* _laboratorio = nullptr;
public:
    PaMedicamentos();
    PaMedicamentos(int id_num, std::string id_alpha, std::string nombre);
    PaMedicamentos(const PaMedicamentos &orig);
    ~PaMedicamentos();
    int getIdNum() const;
    void setIdNum( int id_num);
    const std::string &getIdAlpha() const ;
    void setIdAlpha(std::string id_alpha);
    const std::string &getNombre() const;
    void setNombre(std::string nombre);
    bool operator==(const PaMedicamentos &otro);
    bool operator<(const PaMedicamentos &otro);

    void servidoPor(Laboratorios *lab);
    Laboratorios* servidoPor() const;
};


#endif //P1_PAMEDICAMENTOS_H

