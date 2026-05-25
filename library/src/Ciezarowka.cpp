#include "../include/Ciezarowka.h"

Ciezarowka::Ciezarowka(std::string nrRej, double kosztAmort, double maksLadownosc, bool wymagaNaczepy)
    : Pojazd(nrRej, kosztAmort), maksLadownoscTony(maksLadownosc), wymagaNaczepy(wymagaNaczepy) {}

bool Ciezarowka::sprawdzLadownosc(double wymaganaWaga, double objetosc) const {

    return (wymaganaWaga / 1000.0) <= maksLadownoscTony;
}

std::string Ciezarowka::pobierzOpisPojazdu() const {
    std::string opis = "Ciezarowka o ladownosci " + std::to_string(maksLadownoscTony) + "t";
    if (wymagaNaczepy) {
        opis += " (wymaga podpiecia naczepy)";
    }
    return opis;
}