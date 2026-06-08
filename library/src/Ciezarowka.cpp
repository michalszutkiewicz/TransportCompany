/**
* @file Ciezarowka.cpp
 * @brief Implementacja klasy Ciezarowka reprezentującej pojazd ciężarowy.
 */
#include "../include/Ciezarowka.h"
#include "../include/Zlecenie.h"
#include <sstream>

/**
 * @brief Konstruktor obiektu Ciezarowka.
 * @param nrRej Numer rejestracyjny pojazdu.
 * @param kosztAmort Koszt amortyzacji jednostkowej.
 * @param maksLadownosc Maksymalna ładowność w tonach.
 * @param wymagaNaczepy Flaga określająca wymóg posiadania naczepy (true/false).
 */
Ciezarowka::Ciezarowka(std::string nrRej, double kosztAmort, double maksLadownosc, bool wymagaNaczepy)
    : Pojazd(nrRej, kosztAmort), maksLadownoscTony(maksLadownosc), wymagaNaczepy(wymagaNaczepy) {}

/**
 * @brief Weryfikuje, czy ciężarówka może wykonać zlecenie.
 * * Sprawdza ładowność (masę) oraz zgodność kategorii uprawnień z wymaganiami zlecenia.
 * @param z Referencja do zlecenia.
 * @return true jeśli pojazd spełnia wymagania zlecenia, false w przeciwnym razie.
 */
bool Ciezarowka::czyMozeWykonacZlecenie(const Zlecenie& z) const {
    return sprawdzLadownosc(z.pobierzWymaganaWage(), z.pobierzObjetosc()) &&
           z.pobierzWymaganaKategorie() == pobierzWymaganaKategorie();
}

/**
 * @brief Sprawdza, czy ładunek mieści się w limicie wagowym ciężarówki.
 * * Metoda dokonuje konwersji masy z kilogramów (zlecenia) na tony (pojazdu).
 * @param wymaganaWaga Masa ładunku w kilogramach.
 * @param objetosc Objętość ładunku (pomijana w logice dla ciężarówki).
 * @return true jeśli masa w tonach jest mniejsza lub równa maksymalnej ładowności, false w przeciwnym razie.
 */
bool Ciezarowka::sprawdzLadownosc(double wymaganaWaga, double objetosc) const {
    return (wymaganaWaga / 1000.0) <= maksLadownoscTony;
}

/**
 * @brief Pobiera sformatowany opis techniczny ciężarówki.
 * @return Ciąg znaków zawierający szczegóły pojazdu (w tym informację o naczepie).
 */
std::string Ciezarowka::pobierzOpisPojazdu() const {
    std::ostringstream oss;
    oss << "[CIEŻARÓWKA] Nr rej: " << pobierzNrRejestracyjny()
        << " | Koszt amortyzacji: " << pobierzKosztAmortyzacji() << " PLN/km"
        << " | Ładowność: " << maksLadownoscTony << "t"
        << " | Naczepa: " << (wymagaNaczepy ? "TAK" : "NIE");
    return oss.str();
}

/**
 * @brief Serializuje dane ciężarówki do formatu tekstowego dla potrzeb zapisu.
 * @return Ciąg znaków w formacie "CIEZAROWKA;nrRej;koszt;ladownosc;czyNaczepa".
 */
std::string Ciezarowka::serializuj() const {
    std::ostringstream oss;
    oss << "CIEZAROWKA;"
        << pobierzNrRejestracyjny() << ";"
        << pobierzKosztAmortyzacji() << ";"
        << maksLadownoscTony << ";"
        << (wymagaNaczepy ? "1" : "0");
    return oss.str();
}