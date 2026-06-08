//
// Created by MichalSw11 on 05.06.2026.
//

#ifndef ATOM_PN_1330_06_ISERIALIZOWANY_H
#define ATOM_PN_1330_06_ISERIALIZOWANY_H

#pragma once
#include <string>

/**
 * @class ISerializowalny
 * @brief Abstrakcyjny interfejs definiujący kontrakt dla obiektów obsługujących serializację.
 * * Interfejs wymusza implementację metod niezbędnych do zapisu, odczytu oraz
 * konwersji stanu obiektów na format szeregowy (np. w celu zapisu do bazy lub pliku).
 * @author Michał Szutkiewicz
 * @version 1.0
 */
class ISerializowalny {
public:
    /**
     * @brief Wirtualny destruktor zapewniający poprawne usuwanie obiektów pochodnych.
     */
    virtual ~ISerializowalny() = default;

    /**
     * @brief Zapisuje aktualny stan obiektu do wskazanego pliku.
     * @param sciezka Ścieżka do pliku docelowego.
     */
    virtual void zapiszStan(const std::string& sciezka) const = 0;

    /**
     * @brief Wczytuje stan obiektu z pliku zewnętrznego.
     * @param sciezka Ścieżka do pliku źródłowego.
     */
    virtual void wczytajStan(const std::string& sciezka) = 0;

    /**
     * @brief Konwertuje wewnętrzny stan obiektu do formatu szeregowego.
     * @return Ciąg znaków reprezentujący zserializowane dane obiektu.
     */
    virtual std::string serializuj() const = 0;

    /**
     * @brief Przywraca stan obiektu na podstawie podanych danych szeregowych.
     * @param dane Ciąg znaków z danymi do deserializacji.
     */
    virtual void deserializuj(const std::string& dane) = 0;
};

#endif //ATOM_PN_1330_06_ISERIALIZOWANY_H
