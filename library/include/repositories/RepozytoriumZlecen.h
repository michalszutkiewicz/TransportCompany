//
// Created by MichalSw11 on 04.06.2026.
//

#ifndef ATOM_PN_1330_06_REPOZYTORIUMZLECEN_H
#define ATOM_PN_1330_06_REPOZYTORIUMZLECEN_H

#pragma once
#include "ISerializowalny.h"
#include "Zlecenie.h"
#include <vector>
#include <memory>
#include <functional>
#include <string>

class RepozytoriumKlientow;
class RepozytoriumPojazdow;
class RepozytoriumPracownikow;

using ZleceniePredykat = std::function<bool(std::shared_ptr<Zlecenie>)>;

class RepozytoriumZlecen : public ISerializowalny {

private:
    std::vector<std::shared_ptr<Zlecenie>> elementy;

public:
    std::shared_ptr<Zlecenie> pobierzZlecenie(const std::string& id) const;
    std::shared_ptr<Zlecenie> pobierzPoIndeksie(int i) const;
    void dodajZlecenie(std::shared_ptr<Zlecenie> element);
    void usunZlecenie(std::shared_ptr<Zlecenie> element);

    std::string raport() const;
    int rozmiar() const;

    std::vector<std::shared_ptr<Zlecenie>> znajdzPo(ZleceniePredykat predykat) const;
    std::vector<std::shared_ptr<Zlecenie>> pobierzWszystkie() const;

    // Implementacja ISerializowalny
    void zapiszStan(const std::string& sciezka) const override;
    void wczytajStan(const std::string& sciezka) override;
    void wczytajStan(const std::string& sciezka,
                     RepozytoriumKlientow& rKlienci,
                     RepozytoriumPojazdow& rPojazdy,
                     RepozytoriumPracownikow& rPracownicy);

    std::string serializuj() const override;
    void deserializuj(const std::string& dane) override;
};

#endif //ATOM_PN_1330_06_REPOZYTORIUMZLECEN_H
