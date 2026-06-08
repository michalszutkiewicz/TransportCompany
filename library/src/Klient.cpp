/**
* @file Klient.cpp
 * @brief Implementacja klasy Klient reprezentującej podmiot zlecający usługi transportowe.
 */
#include "Klient.h"
#include <iostream>
#include <sstream>

/**
 * @brief Konstruktor obiektu Klient.
 * @param id Unikalny identyfikator klienta w systemie.
 * @param imie Imię klienta (lub nazwa firmy).
 * @param nazwisko Nazwisko klienta.
 */
Klient::Klient(std::string id, std::string imie, std::string nazwisko)
    : idKlienta(id), imie(imie), nazwisko(nazwisko) {}

/**
 * @brief Pobiera pełne dane klienta w formie czytelnej dla użytkownika.
 * @return Ciąg znaków zawierający imię, nazwisko oraz identyfikator klienta.
 */
std::string Klient::pobierzPelneDane() const {
    return imie + " " + nazwisko + " (ID: " + idKlienta + ")";
}

/**
 * @brief Serializuje dane klienta do formatu tekstowego dla potrzeb trwałego zapisu.
 * * Format zapisu: "id;imie;nazwisko".
 * @return Ciąg znaków z danymi klienta gotowy do zapisu w pliku.
 */
std::string Klient::serializuj() const {
    std::ostringstream oss;
    oss << idKlienta << ";" << imie << ";" << nazwisko;
    return oss.str();
}