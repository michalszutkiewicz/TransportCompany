#ifndef POBI_MENEDZERZLECEN_H
#define POBI_MENEDZERZLECEN_H

#pragma once
#include <memory>

// Forward declarations
class Zlecenie;
class Pojazd;
class Pracownik;

class MenedzerZlecen {
public:
    MenedzerZlecen() = default;

    // Przechodzimy na shared_ptr dla spójności z klasą Zlecenie
    bool probaPrzypisaniaPojazdu(Zlecenie& z, std::shared_ptr<Pojazd> p);
    bool probaPrzypisaniaPracownika(Zlecenie& z, std::shared_ptr<Pracownik> pr);
    bool weryfikujGotowoscDoRealizacji(const Zlecenie& z);
    bool sprawdzUprawnienia(std::shared_ptr<Pracownik> pr, std::shared_ptr<Pojazd> p);
    bool sprawdzDostepnoscZasobow(const Zlecenie& z) const;
};

#endif //POBI_MENEDZERZLECEN_H