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

    bool mozeWykonacPrace(std::string wymaganaKategoria) const override;
    std::string pobierzRole() const override;
};

#endif //ATOM_PN_1330_06_KIEROWCA_H