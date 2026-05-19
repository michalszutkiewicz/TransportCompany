#ifndef ATOM_PN_1330_06_POJAZD_H
#define ATOM_PN_1330_06_POJAZD_H

#pragma once
#include <string>
#include <vector>
#include "Termin.h"

class Pojazd  {
private:
    std::string nrRejestracyjny;
    std::vector<Termin> zajeteTerminy;

public:
    Pojazd(std::string nrRej);

    virtual ~Pojazd() = default;

    bool czyDostepny(const Termin& t) const;
    void zarezerwuj(const Termin& t);

    virtual std::string pobierzOpisPojazdu() const = 0;
};

#endif //ATOM_PN_1330_06_POJAZD_H