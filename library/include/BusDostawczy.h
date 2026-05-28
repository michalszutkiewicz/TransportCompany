#ifndef ATOM_PN_1330_06_BUSDOSTAWCZY_H
#define ATOM_PN_1330_06_BUSDOSTAWCZY_H

#pragma once
#include "Pojazd.h"

class BusDostawczy : public Pojazd {
private:
    double pojemnoscM3;

public:
    BusDostawczy(std::string nrRej, double kosztAmortyzacji, double pojemnoscM3);

    bool sprawdzLadownosc(double wymaganaWaga, double objetosc) const override;
    std::string pobierzWymaganaKategorie() const override { return "B"; }
    std::string pobierzOpisPojazdu() const override;
};

#endif //ATOM_PN_1330_06_BUSDOSTAWCZY_H