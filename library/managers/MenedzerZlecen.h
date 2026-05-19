#ifndef POBI_MENEDZERZLECEN_H
#define POBI_MENEDZERZLECEN_H

#pragma once

class Zlecenie;
class Pojazd;
class Pracownik;

class MenedzerZlecen {
public:
    MenedzerZlecen() = default;

    // Przekazujemy Zlecenie przez referencję (bo będziemy je modyfikować np. dodając pojazd)
    bool probaPrzypisaniaPojazdu(Zlecenie& z, Pojazd* p);

    bool probaPrzypisaniaPracownika(Zlecenie& z, Pracownik* pr);

    bool weryfikujGotowoscDoRealizacji(const Zlecenie& z);
};

#endif //POBI_MENEDZERZLECEN_H