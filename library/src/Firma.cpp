#include "Firma.h"
#include "Klient.h"
#include "Zasob.h"
#include "Zlecenie.h"
#include <algorithm> //chuj wie czy to sie przyda ale wydaje mi sie ze tak

Firma::Firma(std::string nazwa) : nazwaFirmy(nazwa) {}

void Firma::dodajKlienta(std::shared_ptr<Klient> klient) {
    if (klient) {
        klienci.push_back(klient);
    }
}

const std::vector<std::shared_ptr<Klient>>& Firma::pobierzWszystkichKlientow() const {
    return klienci;
}

void Firma::dodajZasob(std::shared_ptr<Zasob> zasob) {
    if (zasob) {
        zasoby.push_back(zasob);
    }
}

std::vector<std::shared_ptr<Zasob>> Firma::znajdzDostepneZasoby() const {
    std::vector<std::shared_ptr<Zasob>> dostepne;
    for (const auto& z : zasoby) {
        if (z->sprawdzCzyWolny()) {
            dostepne.push_back(z);
        }
    }
    return dostepne;
}

void Firma::utworzZlecenie(std::shared_ptr<Zlecenie> zlecenie) {
    if (zlecenie) {
        zlecenia.push_back(zlecenie);
    }
}

const std::vector<std::shared_ptr<Zlecenie>>& Firma::pobierzWszystkieZlecenia() const {
    return zlecenia;
}

double Firma::obliczCalkowityPrzychod() const {
    double suma = 0;
    for (const auto& z : zlecenia) {
        // Tutaj polimorfizm z klasy Usluga wywołany wewnątrz Zlecenia
        // suma += z->pobierzKoszt(); 
    }
    return suma;
}