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

    double wymaganaWaga;
    double objetosc;
    std::string wymaganaKategoria;

    std::shared_ptr<Klient> klient;
    std::shared_ptr<Usluga> usluga;
    std::vector<std::shared_ptr<Pojazd>> przypisanePojazdy;
    std::vector<std::shared_ptr<Pracownik>> przypisaniPracownicy;

public:
    Zlecenie(std::string id, Termin okres, std::shared_ptr<Klient> k, std::shared_ptr<Usluga> u, double waga, double obj, std::string kat);

    void dodajPojazd(std::shared_ptr<Pojazd> p);
    void dodajPracownika(std::shared_ptr<Pracownik> pr);
    double obliczPelnyKoszt() const;
    void rozlicz();
    Termin pobierzOkres() const;
    std::string pobierzId() const { return idZlecenia; }
    bool czyJestRozliczone() const { return czyRozliczone; }
    std::shared_ptr<Klient> pobierzKlienta() const { return klient; }
    const std::vector<std::shared_ptr<Pojazd>>& pobierzPojazdy() const { return przypisanePojazdy; }
    const std::vector<std::shared_ptr<Pracownik>>& pobierzPracownicy() const { return przypisaniPracownicy; }
    
    double pobierzWymaganaWage() const { return wymaganaWaga; }
    double pobierzObjetosc() const { return objetosc; }
    std::string pobierzWymaganaKategorie() const { return wymaganaKategoria; }
    
    std::string pobierzPodsumowanie() const;

    std::string serializuj() const;
};

#endif //ATOM_PN_1330_06_ZLECENIE_H
