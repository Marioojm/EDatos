#ifndef PRACTICA4_STOCK_H
#define PRACTICA4_STOCK_H


#include "PaMedicamentos.h"
#include "stdexcept"

class Stock {
public:
    Stock();
    Stock(int idPaMed, int numStock, PaMedicamentos* pa);
    virtual ~Stock();

    int getIdPaMed() const;
    void setIdPaMed(int idPaMed);
    int getNumStock() const;
    void setNumStock(int numStock);
    PaMedicamentos *getNumber() const;
    void setNumber(PaMedicamentos *number);

    bool operator<(const Stock &rhs) const; //Este const es obligatorio ya que es el objeto es inmutable.

    void decrementa(int n);
    void aumenta(int n);

private:
    int id_PaMed;
    int num_stock;  //opcional mutable
    PaMedicamentos* number;
};


#endif //PRACTICA4_STOCK_H
