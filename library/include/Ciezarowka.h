#ifndef ATOM_PN_1330_06_CIEZAROWKA_H
#define ATOM_PN_1330_06_CIEZAROWKA_H

#pragma once
#include "Pojazd.h"

/**
 * @class Ciezarowka
 * @brief Klasa reprezentująca pojazd ciężarowy w systemie transportowym.
 * * Rozszerza klasę bazową Pojazd o obsługę parametrów tonażowych oraz
 * wymogów technicznych dotyczących naczep.
 * @author Michał Szutkiewicz
 * @version 1.0
 */
class Ciezarowka : public Pojazd {
private:
    double maksLadownoscTony; ///< Maksymalna dopuszczalna masa ładunku w tonach.
    bool wymagaNaczepy;      ///< Flaga określająca czy pojazd wymaga podpięcia naczepy do operacji.

public:
    /**
     * @brief Konstruktor obiektu Ciezarowka.
     * @param nrRej Numer rejestracyjny pojazdu.
     * @param kosztAmortyzacji Stały koszt amortyzacji przypisany do pojazdu.
     * @param maksLadownosc Maksymalna masa ładunku w tonach.
     * @param wymagaNaczepy Wartość logiczna określająca wymóg posiadania naczepy.
     */
    Ciezarowka(std::string nrRej, double kosztAmortyzacji, double maksLadownosc, bool wymagaNaczepy);

    /**
     * @brief Sprawdza, czy ciężarówka spełnia wymogi techniczne zlecenia.
     * * Weryfikuje wymogi tonażowe oraz kwestię podpięcia naczepy.
     * @param z Stała referencja do zlecenia.
     * @return true jeśli pojazd jest kompatybilny, false w przypadku braku spełnienia wymogów.
     */
    bool czyMozeWykonacZlecenie(const Zlecenie& z) const override;

    /**
     * @brief Zwraca kategorię prawa jazdy wymaganą do obsługi pojazdu ciężarowego.
     * @return Stała wartość "C" dla tej klasy pojazdów.
     */
    std::string pobierzWymaganaKategorie() const override { return "C"; }

    /**
     * @brief Generuje szczegółowy opis techniczny ciężarówki.
     * @return Sformatowany ciąg znaków z danymi pojazdu.
     */
    std::string pobierzOpisPojazdu() const override;

    /**
     * @brief Serializuje stan obiektu do formatu tekstowego na potrzeby zapisu w repozytorium.
     * @return Zserializowane dane obiektu wraz z parametrami tonażowymi.
     */
    std::string serializuj() const override;
};

#endif //ATOM_PN_1330_06_CIEZAROWKA_H