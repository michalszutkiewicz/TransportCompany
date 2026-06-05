#include "../include/Zlecenie.h"
#include "../include/Klient.h"
#include "../include/Usluga.h"
#include "../include/Pojazd.h"
#include "../include/Pracownik.h"

Zlecenie::Zlecenie(std::string id, Termin okres, std::shared_ptr<Klient> k, std::shared_ptr<Usluga> u, double waga, double obj, std::string kat)
    : idZlecenia(id), okresRealizacji(okres), klient(k), usluga(u), czyRozliczone(false), wymaganaWaga(waga), objetosc(obj), wymaganaKategoria(kat) {}

void Zlecenie::dodajPojazd(std::shared_ptr<Pojazd> p) {
    if (p) {
        przypisanePojazdy.push_back(p);
        p->zarezerwujTermin(okresRealizacji);
    }
}

void Zlecenie::dodajPracownika(std::shared_ptr<Pracownik> pr) {
    if (pr) {
        przypisaniPracownicy.push_back(pr);
        pr->zarezerwujTermin(okresRealizacji);
    }
}

double Zlecenie::obliczPelnyKoszt() const {
    if (usluga) {
        return usluga->obliczKoszt();
    }
    return 0.0;
}

void Zlecenie::rozlicz() {
    czyRozliczone = true;
}

Termin Zlecenie::pobierzOkres() const {
    return okresRealizacji;
}

std::string Zlecenie::pobierzPodsumowanie() const {
    std::string info = "Zlecenie nr: " + idZlecenia;

    info += "\nKlient: " + (klient ? klient->pobierzPelneDane() : "Brak danych");
    info += "\nKoszt: " + std::to_string(obliczPelnyKoszt()) + " PLN";
    info += "\nStatus: " + std::string(czyRozliczone ? "Rozliczone" : "W realizacji");

    info += "\nPrzypisani pracownicy: " + std::to_string(przypisaniPracownicy.size());
    info += "\nPrzypisane pojazdy: " + std::to_string(przypisanePojazdy.size());

    return info;
}
