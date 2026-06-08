/**
* @file MenedzerZlecen.cpp
 * @brief Implementacja logiki biznesowej zarządzania zleceniami i zasobami.
 */

#include "../include/managers/MenedzerZlecen.h"
#include "../include/Zlecenie.h"
#include "../include/Pojazd.h"
#include "../include/Pracownik.h"
#include "../include/Termin.h"
#include "../include/Exceptions.h"

/**
 * @brief Próbuje przypisać pojazd do zlecenia.
 * * Weryfikuje dostępność czasową pojazdu oraz sprawdza, czy co najmniej jeden
 * z już przypisanych pracowników posiada uprawnienia do prowadzenia tego pojazdu.
 * @param z Zlecenie, do którego przypisujemy pojazd.
 * @param p Wskaźnik na pojazd.
 * @return true jeśli przypisanie zakończyło się sukcesem, false w przeciwnym razie.
 */
bool MenedzerZlecen::probaPrzypisaniaPojazdu(Zlecenie& z, std::shared_ptr<Pojazd> p) {
    if (!p) {
        throw std::invalid_argument("Wskaznik na pojazd nie moze byc pusty (nullptr).");
    }

    // 1. Weryfikujemy dostępność czasową pojazdu
    if (!p->czyDostepny(z.pobierzOkres())) {
        throw ResourceUnavailableException("Wybrany pojazd jest zajety w wymaganym okresie zlecenia.");
    }

    // 2. Weryfikujemy czy przypisani pracownicy (kierowcy) mogą prowadzić ten pojazd
    const auto& pracownicy = z.pobierzPracownicy();
    if (!pracownicy.empty()) {
        bool ktosMozeProwadzic = false;
        for (const auto& pr : pracownicy) {
            if (sprawdzUprawnienia(pr, p)) {
                ktosMozeProwadzic = true;
                break;
            }
        }
        if (!ktosMozeProwadzic) {
            throw PermissionDeniedException("Zaden z przypisanych pracownikow nie posiada uprawnien do prowadzenia tego pojazdu.");
        }
    }

    z.dodajPojazd(p);
    return true;
}

/**
 * @brief Próbuje przypisać pracownika do zlecenia.
 * * Weryfikuje dostępność czasową pracownika oraz sprawdza, czy posiada on
 * uprawnienia do obsługi przynajmniej jednego z już przypisanych do zlecenia pojazdów.
 * @param z Zlecenie, do którego przypisujemy pracownika.
 * @param pr Wskaźnik na pracownika.
 * @return true jeśli przypisanie zakończyło się sukcesem, false w przeciwnym razie.
 */
bool MenedzerZlecen::probaPrzypisaniaPracownika(Zlecenie& z, std::shared_ptr<Pracownik> pr) {
    if (!pr) {
        throw std::invalid_argument("Wskaznik na pracownika nie moze byc pusty (nullptr).");
    }

    // 1. Weryfikujemy dostępność czasową pracownika
    if (!pr->czyDostepny(z.pobierzOkres())) {
        throw ResourceUnavailableException("Wybrany pracownik ma juz przypisane inne obowiazki w tym czasie.");
    }

    // 2. Weryfikujemy uprawnienia względem już przypisanych pojazdów
    const auto& pojazdy = z.pobierzPojazdy();
    if (!pojazdy.empty()) {
        bool mozeObsluzycJakis = false;
        for (const auto& p : pojazdy) {
            if (sprawdzUprawnienia(pr, p)) {
                mozeObsluzycJakis = true;
                break;
            }
        }

        if (!mozeObsluzycJakis) {
            throw PermissionDeniedException("Pracownik nie posiada uprawnien do obslugi zadnego z przypisanych pojazdow.");
        }
    }

    z.dodajPracownika(pr);
    return true;
}

/**
 * @brief Sprawdza, czy zlecenie jest w pełni przygotowane do realizacji.
 * * Weryfikuje, czy zlecenie nie zostało już rozliczone, czy posiada przypisane
 * pojazdy oraz czy dla każdego przypisanego pojazdu znajduje się przynajmniej
 * jeden pracownik z odpowiednimi uprawnieniami.
 * @param z Zlecenie do weryfikacji.
 * @return true jeśli zlecenie jest gotowe do realizacji, false w przeciwnym razie.
 */
bool MenedzerZlecen::weryfikujGotowoscDoRealizacji(const Zlecenie& z) {
    if (z.czyJestRozliczone()) {
        return false;
    }

    const auto& pojazdy = z.pobierzPojazdy();
    const auto& pracownicy = z.pobierzPracownicy();

    if (pojazdy.empty()) {
        return false;
    }

    for (const auto& p : pojazdy) {
        bool maKierowce = false;
        for (const auto& pr : pracownicy) {
            if (sprawdzUprawnienia(pr, p)) {
                maKierowce = true;
                break;
            }
        }
        if (!maKierowce) {
            return false;
        }
    }

    return true;
}

/**
 * @brief Pomocnicza metoda weryfikująca uprawnienia pracownika do obsługi pojazdu.
 * @param pr Wskaźnik na pracownika.
 * @param p Wskaźnik na pojazd.
 * @return true jeśli pracownik może wykonać pracę w danym pojeździe, false w przeciwnym razie.
 */
bool MenedzerZlecen::sprawdzUprawnienia(std::shared_ptr<Pracownik> pr, std::shared_ptr<Pojazd> p) {
    if (!pr || !p) return false;
    std::string wymaganaKat = p->pobierzWymaganaKategorie();
    return pr->mozeWykonacPrace(wymaganaKat);
}

/**
 * @brief Sprawdza dostępność wszystkich zasobów już przypisanych do zlecenia.
 * * Użyteczne przy sprawdzaniu, czy wcześniejsze rezerwacje zasobów nadal
 * są poprawne w kontekście okresu realizacji zlecenia.
 * @param z Zlecenie z przypisanymi zasobami.
 * @return true jeśli wszystkie zasoby są dostępne, false jeśli wystąpiła kolizja.
 */
bool MenedzerZlecen::sprawdzDostepnoscZasobow(const Zlecenie& z) const {
    // weryfikacja zasobów już przypisanych do zlecenia
    for (const auto& p : z.pobierzPojazdy()) {
        if (!p->czyDostepny(z.pobierzOkres())) return false;
    }
    for (const auto& pr : z.pobierzPracownicy()) {
        if (!pr->czyDostepny(z.pobierzOkres())) return false;
    }
    
    return true;
}
