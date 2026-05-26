//
// Created by Kinga Ratajska on 15/04/2026.
//

#ifndef ATOM_PN_1330_06_ZLECENIE_H
#define ATOM_PN_1330_06_ZLECENIE_H
#pragma once
#include <memory>
#include <vector>
#include <string>
#include "Termin.h"

// Forward declarations
class Klient;
class Usluga;
class Pojazd;
class Pracownik;

class Zlecenie {
private:
    std::string idZlecenia;
    Termin okresRealizacji;
    bool czyRozliczone;

    std::shared_ptr<Klient> klient;
    std::shared_ptr<Usluga> usluga;
    std::vector<std::shared_ptr<Pojazd>> przypisanePojazdy;
    std::vector<std::shared_ptr<Pracownik>> przypisaniPracownicy;

public:
    Zlecenie(std::string id, Termin okres, std::shared_ptr<Klient> k, std::shared_ptr<Usluga> u);

    //zarządzanie zasobami
    void dodajPojazd(std::shared_ptr<Pojazd> pojazd);
    void dodajPracownika(std::shared_ptr<Pracownik> pracownik);


    //logika finansowa i status
    double obliczPelnyKoszt() const;
    void rozlicz() { czyRozliczone = true; }
    bool czyJestRozliczone() const { return czyRozliczone; }

    //gettery do dokumentacji/interfejsu
    std::string pobierzPodsumowanie() const;
    std::shared_ptr<Klient> pobierzKlienta() const { return klient; }
};

#endif //ATOM_PN_1330_06_ZLECENIE_H