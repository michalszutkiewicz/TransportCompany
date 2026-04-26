#ifndef ATOM_PN_1330_06_PRACOWNIK_H
#define ATOM_PN_1330_06_PRACOWNIK_H
#pragma once
#include "Zasob.h"

class Pracownik : public Zasob {
private:
    std::string imieNazwisko;
    std::string pesel;
    bool posiadaUprawnieniaCE;

public:
    Pracownik(std::string id, std::string dane, std::string psl, bool uprawnienia);

    // Nadpisujemy metodę wirtualną
    bool czySpełniaWymagania(double progUmiejetnosci) const override;

    std::string pobierzDane() const { return imieNazwisko; }
};
#endif //ATOM_PN_1330_06_PRACOWNIK_H