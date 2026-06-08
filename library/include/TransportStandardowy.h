/**
* @file TransportStandardowy.h
 * @brief Definicja klasy TransportStandardowy rozszerzającej bazową klasę Usluga.
 */

#ifndef ATOM_PN_1330_06_TRANSPORTSTANDARDOWY_H
#define ATOM_PN_1330_06_TRANSPORTSTANDARDOWY_H
#pragma once
#include "Usluga.h"

/**
 * @class TransportStandardowy
 * @brief Klasa reprezentująca usługę transportu w trybie standardowym.
 * * Implementuje podstawowy algorytm wyceny usługi, który opiera się
 * na iloczynie pokonanego dystansu oraz przypisanej stawki jednostkowej (za kilometr).
 */
class TransportStandardowy : public Usluga {
private:
    double stawkaZaKm; ///< Stawka kosztu za jednostkę dystansu w trybie standardowym.

public:
    /**
     * @brief Konstruktor obiektu TransportStandardowy.
     * @param nazwa Nazwa usługi.
     * @param dystans Dystans do pokonania w ramach usługi.
     * @param stawka Stawka za kilometr.
     */
    TransportStandardowy(std::string nazwa, double dystans, double stawka);

    /**
     * @brief Oblicza całkowity koszt usługi.
     * * Koszt wyliczany jest poprzez pomnożenie dystansu przez stawkę za kilometr.
     * @return Całkowity koszt usługi jako wartość typu double.
     */
    double obliczKoszt() const override;

    /**
     * @brief Pobiera opisowe szczegóły usługi.
     * @return Sformatowany ciąg znaków z informacjami o usłudze.
     */
    std::string pobierzSzczegoly() const override;
};

#endif //ATOM_PN_1330_06_TRANSPORTSTANDARDOWY_H