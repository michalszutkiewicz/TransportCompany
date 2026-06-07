#include "Klient.h"

#include <iostream>
#include <sstream>

Klient::Klient(std::string id, std::string imie, std::string nazwisko)
    : idKlienta(id), imie(imie), nazwisko(nazwisko) {}

std::string Klient::pobierzPelneDane() const {
    return imie + " " + nazwisko + " (ID: " + idKlienta + ")";
}

std::string Klient::serializuj() const {
    std::ostringstream oss;
    oss << idKlienta << ";" << imie << ";" << nazwisko;
    return oss.str();
}