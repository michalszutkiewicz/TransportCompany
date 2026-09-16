/**
 * @file Usluga.h
 * @brief Definicja klasy bazowej Usluga dla systemu zarządzania transportem.
 */

#ifndef ATOM_PN_1330_06_USLUGA_H
#define ATOM_PN_1330_06_USLUGA_H

#pragma once
#include <string>
#include <memory>

class Usluga {
protected:
    std::string nazwaZlecenia; ///< Nazwa lub identyfikator zlecenia.
    double dystans;            ///< Dystans do pokonania wyrażony w kilometrach.

public:
    Usluga(std::string nazwa, double dystans);
    virtual ~Usluga() = default;

    // Metody czysto wirtualne (wymagane w klasach pochodnych)
    virtual double obliczKoszt() const = 0;
    virtual std::string pobierzSzczegoly() const = 0;

    // Gettery zaimplementowane w Usluga.cpp
    std::string pobierzNazwe() const;
    double pobierzDystans() const;
};

#endif //ATOM_PN_1330_06_USLUGA_H