#ifndef ATOM_PN_1330_06_PRACOWNIK_H
#define ATOM_PN_1330_06_PRACOWNIK_H

#pragma once
#include <string>
#include <vector>
#include "Termin.h"

class Zlecenie;

class Pracownik {
private:
    std::string idPracownika;
    std::string imieNazwisko;
    double stawkaGodzinowa;
    std::vector<Termin> zajeteTerminy;

public:
    Pracownik(std::string id, std::string imieNazwisko, double stawkaGodzinowa);
    virtual ~Pracownik() = default;

    bool czyDostepny(const Termin& t) const;
    void zarezerwujTermin(const Termin& t);

    // Metody czysto wirtualne
    virtual bool czyUmieWykonacZlecenie(const Zlecenie& z) const = 0;
    virtual bool mozeWykonacPrace(std::string wymaganaKategoria) const = 0;
    virtual std::string pobierzRole() const = 0;

    std::string pobierzIdPracownika() const { return idPracownika; }
    // alias dla zgodności z Repo
    std::string pobierzPesel() const { return idPracownika; }
};

#endif //ATOM_PN_1330_06_PRACOWNIK_H
