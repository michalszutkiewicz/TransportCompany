/**
* @file Termin.cpp
 * @brief Implementacja klasy Termin do obsługi przedziałów czasowych.
 */

#include "../include/Termin.h"
#include <stdexcept>

/**
 * @brief Konstruktor obiektu Termin.
 * * Weryfikuje spójność przedziału czasowego.
 * @param dataOd Czas rozpoczęcia terminu.
 * @param dataDo Czas zakończenia terminu.
 * @throw std::invalid_argument Jeśli dataOd jest późniejsza niż dataDo.
 */
Termin::Termin(pt::ptime dataOd, pt::ptime dataDo) : dataOd(dataOd), dataDo(dataDo) {
    // data początkowa nie może być późniejsza niż data końcowa.
    if (this->dataOd > this->dataDo) {
        throw std::invalid_argument("Data poczatkowa nie moze byc pozniejsza niz data koncowa!");
    }
}

/**
 * @brief Sprawdza, czy bieżący termin koliduje z innym terminem.
 * * Wykorzystuje warunek przecięcia przedziałów: (start1 < end2) && (end1 > start2).
 * @param inny Termin, z którym sprawdzamy kolizję.
 * @return true jeśli terminy nachodzą na siebie, false w przeciwnym razie.
 */
bool Termin::czyKoliduje(const Termin &inny) const {
    return (this->dataOd < inny.dataDo) && (this->dataDo > inny.dataOd);
}

/**
 * @brief Serializuje termin do formatu tekstowego (ISO extended).
 * @return Ciąg znaków w formacie "ISO_OD;ISO_DO".
 */
std::string Termin::serializuj() const {
    return boost::posix_time::to_iso_extended_string(dataOd) + ";" +
           boost::posix_time::to_iso_extended_string(dataDo);
}