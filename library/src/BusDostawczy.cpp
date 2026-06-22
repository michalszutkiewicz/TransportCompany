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
 * @brief Weryfikuje, czy bus dostawczy może wykonać dane zlecenie.
 * * Metoda bezpośrednio odpytuje przekazany obiekt zlecenia o jego specyficzne wymagania.
 * Weryfikacja opiera się na sprawdzeniu, czy wymagana objętość ładunku mieści się
 * w przestrzeni ładunkowej busa (pomijając kryterium wagi) oraz czy kategoria prawa jazdy
 * przypisana do zlecenia jest zgodna z kategorią pojazdu (B).
 * * @param z Stała referencja do obiektu zlecenia, stanowiącego źródło wymagań transportowych.
 * @return true jeśli pojazd spełnia wymagania objętościowe i uprawnień zlecenia, false w przeciwnym razie.
 */
bool BusDostawczy::czyMozeWykonacZlecenie(const Zlecenie& z) const {
    // Bus pyta obiekt zlecenia tylko o objętość
    bool odpowiedniaObjetosc = z.pobierzObjetosc() <= pojemnoscM3;
    bool odpowiedniaKategoria = z.pobierzWymaganaKategorie() == pobierzWymaganaKategorie();

    return odpowiedniaObjetosc && odpowiedniaKategoria;
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