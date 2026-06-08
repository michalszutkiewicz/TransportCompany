/**
* @file Zlecenie.cpp
 * @brief Implementacja klasy Zlecenie agregującej dane o usłudze, zasobach i kliencie.
 */

#include "../include/Zlecenie.h"
#include "../include/Klient.h"
#include "../include/Usluga.h"
#include "../include/Pojazd.h"
#include "../include/Pracownik.h"
#include <sstream>

/**
 * @brief Konstruktor obiektu Zlecenie.
 * @param id Identyfikator zlecenia.
 * @param okres Termin realizacji zlecenia.
 * @param k Shared pointer do klienta.
 * @param u Shared pointer do usługi.
 * @param waga Wymagana waga ładunku.
 * @param obj Objętość ładunku.
 * @param kat Wymagana kategoria pojazdu/pracownika.
 */
Zlecenie::Zlecenie(std::string id, Termin okres, std::shared_ptr<Klient> k, std::shared_ptr<Usluga> u, double waga, double obj, std::string kat)
    : idZlecenia(id), okresRealizacji(okres), klient(k), usluga(u), czyRozliczone(false), wymaganaWaga(waga), objetosc(obj), wymaganaKategoria(kat) {}

/**
 * @brief Dodaje pojazd do zlecenia i rezerwuje dla niego termin.
 * @param p Shared pointer do pojazdu.
 */
void Zlecenie::dodajPojazd(std::shared_ptr<Pojazd> p) {
    if (p) {
        przypisanePojazdy.push_back(p);
        p->zarezerwujTermin(okresRealizacji);
    }
}

/**
 * @brief Dodaje pracownika do zlecenia i rezerwuje dla niego termin.
 * @param pr Shared pointer do pracownika.
 */
void Zlecenie::dodajPracownika(std::shared_ptr<Pracownik> pr) {
    if (pr) {
        przypisaniPracownicy.push_back(pr);
        pr->zarezerwujTermin(okresRealizacji);
    }
}

/**
 * @brief Oblicza koszt całkowity zlecenia na podstawie przypisanej usługi.
 * @return Koszt obliczony przez obiekt usługi lub 0.0, jeśli brak usługi.
 */
double Zlecenie::obliczPelnyKoszt() const {
    if (usluga) {
        return usluga->obliczKoszt();
    }
    return 0.0;
}

/**
 * @brief Oznacza zlecenie jako rozliczone finansowo.
 */
void Zlecenie::rozlicz() {
    czyRozliczone = true;
}

/**
 * @brief Zwraca okres realizacji zlecenia.
 * @return Obiekt klasy Termin.
 */
Termin Zlecenie::pobierzOkres() const {
    return okresRealizacji;
}

/**
 * @brief Wyznacza aktualny status zlecenia w oparciu o czas systemowy.
 * @return Status: "ROZLICZONE", "ZAKOŃCZONE", "OCZEKUJĄCE" lub "W TOKU".
 */
std::string Zlecenie::pobierzStatus() const {
    if (czyRozliczone) {
        return "ROZLICZONE";
    }

    boost::posix_time::ptime teraz = boost::posix_time::second_clock::local_time();

    if (teraz > okresRealizacji.pobierzCzasDo()) {
        return "ZAKOŃCZONE (oczekuje na rozliczenie)";
    } else if (teraz < okresRealizacji.pobierzCzasOd()) {
        return "OCZEKUJĄCE";
    } else {
        return "W TOKU";
    }
}

/**
 * @brief Generuje czytelne podsumowanie zlecenia dla użytkownika.
 * @return Sformatowany ciąg znaków z informacjami o zleceniu.
 */
std::string Zlecenie::pobierzPodsumowanie() const {
    // Implementacja generuje raport tekstowy z podziałem na status, klienta i przypisane zasoby
    std::ostringstream oss;
    oss << "[ZLECENIE " << idZlecenia << "] - Status: "
        << pobierzStatus() << "\n"
        << "  -> Klient: " << (klient ? klient->pobierzId() : "BRAK KLIENTA") << "\n"
        << "  -> Ładunek: " << wymaganaWaga << " kg, " << objetosc << " m3 (Wymagana kat: " << wymaganaKategoria << ")\n"
        << "  -> Termin Od: " << boost::posix_time::to_simple_string(okresRealizacji.pobierzCzasOd())
        << " Do: " << boost::posix_time::to_simple_string(okresRealizacji.pobierzCzasDo()) << "\n"
        << "  -> Przypisane Pojazdy (" << przypisanePojazdy.size() << "): ";

    for (const auto& pojazd : przypisanePojazdy) {
        if (pojazd) oss << pojazd->pobierzNumerRejestracyjny() << " ";
    }

    oss << "\n  -> Przypisani Pracownicy (" << przypisaniPracownicy.size() << "): ";
    for (const auto& pracownik : przypisaniPracownicy) {
        if (pracownik) oss << pracownik->pobierzIdPracownika() << " ";
    }
    oss << "\n------------------------------------------------";

    return oss.str();
}

/**
 * @brief Serializuje zlecenie do formatu zapisu (dane rozdzielone średnikami).
 * @return Ciąg znaków z danymi zlecenia.
 */
std::string Zlecenie::serializuj() const {
    std::ostringstream oss;

    oss << idZlecenia << ";"
        << czyRozliczone << ";"
        << wymaganaWaga << ";"
        << objetosc << ";"
        << wymaganaKategoria << ";"
        << okresRealizacji.serializuj() << ";";

    if (klient) {
        oss << klient->pobierzId() << ";";
    } else {
        oss << "BRAK;";
    }

    oss << przypisanePojazdy.size() << ";";
    for (const auto& pojazd : przypisanePojazdy) {
        if (pojazd) oss << pojazd->pobierzNumerRejestracyjny() << ",";
    }
    oss << ";";

    oss << przypisaniPracownicy.size() << ";";
    for (const auto& pracownik : przypisaniPracownicy) {
        if (pracownik) oss << pracownik->pobierzIdPracownika() << ",";
    }

    return oss.str();
}