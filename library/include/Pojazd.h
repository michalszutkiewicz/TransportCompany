/**
 * @file Pojazd.h
 * @brief Definicja klasy bazowej Pojazd dla systemu zarządzania transportem.
 */

#ifndef ATOM_PN_1330_06_POJAZD_H
#define ATOM_PN_1330_06_POJAZD_H

#pragma once
#include <string>
#include <vector>
#include "Termin.h"

class Zlecenie;

/**
 * @class Pojazd
 * @brief Klasa abstrakcyjna reprezentująca zasób transportowy w firmie.
 * * Odpowiada za zarządzanie dostępnością pojazdu w czasie oraz weryfikację 
 * parametrów technicznych niezbędnych do realizacji zleceń transportowych.
 * Służy jako klasa bazowa dla konkretnych typów pojazdów (np. ciężarówki, busy).
 */
class Pojazd  {
private:
    std::string numerRejestracyjny; ///< Unikalny identyfikator pojazdu w systemie.
    double kosztAmortyzacji;        ///< Koszt eksploatacji pojazdu (amortyzacja) doliczany do zlecenia.
    std::vector<Termin> zajeteTerminy; ///< Lista zarezerwowanych przedziałów czasowych pojazdu.

public:
    /**
     * @brief Konstruktor obiektu Pojazd.
     * @param nrRej Numer rejestracyjny pojazdu.
     * @param kosztAmortyzacji Koszt amortyzacji jednostkowej pojazdu.
     */
    Pojazd(std::string nrRej, double kosztAmortyzacji);

    /**
     * @brief Wirtualny destruktor domyślny.
     */
    virtual ~Pojazd() = default;

    /**
     * @brief Sprawdza, czy pojazd jest dostępny w podanym terminie.
     * @param t Termin, dla którego sprawdzana jest dostępność.
     * @return true jeśli termin nie koliduje z żadną rezerwacją, false w przeciwnym razie.
     */
    bool czyDostepny(const Termin& t) const;

    /**
     * @brief Rezerwuje pojazd w określonym terminie.
     * @param t Termin do zarezerwowania.
     * @throw Może zgłosić wyjątek, jeśli termin jest już zajęty lub nieprawidłowy.
     */
    void zarezerwujTermin(const Termin& t);

    /**
     * @brief Weryfikuje, czy pojazd spełnia wymagania specyficzne dla danego zlecenia.
     * @param z Referencja do zlecenia.
     * @return true jeśli pojazd może obsłużyć zlecenie, false w przeciwnym razie.
     */
    virtual bool czyMozeWykonacZlecenie(const Zlecenie& z) const = 0;

    /**
     * @brief Sprawdza, czy parametry ładunkowe zlecenia mieszczą się w limitach pojazdu.
     * @param wymaganaWaga Masa ładunku.
     * @param objetosc Objętość ładunku.
     * @return true jeśli ładunek może być bezpiecznie przewieziony, false w przeciwnym razie.
     */
    virtual bool sprawdzLadownosc(double wymaganaWaga, double objetosc) const = 0;

    /**
     * @brief Pobiera kategorię prawa jazdy wymaganą do prowadzenia pojazdu.
     * @return Ciąg znaków oznaczający kategorię (np. "C", "B").
     */
    virtual std::string pobierzWymaganaKategorie() const = 0;

    /**
     * @brief Zwraca szczegółowy opis techniczny pojazdu.
     * @return Opis tekstowy (np. marka, model, typ zabudowy).
     */
    virtual std::string pobierzOpisPojazdu() const = 0;

    /**
     * @brief Zwraca numer rejestracyjny pojazdu.
     * @return Numer rejestracyjny.
     */
    std::string pobierzNumerRejestracyjny() const { return numerRejestracyjny; }

    /**
     * @brief Alias metody pobierającej numer rejestracyjny (używany w warstwie repozytoriów).
     * @return Numer rejestracyjny.
     */
    std::string pobierzNrRejestracyjny() const { return numerRejestracyjny; }

    /**
     * @brief Pobiera przypisany koszt amortyzacji.
     * @return Koszt amortyzacji.
     */
    double pobierzKosztAmortyzacji() const { return kosztAmortyzacji; }

    /**
     * @brief Przygotowuje dane pojazdu do zapisu w formacie trwałym.
     * @return Ciąg znaków w formacie serializacji.
     */
    virtual std::string serializuj() const = 0;
};

#endif //ATOM_PN_1330_06_POJAZD_H