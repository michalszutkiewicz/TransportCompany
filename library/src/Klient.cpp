#include "Klient.h"

Klient::Klient(std::string id, std::string imie, std::string nazwisko)
    : idKlienta(id), imie(imie), nazwisko(nazwisko) {}

std::string Klient::pobierzPelneDane() const {
    return imie + " " + nazwisko + " (ID: " + idKlienta + ")";
}
