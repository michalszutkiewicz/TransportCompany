#include "../include/BusDostawczy.h"
#include "../include/Zlecenie.h"
#include <sstream>

BusDostawczy::BusDostawczy(std::string nrRej, double kosztAmort, double pojemnoscM3)
    : Pojazd(nrRej, kosztAmort), pojemnoscM3(pojemnoscM3) {}

bool BusDostawczy::czyMozeWykonacZlecenie(const Zlecenie& z) const {
    return sprawdzLadownosc(z.pobierzWymaganaWage(), z.pobierzObjetosc()) &&
           z.pobierzWymaganaKategorie() == pobierzWymaganaKategorie();
}

bool BusDostawczy::sprawdzLadownosc(double wymaganaWaga, double objetosc) const {
    return objetosc <= pojemnoscM3;
}

#include <sstream>

std::string BusDostawczy::pobierzOpisPojazdu() const {
    std::ostringstream oss;
    oss << "[BUS DOSTAWCZY] Nr rej: " << pobierzNrRejestracyjny()
        << " | Koszt amortyzacji: " << pobierzKosztAmortyzacji() << " PLN/km"
        << " | Pojemność: " << pojemnoscM3 << " m3";
    return oss.str();
}



std::string BusDostawczy::serializuj() const {
    std::ostringstream oss;
    oss << "BUS;"
        << pobierzNrRejestracyjny() << ";"
        << pobierzKosztAmortyzacji() << ";"
        << pojemnoscM3;
    return oss.str();
}