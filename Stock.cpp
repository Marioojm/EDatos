//
// Created by mario on 10/11/2025.
//

#include "Stock.h"

Stock::Stock() {

}

Stock::Stock(int idPaMed, int numStock, PaMedicamentos* pa) {

}

Stock::~Stock() {

}

int Stock::getIdPaMed() const {
    return id_PaMed;
}

void Stock::setIdPaMed(int idPaMed) {
    Stock::id_PaMed = idPaMed;
}

int Stock::getNumStock() const {
    return num_stock;
}

void Stock::setNumStock(int numStock) {
    Stock::num_stock=numStock;
}

PaMedicamentos *Stock::getNumber() const {
    return number;
}

void Stock::setNumber(PaMedicamentos *number) {
    Stock::number=number;
}

bool Stock::operator<(const Stock &rhs) const {
    return this->id_PaMed > rhs.id_PaMed;
}

void Stock::decrementa(int n) {
    if(n>num_stock || n<0) {
        throw std::invalid_argument("Valor de n no válido");
    }
    num_stock=num_stock-n;
}

void Stock::aumenta(int n) {
    if(n<0) {
        throw std::invalid_argument("Valor de n no válido");
    }
    num_stock=num_stock+n;
}
