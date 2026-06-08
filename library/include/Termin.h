/**
* @file Termin.h
 * @brief Definicja klasy Termin reprezentującej przedział czasowy.
 */

#ifndef POBI_TERMIN_H
#define POBI_TERMIN_H

#pragma once
#include <boost/date_time/posix_time/posix_time.hpp>

namespace pt = boost::posix_time;
namespace gr = boost::gregorian;

/**
 * @class Termin
 * @brief Klasa reprezentująca przedział czasowy (od-do) w systemie.
 * * Odpowiada za przechowywanie dat i godzin rozpoczęcia oraz zakończenia
 * danego zdarzenia (np. rezerwacji pojazdu lub pracy pracownika).
 * Umożliwia weryfikację konfliktów czasowych pomiędzy różnymi terminami.
 */
class Termin {
private:
    pt::ptime dataOd; ///< Data i czas rozpoczęcia terminu.
    pt::ptime dataDo; ///< Data i czas zakończenia terminu.

public:
    /**
     * @brief Konstruktor obiektu Termin.
     * @param dataOd Czas rozpoczęcia.
     * @param dataDo Czas zakończenia.
     */
    Termin(pt::ptime dataOd, pt::ptime dataDo);

    /**
     * @brief Sprawdza, czy bieżący termin koliduje z innym, podanym terminem.
     * * Logika kolizji uwzględnia przecięcia się przedziałów czasowych.
     * @param inny Referencja do terminu, z którym sprawdzamy kolizję.
     * @return true jeśli terminy nachodzą na siebie, false w przeciwnym razie.
     */
    bool czyKoliduje(const Termin &inny) const;

    /**
     * @brief Pobiera czas rozpoczęcia terminu.
     * @return Obiekt ptime reprezentujący początek.
     */
    pt::ptime pobierzCzasOd() const { return dataOd; }

    /**
     * @brief Pobiera czas zakończenia terminu.
     * @return Obiekt ptime reprezentujący koniec.
     */
    pt::ptime pobierzCzasDo() const { return dataDo; }

    /**
     * @brief Przygotowuje dane terminu do zapisu w formacie tekstowym.
     * @return Ciąg znaków z reprezentacją danych terminu.
     */
    std::string serializuj() const;
};

#endif //POBI_TERMIN_H