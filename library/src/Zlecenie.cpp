#include "../include/Zlecenie.h"
#include "Klient.h"
#include "Usluga.h"
#include "Zasob.h"

Zlecenie::Zlecenie(std::string id, std::string termin, std::shared_ptr<Klient> k, std::shared_ptr<Usluga> u)
    : idZlecenia(id), terminRealizacji(termin), klient(k), usluga(u), czyRozliczone(false) {}

void Zlecenie::dodajZasob(std::shared_ptr<Zasob> zasob) {
    if (zasob) {
        przypisaneZasoby.push_back(zasob);
        zasob->ustawDostepnosc(false); //automatyczna rezerwacja zasobu(jak uzywamy w tym zleceniu to nie moze byc przypisane do innego )
    }
}

double Zlecenie::obliczPelnyKoszt() const {
    if (usluga) {
        return usluga->obliczKoszt(); //polimorficzne wywołanie
    }
    return 0.0;
}


//nwm czy to jest dobrze bo mozg mi to spalilo wiec jak co to popraw!!!!
std::string Zlecenie::pobierzPodsumowanie() const {
    std::string info = "Zlecenie nr: " + idZlecenia + " | Termin: " + terminRealizacji;
    info += "\nKlient: " + (klient ? klient->pobierzPelneDane() : "Brak danych");
    info += "\nKoszt: " + std::to_string(obliczPelnyKoszt()) + " PLN";
    info += "\nStatus: " + std::string(czyRozliczone ? "Rozliczone" : "W realizacji");
    return info;
}