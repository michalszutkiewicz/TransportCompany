#include "../include/managers/MenedzerZlecen.h"
#include "../include/Zlecenie.h"
#include "../include/Pojazd.h"
#include "../include/Pracownik.h"
#include "../include/Termin.h"

bool MenedzerZlecen::probaPrzypisaniaPojazdu(Zlecenie& z, std::shared_ptr<Pojazd> p) {
    if (!p) {
        return false;
    }

    // 1. Weryfikujemy dostępność czasową pojazdu
    if (!p->czyDostepny(z.pobierzOkres())) {
        return false;
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
            return false;
        }
    }

    z.dodajPojazd(p);
    return true;
}

bool MenedzerZlecen::probaPrzypisaniaPracownika(Zlecenie& z, std::shared_ptr<Pracownik> pr) {
    if (!pr) {
        return false;
    }

    // 1. Weryfikujemy dostępność czasową pracownika
    if (!pr->czyDostepny(z.pobierzOkres())) {
        return false;
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
            return false;
        }
    }

    z.dodajPracownika(pr);
    return true;
}

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

bool MenedzerZlecen::sprawdzUprawnienia(std::shared_ptr<Pracownik> pr, std::shared_ptr<Pojazd> p) {
    if (!pr || !p) return false;
    std::string wymaganaKat = p->pobierzWymaganaKategorie();
    return pr->mozeWykonacPrace(wymaganaKat);
}

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
