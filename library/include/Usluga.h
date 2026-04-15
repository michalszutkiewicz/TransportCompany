#pragma once
#include <string>

#ifndef ATOM_PN_1330_06_USLUGA_H
#define ATOM_PN_1330_06_USLUGA_H


class Usluga {
protected:
    std::string nazwaZlecenia;
    double dystans; // w kilometrach

public:
    // Konstruktor
    Usluga(std::string nazwa, double dystans)
        : nazwaZlecenia(nazwa), dystans(dystans) {}

    // WIRTUALNY DESTRUKTOR (kluczowy przy polimorfizmie)
    virtual ~Usluga() = default;

    virtual double obliczKoszt() const = 0;
    virtual std::string pobierzSzczegoly() const = 0;
    std::string pobierzNazwe() const { return nazwaZlecenia; }
};
#endif //ATOM_PN_1330_06_USLUGA_H
