#include "../include/Magazynier.h"

Magazynier::Magazynier(std::string pesel, std::string imieNazwisko, double stawkaGodzinowa, bool uprawnienia)
    : Pracownik(pesel, imieNazwisko, stawkaGodzinowa), uprawnieniaNaWozkiWidlowe(uprawnienia) {}

bool Magazynier::mozeWykonacPrace(std::string wymaganaKategoria) const {
    // jeśli praca wymaga wózka, sprawdzamy uprawnienia.
    if (wymaganaKategoria == "WozekWidlowy") {
        return uprawnieniaNaWozkiWidlowe;
    }
    
    // Magazynier nie posiada kategorii prawa jazdy (B, C, C+E)
    if (wymaganaKategoria == "B" || wymaganaKategoria == "C" || wymaganaKategoria == "C+E") {
        return false;
    }

    // Dla innych ogólnych prac (nie wymagających uprawnień) zwracamy true
    return true; 
}

std::string Magazynier::pobierzRole() const {
    return "Magazynier";
}