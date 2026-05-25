#include "../include/Pojazd.h"

Pojazd::Pojazd(std::string nrRej, double kosztAmortyzacji)
    : nrRejestracyjny(nrRej), kosztAmortyzacji(kosztAmortyzacji) {}

bool Pojazd::czyDostepny(const Termin& t) const {
    return true; 
}

void Pojazd::zarezerwujTermin(const Termin& t) {
    zajeteTerminy.push_back(t);
}