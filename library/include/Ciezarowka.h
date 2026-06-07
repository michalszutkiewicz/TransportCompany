#ifndef ATOM_PN_1330_06_CIEZAROWKA_H
#define ATOM_PN_1330_06_CIEZAROWKA_H

#pragma once
#include "Pojazd.h"

class Ciezarowka : public Pojazd {
private:
    double maksLadownoscTony;
    bool wymagaNaczepy;

public:
    Ciezarowka(std::string nrRej, double kosztAmortyzacji, double maksLadownosc, bool wymagaNaczepy);

    bool czyMozeWykonacZlecenie(const Zlecenie& z) const override;
    bool sprawdzLadownosc(double wymaganaWaga, double objetosc) const override;
    std::string pobierzWymaganaKategorie() const override { return "C"; }
    std::string pobierzOpisPojazdu() const override;

    std::string serializuj() const override;
};

#endif //ATOM_PN_1330_06_CIEZAROWKA_H