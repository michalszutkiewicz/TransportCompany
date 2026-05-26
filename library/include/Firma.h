#ifndef ATOM_PN_1330_06_FIRMA_H
#define ATOM_PN_1330_06_FIRMA_H

#pragma once
#include <vector>
#include <memory>
#include <string>

// Forward declarations
class Klient;
class Pojazd;
class Pracownik;
class Zlecenie;

class Firma {
private:
    std::string nazwaFirmy;

    // Kontenery na dane (polimorfizmy)
    std::vector<std::shared_ptr<Klient>> klienci;
    std::vector<std::shared_ptr<Pojazd>> pojazdy;
    std::vector<std::shared_ptr<Pracownik>> pracownicy;
    std::vector<std::shared_ptr<Zlecenie>> zlecenia;

public:
    Firma(std::string nazwa);
    ~Firma() = default;

    // Zarządzanie Klientami
    void dodajKlienta(std::shared_ptr<Klient> klient);
    std::shared_ptr<Klient> pobierzKlienta(std::string id);

    // Zarządzanie Zasobami
    void rejestrujPojazd(std::shared_ptr<Pojazd> pojazd);
    void zatrudnijPracownika(std::shared_ptr<Pracownik> pracownik);

    // Zarządzanie Zleceniami
    void dodajZlecenie(std::shared_ptr<Zlecenie> zlecenie);

    // Metody biznesowe
    double obliczCalkowityPrzychod() const;
};

#endif //ATOM_PN_1330_06_FIRMA_H