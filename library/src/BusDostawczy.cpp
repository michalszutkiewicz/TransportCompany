#include "../include/BusDostawczy.h"

BusDostawczy::BusDostawczy(std::string nrRej, double kosztAmort, double pojemnoscM3)
    : Pojazd(nrRej, kosztAmort), pojemnoscM3(pojemnoscM3) {}

bool BusDostawczy::sprawdzLadownosc(double wymaganaWaga, double objetosc) const {
    return objetosc <= pojemnoscM3;
}

std::string BusDostawczy::pobierzOpisPojazdu() const {
    return "Bus dostawczy z przestrzenia ladunkowa: " + std::to_string(pojemnoscM3) + " m^3";
}