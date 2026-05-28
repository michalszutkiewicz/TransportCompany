#include "../include/Pojazd.h"

Pojazd::Pojazd(std::string nrRej, double kosztAmortyzacji)
    : nrRejestracyjny(nrRej), kosztAmortyzacji(kosztAmortyzacji) {}

bool Pojazd::czyDostepny(const Termin& t) const {
    for (const auto& zajety : zajeteTerminy) {
        if (zajety.czyKoliduje(t)) {
            return false;
        }
    }
    return true;
}

void Pojazd::zarezerwujTermin(const Termin& t) {
    zajeteTerminy.push_back(t);
}