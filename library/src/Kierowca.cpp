/**
* @file Kierowca.cpp
 * @brief Implementacja klasy Kierowca reprezentującej pracownika z uprawnieniami do prowadzenia pojazdów.
 */
#include "../include/Kierowca.h"
#include "../include/Zlecenie.h"
#include <algorithm> // Wymagane dla std::find
#include <sstream>

/**
 * @brief Konstruktor obiektu Kierowca.
 * @param pesel Unikalny identyfikator (PESEL).
 * @param imieNazwisko Imię i nazwisko kierowcy.
 * @param stawkaGodzinowa Wynagrodzenie za godzinę pracy.
 * @param kategorie Wektor posiadanych kategorii prawa jazdy (np. "B", "C").
 */
Kierowca::Kierowca(std::string pesel, std::string imieNazwisko, double stawkaGodzinowa, std::vector<std::string> kategorie)
    : Pracownik(pesel, imieNazwisko, stawkaGodzinowa), kategoriePrawaJazdy(kategorie) {}

/**
 * @brief Weryfikuje, czy kierowca posiada kompetencje do wykonania zlecenia.
 * * Sprawdza, czy kategoria wymagana przez zlecenie znajduje się w zestawie kategorii kierowcy.
 * @param z Referencja do zlecenia.
 * @return true jeśli kierowca może obsłużyć zlecenie, false w przeciwnym razie.
 */
bool Kierowca::czyUmieWykonacZlecenie(const Zlecenie& z) const {
    return mozeWykonacPrace(z.pobierzWymaganaKategorie());
}

/**
 * @brief Sprawdza, czy kierowca posiada określoną kategorię prawa jazdy.
 * @param wymaganaKategoria Nazwa kategorii niezbędnej do pracy.
 * @return true jeśli kategoria znajduje się w posiadanych przez kierowcę, false w przeciwnym razie.
 */
bool Kierowca::mozeWykonacPrace(std::string wymaganaKategoria) const {
    // czy wymagana kategoria znajduje się w wektorze posiadanych kategorii
    return std::find(kategoriePrawaJazdy.begin(), kategoriePrawaJazdy.end(), wymaganaKategoria) != kategoriePrawaJazdy.end();
}

/**
 * @brief Zwraca rolę pracownika w systemie.
 * @return Ciąg znaków "Kierowca".
 */
std::string Kierowca::pobierzRole() const {
    return "Kierowca";
}

/**
 * @brief Pobiera pełne dane kierowcy, w tym listę uprawnień.
 * @return Sformatowany ciąg danych kadrowych.
 */
std::string Kierowca::pobierzPelneDane() const {
    std::ostringstream oss;
    oss << "[KIEROWCA] PESEL: " << pobierzPesel()
        << " | Imię i Nazwisko: " << pobierzImieNazwisko()
        << " | Stawka: " << pobierzStawke() << " PLN/h"
        << " | Kategorie: ";

    for (size_t i = 0; i < kategoriePrawaJazdy.size(); ++i) {
        oss << kategoriePrawaJazdy[i];
        if (i < kategoriePrawaJazdy.size() - 1) oss << ", ";
    }
    return oss.str();
}

/**
 * @brief Serializuje dane kierowcy do formatu tekstowego.
 * @return Ciąg znaków w formacie "KIEROWCA;pesel;imieNazwisko;stawka;kat1,kat2...".
 */
std::string Kierowca::serializuj() const {
    std::ostringstream oss;
    oss << "KIEROWCA;"
        << pobierzPesel() << ";"
        << pobierzImieNazwisko() << ";"
        << pobierzStawke() << ";";

    for (size_t i = 0; i < kategoriePrawaJazdy.size(); ++i) {
        oss << kategoriePrawaJazdy[i];
        if (i < kategoriePrawaJazdy.size() - 1) {
            oss << ",";
        }
    }

    return oss.str();
}