/**
* @file Pracownik.cpp
 * @brief Implementacja bazowej klasy Pracownik zarządzającej harmonogramem pracy.
 */

#include "../include/Pracownik.h"

/**
 * @brief Konstruktor obiektu Pracownik.
 * @param id Unikalny identyfikator pracownika (np. PESEL).
 * @param imieNazwisko Pełne imię i nazwisko pracownika.
 * @param stawkaGodzinowa Wynagrodzenie za godzinę pracy.
 */
Pracownik::Pracownik(std::string id, std::string imieNazwisko, double stawkaGodzinowa)
    : idPracownika(id), imieNazwisko(imieNazwisko), stawkaGodzinowa(stawkaGodzinowa) {}

/**
 * @brief Weryfikuje dostępność pracownika w zadanym przedziale czasowym.
 * * Metoda sprawdza, czy nowy termin nie koliduje z żadnym już
 * zarezerwowanym w harmonogramie pracownika.
 * @param t Termin podlegający weryfikacji.
 * @return true jeśli pracownik jest dostępny w podanym terminie, false w przeciwnym razie.
 */
bool Pracownik::czyDostepny(const Termin& t) const {
    for (const auto& zajety : zajeteTerminy) {
        if (zajety.czyKoliduje(t)) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Rezerwuje czas pracy pracownika.
 * * Dodaje nowy termin do harmonogramu zajętości pracownika.
 * @param t Termin do zarezerwowania.
 */
void Pracownik::zarezerwujTermin(const Termin& t) {
    zajeteTerminy.push_back(t);
}
