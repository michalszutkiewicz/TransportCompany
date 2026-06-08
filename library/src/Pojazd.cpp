/**
* @file Pojazd.cpp
 * @brief Implementacja bazowej klasy Pojazd zarządzającej dostępnością zasobów.
 */

#include "../include/Pojazd.h"

/**
 * @brief Konstruktor obiektu Pojazd.
 * @param nrRej Numer rejestracyjny pojazdu.
 * @param kosztAmortyzacji Jednostkowy koszt eksploatacji pojazdu.
 */
Pojazd::Pojazd(std::string nrRej, double kosztAmortyzacji)
    : numerRejestracyjny(nrRej), kosztAmortyzacji(kosztAmortyzacji) {}

/**
 * @brief Weryfikuje dostępność pojazdu w zadanym przedziale czasowym.
 * * Metoda iteruje po liście zajętych terminów i sprawdza, czy nowy termin
 * nie koliduje z żadną istniejącą rezerwacją.
 * @param t Termin podlegający sprawdzeniu.
 * @return true jeśli pojazd jest dostępny, false jeśli występuje konflikt terminów.
 */
bool Pojazd::czyDostepny(const Termin& t) const {
    for (const auto& zajety : zajeteTerminy) {
        if (zajety.czyKoliduje(t)) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Rezerwuje pojazd w określonym terminie.
 * * Dodaje nowy termin do listy zajętości pojazdu.
 * @param t Termin do zarezerwowania.
 */
void Pojazd::zarezerwujTermin(const Termin& t) {
    zajeteTerminy.push_back(t);
}
