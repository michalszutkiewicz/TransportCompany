/**
* @file TransportEkspresowy.h
 * @brief Definicja klasy TransportEkspresowy rozszerzającej bazową klasę Usluga.
 */

#ifndef ATOM_PN_1330_06_TRANSPORTEKSPRESOWY_H
#define ATOM_PN_1330_06_TRANSPORTEKSPRESOWY_H
#pragma once
#include "Usluga.h"

/**
 * @class TransportEkspresowy
 * @brief Klasa reprezentująca usługę transportu w trybie ekspresowym.
 * * Implementuje specyficzną logikę obliczania kosztu usługi, która uwzględnia
 * stawkę za kilometr oraz dodatkową opłatę stałą za priorytetowy charakter zlecenia.
 */
class TransportEkspresowy : public Usluga {
private:
    double stawkaEkspresowa; ///< Stawka za jednostkę dystansu w trybie ekspresowym.
    double oplataStala;      ///< Dodatkowa opłata stała za obsługę zlecenia w trybie przyspieszonym.

public:
    /**
     * @brief Konstruktor obiektu TransportEkspresowy.
     * @param nazwa Nazwa usługi.
     * @param dystans Dystans do pokonania.
     * @param stawka Stawka za kilometr w trybie ekspresowym.
     * @param extra Dodatkowa opłata stała za tryb ekspresowy.
     */
    TransportEkspresowy(std::string nazwa, double dystans, double stawka, double extra);

    /**
     * @brief Oblicza całkowity koszt usługi.
     * * Koszt obliczany jest jako suma iloczynu dystansu i stawki oraz opłaty stałej.
     * @return Całkowity koszt usługi jako wartość typu double.
     */
    double obliczKoszt() const override;

    /**
     * @brief Pobiera opisowe szczegóły usługi.
     * @return Sformatowany ciąg znaków zawierający informacje o usłudze.
     */
    std::string pobierzSzczegoly() const override;
};

#endif //ATOM_PN_1330_06_TRANSPORTEKSPRESOWY_H