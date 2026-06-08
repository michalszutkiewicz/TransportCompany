/**
* @file BusDostawczy.cpp
 * @brief Implementacja klasy BusDostawczy reprezentującej lekki pojazd transportowy.
 */
#include "../include/BusDostawczy.h"
#include "../include/Zlecenie.h"
#include <sstream>

/**
 * @brief Konstruktor obiektu BusDostawczy.
 * @param nrRej Numer rejestracyjny pojazdu.
 * @param kosztAmort Koszt amortyzacji jednostkowej.
 * @param pojemnoscM3 Pojemność przestrzeni ładunkowej w metrach sześciennych.
 */
BusDostawczy::BusDostawczy(std::string nrRej, double kosztAmort, double pojemnoscM3)
    : Pojazd(nrRej, kosztAmort), pojemnoscM3(pojemnoscM3) {}

/**
 * @brief Weryfikuje, czy bus może wykonać zlecenie.
 * * Sprawdza ładowność (objętość) oraz zgodność kategorii uprawnień z wymaganiami zlecenia.
 * @param z Referencja do zlecenia.
 * @return true jeśli pojazd spełnia wymagania zlecenia, false w przeciwnym razie.
 */
bool BusDostawczy::czyMozeWykonacZlecenie(const Zlecenie& z) const {
    return sprawdzLadownosc(z.pobierzWymaganaWage(), z.pobierzObjetosc()) &&
           z.pobierzWymaganaKategorie() == pobierzWymaganaKategorie();
}

/**
 * @brief Sprawdza, czy ładunek mieści się w pojemności busa.
 * @param wymaganaWaga Masa ładunku (w przypadku busa kluczowa jest objętość).
 * @param objetosc Objętość ładunku.
 * @return true jeśli objętość jest mniejsza lub równa dostępnej pojemności, false w przeciwnym razie.
 */
bool BusDostawczy::sprawdzLadownosc(double wymaganaWaga, double objetosc) const {
    return objetosc <= pojemnoscM3;
}

/**
 * @brief Pobiera sformatowany opis techniczny busa.
 * @return Ciąg znaków zawierający szczegóły pojazdu.
 */
std::string BusDostawczy::pobierzOpisPojazdu() const {
    std::ostringstream oss;
    oss << "[BUS DOSTAWCZY] Nr rej: " << pobierzNrRejestracyjny()
        << " | Koszt amortyzacji: " << pobierzKosztAmortyzacji() << " PLN/km"
        << " | Pojemność: " << pojemnoscM3 << " m3";
    return oss.str();
}

/**
 * @brief Serializuje dane busa do formatu tekstowego dla potrzeb zapisu.
 * @return Ciąg znaków w formacie "BUS;nrRej;koszt;pojemnosc".
 */
std::string BusDostawczy::serializuj() const {
    std::ostringstream oss;
    oss << "BUS;"
        << pobierzNrRejestracyjny() << ";"
        << pobierzKosztAmortyzacji() << ";"
        << pojemnoscM3;
    return oss.str();
}