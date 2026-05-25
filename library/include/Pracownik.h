#ifndef ATOM_PN_1330_06_PRACOWNIK_H
#define ATOM_PN_1330_06_PRACOWNIK_H

#pragma once
#include <string>
#include <vector>
#include "Termin.h"

class Pracownik {
private:
    std::string pesel;
    std::string imieNazwisko;
    double stawkaGodzinowa;
    std::vector<Termin> zajeteTerminy;

public:
    Pracownik(std::string pesel, std::string imieNazwisko, double stawkaGodzinowa);
    virtual ~Pracownik() = default;

    bool czyDostepny(const Termin& t) const;
    void zarezerwujTermin(const Termin& t);

    // Metody czysto wirtualne
    virtual bool mozeWykonacPrace(std::string wymaganaKategoria) const = 0;
    virtual std::string pobierzRole() const = 0;
};

#endif //ATOM_PN_1330_06_PRACOWNIK_H