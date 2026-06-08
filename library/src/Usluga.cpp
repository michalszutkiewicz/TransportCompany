/**
* @file Usluga.cpp
 * @brief Implementacja bazowej klasy Usluga dla systemu zarządzania transportem.
 */

#include "../include/Usluga.h"

/**
 * @brief Konstruktor obiektu Usluga.
 * @param nazwa Nazwa zlecenia.
 * @param dystans Dystans do pokonania w ramach usługi (w kilometrach).
 */
Usluga::Usluga(std::string nazwa, double dystans)
    : nazwaZlecenia(nazwa), dystans(dystans) {}

/**
 * @brief Pobiera nazwę zlecenia przypisaną do usługi.
 * @return Nazwa zlecenia w postaci ciągu znaków.
 */
std::string Usluga::pobierzNazwe() const {
    return nazwaZlecenia;
}