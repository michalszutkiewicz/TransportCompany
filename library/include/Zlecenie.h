//
// Created by Kinga Ratajska on 15/04/2026.
//

#ifndef ATOM_PN_1330_06_ZLECENIE_H
#define ATOM_PN_1330_06_ZLECENIE_H
#pragma once
#include <memory>
#include <vector>
#include <string>

// Forward declarations
class Klient;
class Usluga;
class Zasob;

class Zlecenie {
private:
    std::string idZlecenia;
    std::string terminRealizacji;
    bool czyRozliczone;

    std::shared_ptr<Klient> klient;
    std::shared_ptr<Usluga> usluga;
    std::vector<std::shared_ptr<Zasob>> przypisaneZasoby;

public:
    Zlecenie(std::string id, std::string termin, std::shared_ptr<Klient> k, std::shared_ptr<Usluga> u);

    //zarządzanie zasobami
    void dodajZasob(std::shared_ptr<Zasob> zasob);

    //logika finansowa i status
    double obliczPelnyKoszt() const;
    void rozlicz() { czyRozliczone = true; }
    bool czyJestRozliczone() const { return czyRozliczone; }

    //gettery do dokumentacji/interfejsu
    std::string pobierzPodsumowanie() const;
    std::shared_ptr<Klient> pobierzKlienta() const { return klient; }
};

#endif //ATOM_PN_1330_06_ZLECENIE_H