/**
 * @file Zlecenie.h
 * @brief Definicja klasy Zlecenie agregującej proces transportowy.
 * @author Kinga Ratajska
 * @date 2026-04-15
 */

#ifndef ATOM_PN_1330_06_ZLECENIE_H
#define ATOM_PN_1330_06_ZLECENIE_H

#pragma once
#include <memory>
#include <vector>
#include <string>
#include "Termin.h"

// Forward declarations
class Klient;
class Usluga;
class Pojazd;
class Pracownik;

/**
 * @class Zlecenie
 * @brief Klasa zarządzająca pełnym cyklem życia zlecenia transportowego.
 * * Zlecenie łączy klienta z wybraną usługą oraz zarządza przydziałem
 * niezbędnych zasobów (pojazdów i pracowników). Odpowiada za weryfikację
 * parametrów ładunkowych oraz rozliczanie kosztów końcowych.
 */
class Zlecenie {
private:
    std::string idZlecenia;      ///< Unikalny identyfikator zlecenia.
    Termin okresRealizacji;     ///< Planowany termin wykonania zlecenia.
    bool czyRozliczone;         ///< Status finansowy zlecenia.

    double wymaganaWaga;        ///< Masa ładunku określona w zleceniu.
    double objetosc;            ///< Objętość ładunku.
    std::string wymaganaKategoria; ///< Wymagana kategoria uprawnień do realizacji.

    std::shared_ptr<Klient> klient; ///< Wskaźnik na klienta zlecającego transport.
    std::shared_ptr<Usluga> usluga; ///< Wskaźnik na typ usługi (np. standardowa, ekspresowa).
    std::vector<std::shared_ptr<Pojazd>> przypisanePojazdy;    ///< Lista pojazdów przypisanych do zadania.
    std::vector<std::shared_ptr<Pracownik>> przypisaniPracownicy; ///< Lista pracowników delegowanych do zadania.

public:
    /**
     * @brief Konstruktor obiektu Zlecenie.
     * @param id Identyfikator zlecenia.
     * @param okres Termin realizacji.
     * @param k Wskaźnik na klienta.
     * @param u Wskaźnik na usługę.
     * @param waga Wymagana masa ładunku.
     * @param obj Objętość ładunku.
     * @param kat Wymagana kategoria uprawnień.
     */
    Zlecenie(std::string id, Termin okres, std::shared_ptr<Klient> k, std::shared_ptr<Usluga> u, double waga, double obj, std::string kat);

    /**
     * @brief Dodaje pojazd do zlecenia.
     * @param p Wskaźnik na pojazd.
     */
    void dodajPojazd(std::shared_ptr<Pojazd> p);

    /**
     * @brief Dodaje pracownika do realizacji zlecenia.
     * @param pr Wskaźnik na pracownika.
     */
    void dodajPracownika(std::shared_ptr<Pracownik> pr);

    /**
     * @brief Oblicza całkowity koszt zlecenia.
     * * Sumuje koszty usługi oraz koszty pracy i amortyzacji zasobów.
     * @return Sumaryczny koszt zlecenia.
     */
    double obliczPelnyKoszt() const;

    /**
     * @brief Zmienia status zlecenia na rozliczone.
     */
    void rozlicz();

    /**
     * @brief Zwraca okres realizacji.
     * @return Obiekt klasy Termin.
     */
    Termin pobierzOkres() const;

    /**
     * @brief Pobiera identyfikator zlecenia.
     * @return Identyfikator w postaci string.
     */
    std::string pobierzId() const { return idZlecenia; }

    /**
     * @brief Sprawdza, czy zlecenie zostało rozliczone.
     * @return true jeśli rozliczono, false w przeciwnym razie.
     */
    bool czyJestRozliczone() const { return czyRozliczone; }

    /**
     * @brief Zwraca wskaźnik na klienta.
     * @return Shared pointer do klienta.
     */
    std::shared_ptr<Klient> pobierzKlienta() const { return klient; }

    /**
     * @brief Pobiera listę przypisanych pojazdów.
     * @return Referencja do wektora wskaźników na pojazdy.
     */
    const std::vector<std::shared_ptr<Pojazd>>& pobierzPojazdy() const { return przypisanePojazdy; }

    /**
     * @brief Pobiera listę przypisanych pracowników.
     * @return Referencja do wektora wskaźników na pracowników.
     */
    const std::vector<std::shared_ptr<Pracownik>>& pobierzPracownicy() const { return przypisaniPracownicy; }

    /**
     * @brief Pobiera wymaganą wagę ładunku.
     */
    double pobierzWymaganaWage() const { return wymaganaWaga; }

    /**
     * @brief Pobiera wymaganą objętość ładunku.
     */
    double pobierzObjetosc() const { return objetosc; }

    /**
     * @brief Pobiera wymaganą kategorię uprawnień.
     */
    std::string pobierzWymaganaKategorie() const { return wymaganaKategoria; }

    /**
     * @brief Zwraca aktualny status zlecenia (np. "oczekujące", "zrealizowane").
     */
    std::string pobierzStatus() const;

    /**
     * @brief Generuje krótkie podsumowanie zlecenia.
     * @return Tekstowe podsumowanie.
     */
    std::string pobierzPodsumowanie() const;

    /**
     * @brief Serializuje obiekt zlecenia do formatu zapisu.
     * @return Ciąg znaków reprezentujący stan zlecenia.
     */
    std::string serializuj() const;
};

#endif //ATOM_PN_1330_06_ZLECENIE_H