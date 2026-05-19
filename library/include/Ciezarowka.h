#ifndef ATOM_PN_1330_06_POJAZD_H
#define ATOM_PN_1330_06_POJAZD_H
#pragma once
#include "Pojazd.h"

class Ciezarowka: public Pojazd{
private:
    double maxLadownosc; // w tonach
    bool wymagaNaczepy;

public:
    Ciezarowka(std::string nrRej, double maksLadownosc, bool wymagaNaczepy);

    // Nadpisujemy metody z klasy Pojazd
    bool sprawdzLadownosc(double wymaganaWaga, double objetosc) const override;

    std::string pobierzOpisPojazdu() const override;
};

#endif //ATOM_PN_1330_06_POJAZD_H