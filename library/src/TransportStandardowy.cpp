#include "../include/TransportStandardowy.h"
#include <iomanip> //do zaokrąglania w stringa bo inaczej gowno wyjdzie z cena
#include <sstream>

TransportStandardowy::TransportStandardowy(std::string nazwa, double dystans, double stawka)
    : Usluga(nazwa, dystans), stawkaZaKm(stawka) {}

double TransportStandardowy::obliczKoszt() const {
    return dystans * stawkaZaKm;
}

std::string TransportStandardowy::pobierzSzczegoly() const {
    std::stringstream ss;
    ss << "Typ: Standardowy | Dystans: " << dystans << " km | Stawka: " << stawkaZaKm << " PLN/km";
    return ss.str();
}