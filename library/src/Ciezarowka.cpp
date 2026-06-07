#include "../include/Ciezarowka.h"
#include "../include/Zlecenie.h"
#include <sstream>

Ciezarowka::Ciezarowka(std::string nrRej, double kosztAmort, double maksLadownosc, bool wymagaNaczepy)
    : Pojazd(nrRej, kosztAmort), maksLadownoscTony(maksLadownosc), wymagaNaczepy(wymagaNaczepy) {}

bool Ciezarowka::czyMozeWykonacZlecenie(const Zlecenie& z) const {
    return sprawdzLadownosc(z.pobierzWymaganaWage(), z.pobierzObjetosc()) &&
           z.pobierzWymaganaKategorie() == pobierzWymaganaKategorie();
}

bool Ciezarowka::sprawdzLadownosc(double wymaganaWaga, double objetosc) const {
    return (wymaganaWaga / 1000.0) <= maksLadownoscTony;
}

std::string Ciezarowka::pobierzOpisPojazdu() const {
    std::ostringstream oss;
    oss << "[CIEŻARÓWKA] Nr rej: " << pobierzNrRejestracyjny()
        << " | Koszt amortyzacji: " << pobierzKosztAmortyzacji() << " PLN/km"
        << " | Ładowność: " << maksLadownoscTony << "t"
        << " | Naczepa: " << (wymagaNaczepy ? "TAK" : "NIE");
    return oss.str();
}

std::string Ciezarowka::serializuj() const {
    std::ostringstream oss;
    oss << "CIEZAROWKA;"
        << pobierzNrRejestracyjny() << ";"
        << pobierzKosztAmortyzacji() << ";"
        << maksLadownoscTony << ";"
        << (wymagaNaczepy ? "1" : "0");
    return oss.str();
}