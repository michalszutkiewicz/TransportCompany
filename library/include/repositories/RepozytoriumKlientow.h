//
// Created by MichalSw11 on 04.06.2026.
//

#ifndef ATOM_PN_1330_06_REPOZYTORIUMKLIENTOW_H
#define ATOM_PN_1330_06_REPOZYTORIUMKLIENTOW_H

#pragma once
#include "ISerializowalny.h"
#include "Klient.h"
#include <vector>
#include <memory>
#include <functional>
#include <string>


using KlientPredykat = std::function<bool(std::shared_ptr<Klient>)>;

class RepozytoriumKlientow : public ISerializowalny {

private:
    std::vector<std::shared_ptr<Klient>> elementy;

public:
    std::shared_ptr<Klient> pobierzKlienta(const std::string& id) const;
    std::shared_ptr<Klient> pobierzPoIndeksie(int i) const;
    void dodajKlienta(std::shared_ptr<Klient> element);
    void usunKlienta(std::shared_ptr<Klient> element);

    std::string raport() const;
    int rozmiar() const;

    std::vector<std::shared_ptr<Klient>> znajdzPo(KlientPredykat predykat) const;
    std::vector<std::shared_ptr<Klient>> pobierzWszystkie() const;

    // Implementacja ISerializowalny
    void zapiszStan(const std::string& sciezka) override;
    void wczytajStan(const std::string& sciezka) override;
    std::string serializuj() const override;
    void deserializuj(const std::string& dane) override;
};

#endif //ATOM_PN_1330_06_REPOZYTORIUMKLIENTOW_H
