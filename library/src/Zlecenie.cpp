#include "../include/Zlecenie.h"
#include "../include/Klient.h"
#include "../include/Usluga.h"
#include "../include/Pojazd.h"
#include "../include/Pracownik.h"

Zlecenie::Zlecenie(std::string id, Termin okres, std::shared_ptr<Klient> k, std::shared_ptr<Usluga> u)
    : idZlecenia(id), okresRealizacji(okres), klient(k), usluga(u), czyRozliczone(false) {}

void Zlecenie::dodajPojazd(std::shared_ptr<Pojazd> pojazd) {
    if (pojazd) {
        przypisanePojazdy.push_back(pojazd);
        // automatyczna rezerwacja konkretnego terminu
        pojazd->zarezerwujTermin(okresRealizacji);
    }
}

void Zlecenie::dodajPracownika(std::shared_ptr<Pracownik> pracownik) {
    if (pracownik) {
        przypisaniPracownicy.push_back(pracownik);
        // automatyczna rezerwacja konkretnego terminu u pracownika
        pracownik->zarezerwujTermin(okresRealizacji);
    }
}

double Zlecenie::obliczPelnyKoszt() const {
    if (usluga) {
        return usluga->obliczKoszt();
    }
    return 0;
}

std::string Zlecenie::pobierzPodsumowanie() const {
    std::string info = "Zlecenie nr: " + idZlecenia;

    info += "\nKlient: " + (klient ? klient->pobierzPelneDane() : "Brak danych");
    info += "\nKoszt: " + std::to_string(obliczPelnyKoszt()) + " PLN";
    info += "\nStatus: " + std::string(czyRozliczone ? "Rozliczone" : "W realizacji");

    // Dodatkowe statystyki pokazujące stan zasobów
    info += "\nPrzypisani pracownicy: " + std::to_string(przypisaniPracownicy.size());
    info += "\nPrzypisane pojazdy: " + std::to_string(przypisanePojazdy.size());

    return info;
}