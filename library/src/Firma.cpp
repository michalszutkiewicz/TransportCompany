#include "Firma.h"

using namespace std;

Firma::Firma() {
    // Miejsce na inicjalizację danymi testowymi zgodnie z wytycznymi UML
}

RepozytoriumKlientow& Firma::pobierzRepozytoriumKlientow() {
    return repoKlientow;
}

RepozytoriumPojazdow& Firma::pobierzRepozytoriumPojazdow() {
    return repoPojazdow;
}

RepozytoriumPracownikow& Firma::pobierzRepozytoriumPracownikow() {
    return repoPracownikow;
}

RepozytoriumZlecen& Firma::pobierzRepozytoriumZlecen() {
    return repoZlecen;
}

double Firma::obliczCalkowityPrzychod() const {
    double suma = 0.0;
    auto zlecenia = repoZlecen.pobierzWszystkie();

    for (const auto& z : zlecenia) {
        if (z && z->czyJestRozliczone()) {
            suma += z->obliczPelnyKoszt();
        }
    }
    return suma;
}