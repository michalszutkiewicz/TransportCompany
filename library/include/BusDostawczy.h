#ifndef ATOM_PN_1330_06_BUSDOSTAWCZY_H
#define ATOM_PN_1330_06_BUSDOSTAWCZY_H

#pragma once
#include "Pojazd.h"

/**
 * @class BusDostawczy
 * @brief Klasa reprezentująca pojazd dostawczy typu "bus" w systemie transportowym.
 * * Dziedziczy po klasie bazowej Pojazd. Odpowiada za weryfikację możliwości realizacji zleceń
 * w oparciu o specyficzne parametry ładowności oraz objętości przestrzeni ładunkowej.
 * @author Michał Szutkiewicz
 * @version 1.0
 */
class BusDostawczy : public Pojazd {
private:
    double pojemnoscM3; ///< Objętość przestrzeni ładunkowej wyrażona w metrach sześciennych.

public:
    /**
     * @brief Konstruktor obiektu BusDostawczy.
     * @param nrRej Numer rejestracyjny pojazdu.
     * @param kosztAmortyzacji Stały koszt amortyzacji przypisany do pojazdu.
     * @param pojemnoscM3 Maksymalna objętość ładunku możliwa do przewiezienia.
     */
    BusDostawczy(std::string nrRej, double kosztAmortyzacji, double pojemnoscM3);

    /**
     * @brief Sprawdza, czy bus jest w stanie wykonać dane zlecenie.
     * * Weryfikacja obejmuje kompatybilność wymagań zlecenia z parametrami technicznymi busa.
     * @param z Stała referencja do zlecenia.
     * @return true jeśli pojazd spełnia wymagania zlecenia, false w przeciwnym razie.
     */
    bool czyMozeWykonacZlecenie(const Zlecenie& z) const override;

    /**
     * @brief Weryfikuje czy ładunek mieści się w limitach wagowych i objętościowych pojazdu.
     * @param wymaganaWaga Waga ładunku w kg.
     * @param objetosc Objętość ładunku w m3.
     * @return true jeśli ładunek jest możliwy do przewiezienia, false jeśli przekracza limity.
     */
    bool sprawdzLadownosc(double wymaganaWaga, double objetosc) const override;

    /**
     * @brief Zwraca kategorię prawa jazdy wymaganą do prowadzenia tego pojazdu.
     * @return Stała wartość "B" dla tej klasy pojazdów.
     */
    std::string pobierzWymaganaKategorie() const override { return "B"; }

    /**
     * @brief Generuje pełny opis techniczny pojazdu.
     * @return Sformatowany ciąg znaków z danymi pojazdu.
     */
    std::string pobierzOpisPojazdu() const override;

    /**
     * @brief Serializuje stan obiektu do formatu tekstowego.
     * @return Zserializowane dane obiektu (w tym pojemność ładunkową).
     */
    std::string serializuj() const override;
};

#endif //ATOM_PN_1330_06_BUSDOSTAWCZY_H