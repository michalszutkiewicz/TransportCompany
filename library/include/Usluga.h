#ifndef ATOM_PN_1330_06_USLUGA_H
#define ATOM_PN_1330_06_USLUGA_H

#pragma once
#include <string>

class Usluga {
protected:
    std::string nazwaZlecenia;
    double dystans; // w kilometrach

public:
    Usluga(std::string nazwa, double dystans);

    // WIRTUALNY DESTRUKTOR
    virtual ~Usluga() = default;

    // metody czysto wirtualne
    virtual double obliczKoszt() const = 0;
    virtual std::string pobierzSzczegoly() const = 0;

    std::string pobierzNazwe() const;
};

#endif //ATOM_PN_1330_06_USLUGA_H