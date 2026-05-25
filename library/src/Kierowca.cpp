#include "../include/Kierowca.h"
#include <algorithm> // Wymagane dla std::find

Kierowca::Kierowca(std::string pesel, std::string imieNazwisko, double stawkaGodzinowa, std::vector<std::string> kategorie)
    : Pracownik(pesel, imieNazwisko, stawkaGodzinowa), kategoriePrawaJazdy(kategorie) {}

bool Kierowca::mozeWykonacPrace(std::string wymaganaKategoria) const {
    // czy wymagana kategoria znajduje się w wektorze posiadanych kategorii
    return std::find(kategoriePrawaJazdy.begin(), kategoriePrawaJazdy.end(), wymaganaKategoria) != kategoriePrawaJazdy.end();
}

std::string Kierowca::pobierzRole() const {
    return "Kierowca";
}