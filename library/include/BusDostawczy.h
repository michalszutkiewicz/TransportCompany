#ifndef POBI_BUSDOSTAWCZY_H
#define POBI_BUSDOSTAWCZY_H

#pragma once

#include "Pojazd.h"

class BusDostawczy : public Pojazd {
private:
    double pojemnoscM3;

public:
    BusDostawczy(std::string nrRej, double pojemnoscM3);

    // Nadpisujemy metody z klasy Pojazd
    bool sprawdzLadownosc(double wymaganaWaga, double objetosc) const override;
    std::string pobierzOpisPojazdu() const override;
};

#endif //POBI_BUSDOSTAWCZY_H