/**
* @file TransportStandardowy.cpp
 * @brief Implementacja klasy TransportStandardowy obsługującej standardowe zlecenia transportowe.
 */

#include "../include/TransportStandardowy.h"
#include <iomanip>
#include <sstream>

/**
 * @brief Konstruktor obiektu TransportStandardowy.
 * @param nazwa Nazwa zlecenia.
 * @param dystans Całkowity dystans do pokonania w kilometrach.
 * @param stawka Stawka za jeden kilometr trasy.
 */
TransportStandardowy::TransportStandardowy(std::string nazwa, double dystans, double stawka)
    : Usluga(nazwa, dystans), stawkaZaKm(stawka) {}

/**
 * @brief Oblicza całkowity koszt usługi standardowej.
 * * Koszt jest iloczynem dystansu oraz stawki za kilometr.
 * @return Całkowity koszt usługi (double).
 */
double TransportStandardowy::obliczKoszt() const {
    return dystans * stawkaZaKm;
}

/**
 * @brief Pobiera szczegółowe informacje o usłudze standardowej.
 * * Zwraca sformatowany ciąg znaków zawierający typ usługi, pokonany dystans
 * oraz stawkę jednostkową.
 * @return Sformatowany opis usługi w postaci tekstowej.
 */
std::string TransportStandardowy::pobierzSzczegoly() const {
    std::stringstream ss;
    ss << "Typ: Standardowy | Dystans: " << dystans << " km | Stawka: " << stawkaZaKm << " PLN/km";
    return ss.str();
}