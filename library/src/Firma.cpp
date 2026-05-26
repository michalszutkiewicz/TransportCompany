#include "../include/Firma.h"
#include "../include/Klient.h"
#include "../include/Pojazd.h"
#include "../include/Pracownik.h"
#include "../include/Zlecenie.h"
#include <algorithm>

Firma::Firma(std::string nazwa) : nazwaFirmy(nazwa) {}

void Firma::dodajKlienta(std::shared_ptr<Klient> klient) {
    if (klient) {
        klienci.push_back(klient);
    }
}

void Firma::rejestrujPojazd(std::shared_ptr<Pojazd> pojazd) {
    if (pojazd) {
        pojazdy.push_back(pojazd);
    }
}

void Firma::zatrudnijPracownika(std::shared_ptr<Pracownik> pracownik) {
    if (pracownik) {
        pracownicy.push_back(pracownik);
    }
}

void Firma::dodajZlecenie(std::shared_ptr<Zlecenie> zlecenie) {
    if (zlecenie) {
        zlecenia.push_back(zlecenie);
    }
}

std::shared_ptr<Klient> Firma::pobierzKlienta(std::string id) {
    // używamy <algorithm> i wyrażenia lambda do wyszukania klienta
    auto it = std::find_if(klienci.begin(), klienci.end(),
        [&id](const std::shared_ptr<Klient>& k) {
            return k != nullptr && k->pobierzId() == id;
        });

    if (it != klienci.end()) {
        return *it;
    }

    return nullptr;
}

double Firma::obliczCalkowityPrzychod() const {
    double suma = 0.0;
    for (const auto& z : zlecenia) {
        // doliczamy do przychodu tylko Zlecenia, które zostały faktycznie zrealizowane/rozliczone.
        if (z && z->czyJestRozliczone()) {
            suma += z->obliczPelnyKoszt();
        }
    }
    return suma;
}