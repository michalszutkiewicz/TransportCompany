#include "../include/Klient.h"

Klient::Klient(std::string imie, std::string nazwisko, std::string id)
    : imie(imie), nazwisko(nazwisko), idKlienta(id) {}

std::string Klient::pobierzPelneDane() const {
    return imie + " " + nazwisko + " (ID: " + idKlienta + ")";
}