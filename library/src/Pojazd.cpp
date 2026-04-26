#include "Pojazd.h"

Pojazd::Pojazd(std::string id, std::string nrRej, double ladownosc) 
    : Zasob(id), nrRejestracyjny(nrRej), maxLadownosc(ladownosc) {}

bool Pojazd::czySpełniaWymagania(double wymaganaWaga) const {
    //sprawdzamy czy pojazd jest wolny ORAZ czy udźwignie towar
    return sprawdzCzyWolny() && (maxLadownosc >= wymaganaWaga);
}