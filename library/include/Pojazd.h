#ifndef ATOM_PN_1330_06_POJAZD_H
#define ATOM_PN_1330_06_POJAZD_H

#pragma once
#include <string>
#include <vector>
#include "Termin.h"

class Pojazd  {
private:
    std::string nrRejestracyjny;
    double kosztAmortyzacji;
    std::vector<Termin> zajeteTerminy;

public:
    Pojazd(std::string nrRej, double kosztAmortyzacji);
    virtual ~Pojazd() = default;

    bool czyDostepny(const Termin& t) const;
    void zarezerwujTermin(const Termin& t);

    virtual bool sprawdzLadownosc(double wymaganaWaga, double objetosc) const = 0;
    virtual std::string pobierzWymaganaKategorie() const = 0;
    virtual std::string pobierzOpisPojazdu() const = 0;
};

#endif //ATOM_PN_1330_06_POJAZD_H