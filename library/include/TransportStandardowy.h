#ifndef ATOM_PN_1330_06_TRANSPORTSTANDARDOWY_H
#define ATOM_PN_1330_06_TRANSPORTSTANDARDOWY_H
#pragma once
#include "Usluga.h"

class TransportStandardowy : public Usluga {
private:
    double stawkaZaKm;

public:
    TransportStandardowy(std::string nazwa, double dystans, double stawka);

    // Nadpisujemy metody wirtualne
    double obliczKoszt() const override;
    std::string pobierzSzczegoly() const override;
};

#endif //ATOM_PN_1330_06_TRANSPORTSTANDARDOWY_H