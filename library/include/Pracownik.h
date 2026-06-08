/**
 * @file Pracownik.h
 * @brief Definicja klasy bazowej Pracownik dla systemu zarządzania transportem.
 */

#ifndef ATOM_PN_1330_06_PRACOWNIK_H
#define ATOM_PN_1330_06_PRACOWNIK_H

#pragma once
#include <string>
#include <vector>
#include "Termin.h"

class Zlecenie;

/**
 * @class Pracownik
 * @brief Klasa abstrakcyjna reprezentująca zasób ludzki w przedsiębiorstwie.
 * * Odpowiada za zarządzanie czasem pracy pracownika (poprzez listę terminów)
 * oraz weryfikację kompetencji niezbędnych do obsługi różnych typów zleceń.
 * Jest klasą bazową dla wyspecjalizowanych ról (np. Kierowca, Magazynier).
 */
class Pracownik {
private:
    std::string idPracownika;     ///< Unikalny identyfikator pracownika (np. PESEL).
    std::string imieNazwisko;     ///< Imię i nazwisko pracownika.
    double stawkaGodzinowa;       ///< Stawka za godzinę pracy służąca do kalkulacji kosztów zlecenia.
    std::vector<Termin> zajeteTerminy; ///< Harmonogram pracownika określający dostępność.

public:
    /**
     * @brief Konstruktor obiektu Pracownik.
     * @param id Identyfikator pracownika.
     * @param imieNazwisko Pełne imię i nazwisko.
     * @param stawkaGodzinowa Stawka wynagrodzenia pracownika.
     */
    Pracownik(std::string id, std::string imieNazwisko, double stawkaGodzinowa);

    /**
     * @brief Wirtualny destruktor domyślny.
     */
    virtual ~Pracownik() = default;

    /**
     * @brief Sprawdza dostępność pracownika w określonym czasie.
     * @param t Termin podlegający weryfikacji.
     * @return true jeśli pracownik nie ma w tym czasie innych zadań, false w przeciwnym razie.
     */
    bool czyDostepny(const Termin& t) const;

    /**
     * @brief Przypisuje pracownika do realizacji zadania w podanym terminie.
     * @param t Termin do zarezerwowania w kalendarzu pracownika.
     */
    void zarezerwujTermin(const Termin& t);

    /**
     * @brief Weryfikuje, czy pracownik posiada umiejętności wymagane przez zlecenie.
     * @param z Zlecenie podlegające sprawdzeniu.
     * @return true jeśli pracownik jest kompetentny do wykonania zlecenia, false w przeciwnym razie.
     */
    virtual bool czyUmieWykonacZlecenie(const Zlecenie& z) const = 0;

    /**
     * @brief Sprawdza, czy pracownik posiada wymagane uprawnienia (np. kategorię prawa jazdy).
     * @param wymaganaKategoria Nazwa kategorii niezbędnej do wykonania zadania.
     * @return true jeśli pracownik posiada uprawnienia, false w przeciwnym razie.
     */
    virtual bool mozeWykonacPrace(std::string wymaganaKategoria) const = 0;

    /**
     * @brief Zwraca nazwę roli pełnionej przez pracownika (Kierowca).
     * @return Ciąg znaków określający rolę.
     */
    virtual std::string pobierzRole() const = 0;

    /**
     * @brief Pobiera identyfikator pracownika.
     * @return Identyfikator.
     */
    std::string pobierzIdPracownika() const { return idPracownika; }

    /**
     * @brief Alias metody pobierającej identyfikator (używany w warstwie repozytoriów).
     * @return Identyfikator pracownika (PESEL).
     */
    std::string pobierzPesel() const { return idPracownika; }

    /**
     * @brief Zwraca imię i nazwisko pracownika.
     * @return Imię i nazwisko.
     */
    std::string pobierzImieNazwisko() const { return imieNazwisko; }

    /**
     * @brief Zwraca stawkę godzinową pracownika.
     * @return Stawka godzinowa.
     */
    double pobierzStawke() const { return stawkaGodzinowa; }

    /**
     * @brief Pobiera kompletne dane pracownika w celach prezentacyjnych.
     * @return Ciąg znaków zawierający informacje o pracowniku.
     */
    virtual std::string pobierzPelneDane() const = 0;

    /**
     * @brief Przygotowuje dane pracownika do zapisu w formacie trwałym.
     * @return Ciąg znaków z serializowanymi danymi.
     */
    virtual std::string serializuj() const = 0;
};

#endif //ATOM_PN_1330_06_PRACOWNIK_H