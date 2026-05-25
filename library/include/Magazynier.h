#ifndef ATOM_PN_1330_06_MAGAZYNIER_H
#define ATOM_PN_1330_06_MAGAZYNIER_H

#pragma once
#include <string>
#include "Pracownik.h"

class Magazynier : public Pracownik {
private:
    bool uprawnieniaNaWozkiWidlowe;

public:
    Magazynier(std::string pesel, std::string imieNazwisko, double stawkaGodzinowa, bool uprawnienia);

    bool mozeWykonacPrace(std::string wymaganaKategoria) const override;
    std::string pobierzRole() const override;
};

#endif //ATOM_PN_1330_06_MAGAZYNIER_H