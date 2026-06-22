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
 * @brief Weryfikuje, czy ciężarówka może wykonać dane zlecenie.
 * * Metoda bezpośrednio odpytuje przekazany obiekt zlecenia o jego specyficzne wymagania.
 * Weryfikacja opiera się na sprawdzeniu, czy wymagana masa ładunku (po konwersji
 * z kilogramów na tony) nie przekracza dopuszczalnej ładowności ciężarówki oraz
 * czy kategoria prawa jazdy przypisana do zlecenia jest zgodna z kategorią pojazdu (C).
 * * @param z Stała referencja do obiektu zlecenia, stanowiącego źródło wymagań transportowych.
 * @return true jeśli pojazd spełnia wymagania tonażowe i uprawnień zlecenia, false w przeciwnym razie.
 */
bool Ciezarowka::czyMozeWykonacZlecenie(const Zlecenie& z) const {
    // Ciężarówka pyta obiekt zlecenia tylko o wagę
    bool odpowiedniaWaga = (z.pobierzWymaganaWage() / 1000.0) <= maksLadownoscTony;
    bool odpowiedniaKategoria = z.pobierzWymaganaKategorie() == pobierzWymaganaKategorie();

    return odpowiedniaWaga && odpowiedniaKategoria;
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