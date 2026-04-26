#ifndef ATOM_PN_1330_06_TRANSPORTEKSPRESOWY_H
#define ATOM_PN_1330_06_TRANSPORTEKSPRESOWY_H
#pragma once
#include "Usluga.h"

class TransportEkspresowy : public Usluga {
private:
    double stawkaEkspresowa;
    double oplataStala;

public:
    TransportEkspresowy(std::string nazwa, double dystans, double stawka, double extra);

    double obliczKoszt() const override;
    std::string pobierzSzczegoly() const override;
};

#endif //ATOM_PN_1330_06_TRANSPORTEKSPRESOWY_H