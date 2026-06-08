/**
* @file TransportEkspresowy.cpp
 * @brief Implementacja klasy TransportEkspresowy obsługującej priorytetowe zlecenia.
 */

#include "../include/TransportEkspresowy.h"
#include <sstream>

/**
 * @brief Konstruktor obiektu TransportEkspresowy.
 * @param nazwa Nazwa zlecenia.
 * @param dystans Dystans do pokonania w kilometrach.
 * @param stawka Stawka jednostkowa za kilometr w trybie ekspresowym.
 * @param extra Dodatkowa opłata stała za realizację ekspresową.
 */
TransportEkspresowy::TransportEkspresowy(std::string nazwa, double dystans, double stawka, double extra)
    : Usluga(nazwa, dystans), stawkaEkspresowa(stawka), oplataStala(extra) {}

/**
 * @brief Oblicza całkowity koszt usługi ekspresowej.
 * * Koszt jest sumą iloczynu dystansu i stawki jednostkowej oraz stałej opłaty za priorytet.
 * @return Całkowity koszt usługi (double).
 */
double TransportEkspresowy::obliczKoszt() const {
    //koszt jest wyższy o oplate stałą za priorytet wiec musimy dodac
    return (dystans * stawkaEkspresowa) + oplataStala;
}

/**
 * @brief Pobiera szczegółowe informacje o usłudze ekspresowej.
 * @return Sformatowany ciąg znaków z danymi o typie, dystansie i dopłacie.
 */
std::string TransportEkspresowy::pobierzSzczegoly() const {
    std::stringstream ss;
    ss << "Typ: EKSPRESOWY | Dystans: " << dystans << " km | Dopłata stała: " << oplataStala << " PLN";
    return ss.str();
}