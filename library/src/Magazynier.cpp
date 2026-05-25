#include "../include/Magazynier.h"

Magazynier::Magazynier(std::string pesel, std::string imieNazwisko, double stawkaGodzinowa, bool uprawnienia)
    : Pracownik(pesel, imieNazwisko, stawkaGodzinowa), uprawnieniaNaWozkiWidlowe(uprawnienia) {}

bool Magazynier::mozeWykonacPrace(std::string wymaganaKategoria) const {
    // jeśli praca wymaga wózka, sprawdzamy uprawnienia.
    if (wymaganaKategoria == "WozekWidlowy") {
        return uprawnieniaNaWozkiWidlowe;
    }
    // jeśli nie wymaga wózka, zakładamy, że magazynier może to zrobić
    return true; 
}

std::string Magazynier::pobierzRole() const {
    return "Magazynier";
}