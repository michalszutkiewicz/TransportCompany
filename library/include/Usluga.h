/**
* @file Usluga.h
 * @brief Definicja klasy bazowej Usluga dla systemu zarządzania transportem.
 */

#ifndef ATOM_PN_1330_06_USLUGA_H
#define ATOM_PN_1330_06_USLUGA_H

#pragma once
#include <string>

/**
 * @class Usluga
 * @brief Klasa abstrakcyjna definiująca ogólny interfejs usługi transportowej.
 * * Służy jako fundament dla różnych typów usług (np. standardowej, ekspresowej).
 * Przechowuje podstawowe dane o zleceniu oraz wymusza implementację logiki
 * wyceny i prezentacji szczegółów w klasach pochodnych.
 */
class Usluga {
protected:
    std::string nazwaZlecenia; ///< Nazwa lub identyfikator zlecenia.
    double dystans;            ///< Dystans do pokonania wyrażony w kilometrach.

public:
    /**
     * @brief Konstruktor obiektu Usluga.
     * @param nazwa Nazwa zlecenia.
     * @param dystans Dystans usługi (km).
     */
    Usluga(std::string nazwa, double dystans);

    /**
     * @brief Wirtualny destruktor domyślny.
     */
    virtual ~Usluga() = default;

    /**
     * @brief Czysto wirtualna metoda obliczająca koszt usługi.
     * * Każda usługa musi zaimplementować własny algorytm wyceny.
     * @return Obliczony koszt usługi typu double.
     */
    virtual double obliczKoszt() const = 0;

    /**
     * @brief Czysto wirtualna metoda pobierająca szczegóły usługi.
     * @return Ciąg znaków opisujący parametry usługi.
     */
    virtual std::string pobierzSzczegoly() const = 0;

    /**
     * @brief Pobiera nazwę zlecenia.
     * @return Nazwa zlecenia.
     */
    std::string pobierzNazwe() const;
};

#endif //ATOM_PN_1330_06_USLUGA_H