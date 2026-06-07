#include "../include/Kierowca.h"
#include "../include/Zlecenie.h"
#include <algorithm> // Wymagane dla std::find
#include <sstream>

Kierowca::Kierowca(std::string pesel, std::string imieNazwisko, double stawkaGodzinowa, std::vector<std::string> kategorie)
    : Pracownik(pesel, imieNazwisko, stawkaGodzinowa), kategoriePrawaJazdy(kategorie) {}

bool Kierowca::czyUmieWykonacZlecenie(const Zlecenie& z) const {
    return mozeWykonacPrace(z.pobierzWymaganaKategorie());
}

bool Kierowca::mozeWykonacPrace(std::string wymaganaKategoria) const {
    // czy wymagana kategoria znajduje się w wektorze posiadanych kategorii
    return std::find(kategoriePrawaJazdy.begin(), kategoriePrawaJazdy.end(), wymaganaKategoria) != kategoriePrawaJazdy.end();
}

std::string Kierowca::pobierzRole() const {
    return "Kierowca";
}

std::string Kierowca::pobierzPelneDane() const {
    std::ostringstream oss;
    oss << "[KIEROWCA] PESEL: " << pobierzPesel()
        << " | Imię i Nazwisko: " << pobierzImieNazwisko()
        << " | Stawka: " << pobierzStawke() << " PLN/h"
        << " | Kategorie: ";

    for (size_t i = 0; i < kategoriePrawaJazdy.size(); ++i) {
        oss << kategoriePrawaJazdy[i];
        if (i < kategoriePrawaJazdy.size() - 1) oss << ", ";
    }
    return oss.str();
}

std::string Kierowca::serializuj() const {
    std::ostringstream oss;
    oss << "KIEROWCA;"
        << pobierzPesel() << ";"
        << pobierzImieNazwisko() << ";"
        << pobierzStawke() << ";";

    for (size_t i = 0; i < kategoriePrawaJazdy.size(); ++i) {
        oss << kategoriePrawaJazdy[i];
        if (i < kategoriePrawaJazdy.size() - 1) {
            oss << ",";
        }
    }

    return oss.str();
}