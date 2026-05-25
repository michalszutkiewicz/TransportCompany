#include "../include/Pracownik.h"


Pracownik::Pracownik(std::string pesel, std::string imieNazwisko, double stawkaGodzinowa)
    : pesel(pesel), imieNazwisko(imieNazwisko), stawkaGodzinowa(stawkaGodzinowa) {}

bool Pracownik::czyDostepny(const Termin& t) const {
    return true;
}

void Pracownik::zarezerwujTermin(const Termin& t) {
    zajeteTerminy.push_back(t);
}