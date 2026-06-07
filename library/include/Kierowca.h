#ifndef ATOM_PN_1330_06_KIEROWCA_H
#define ATOM_PN_1330_06_KIEROWCA_H

#pragma once
#include <string>
#include <vector>
#include "Pracownik.h"

class Kierowca : public Pracownik {
private:
    std::vector<std::string> kategoriePrawaJazdy;

public:
    Kierowca(std::string pesel, std::string imieNazwisko, double stawkaGodzinowa, std::vector<std::string> kategorie);

    bool czyUmieWykonacZlecenie(const Zlecenie& z) const override;
    bool mozeWykonacPrace(std::string wymaganaKategoria) const override;
    std::string pobierzRole() const override;
    std::string pobierzPelneDane() const override;

    std::string serializuj() const override;
};

#endif //ATOM_PN_1330_06_KIEROWCA_H