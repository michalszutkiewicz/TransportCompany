#ifndef ATOM_PN_1330_06_POJAZD_H
#define ATOM_PN_1330_06_POJAZD_H
#pragma once
#include "Zasob.h"

class Pojazd : public Zasob {
private:
    double maxLadownosc; // w tonach
    std::string nrRejestracyjny;

public:
    Pojazd(std::string id, std::string nrRej, double ladownosc);

    //nadpisujemy metodę wirtualną z klasy Zasob
    bool czySpełniaWymagania(double wymaganaWaga) const override;

    //metoda
    std::string pobierzNrRej() const { return nrRejestracyjny; }
};

#endif //ATOM_PN_1330_06_POJAZD_H