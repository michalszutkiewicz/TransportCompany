#ifndef ATOM_PN_1330_06_KLIENT_H
#define ATOM_PN_1330_06_KLIENT_H

#pragma once
#include <string>
#include <vector>
#include <memory>

/**
 * @class Klient
 * @brief Klasa reprezentująca zleceniodawcę w systemie transportowym.
 * * Przechowuje podstawowe dane identyfikacyjne klienta niezbędne do procesowania
 * zleceń i generowania dokumentacji przewozowej.
 * @author Michał Szutkiewicz
 * @version 1.0
 */
class Klient {
private:
    std::string idKlienta; ///< Unikalny identyfikator klienta w systemie.
    std::string imie;      ///< Imię klienta.
    std::string nazwisko;  ///< Nazwisko klienta.

public:
    /**
     * @brief Konstruktor obiektu Klient.
     * @param id Unikalny identyfikator.
     * @param imie Imię klienta.
     * @param nazwisko Nazwisko klienta.
     */
    Klient(std::string id, std::string imie, std::string nazwisko);

    /**
     * @brief Wirtualny destruktor zapewniający poprawne zarządzanie zasobami.
     */
    virtual ~Klient() = default;

    /**
     * @brief Pobiera identyfikator klienta.
     * @return Identyfikator klienta.
     */
    std::string pobierzId() const { return idKlienta; }

    /**
     * @brief Pobiera imię klienta.
     * @return Imię klienta.
     */
    std::string pobierzImie() const { return imie; }

    /**
     * @brief Pobiera nazwisko klienta.
     * @return Nazwisko klienta.
     */
    std::string pobierzNazwisko() const { return nazwisko; }

    /**
     * @brief Zwraca pełne dane personalne klienta w formie tekstowej.
     * @return Sformatowany ciąg znaków (Imię + Nazwisko + ID).
     */
    std::string pobierzPelneDane() const;

    /**
     * @brief Serializuje dane klienta do formatu tekstowego.
     * @return Zserializowane dane klienta.
     */
    virtual std::string serializuj() const;
};

#endif //ATOM_PN_1330_06_KLIENT_H