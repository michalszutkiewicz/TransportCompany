#include "../include/Usluga.h"

Usluga::Usluga(std::string nazwa, double dystans)
    : nazwaZlecenia(nazwa), dystans(dystans) {}

std::string Usluga::pobierzNazwe() const {
    return nazwaZlecenia;
}