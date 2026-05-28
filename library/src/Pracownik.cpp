#include "../include/Pracownik.h"


Pracownik::Pracownik(std::string pesel, std::string imieNazwisko, double stawkaGodzinowa)
    : pesel(pesel), imieNazwisko(imieNazwisko), stawkaGodzinowa(stawkaGodzinowa) {}

bool Pracownik::czyDostepny(const Termin& t) const {
    for (const auto& zajety : zajeteTerminy) {
        if (zajety.czyKoliduje(t)) {
            return false;
        }
    }
    return true;
}

void Pracownik::zarezerwujTermin(const Termin& t) {
    zajeteTerminy.push_back(t);
}