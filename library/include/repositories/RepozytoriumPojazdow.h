//
// Created by MichalSw11 on 04.06.2026.
//

#ifndef ATOM_PN_1330_06_REPOZYTORIUMPOJAZDOW_H
#define ATOM_PN_1330_06_REPOZYTORIUMPOJAZDOW_H

#pragma once
#include "ISerializowalny.h"
#include "Pojazd.h"
#include <vector>
#include <memory>
#include <functional>
#include <string>

using PojazdPredykat = std::function<bool(std::shared_ptr<Pojazd>)>;

class RepozytoriumPojazdow : public ISerializowalny {

private:
    std::vector<std::shared_ptr<Pojazd>> elementy;

public:
    std::shared_ptr<Pojazd> pobierzPojazd(const std::string& id) const;
    std::shared_ptr<Pojazd> pobierzPoIndeksie(int i) const;
    void dodajPojazd(std::shared_ptr<Pojazd> element);
    void usunPojazd(std::shared_ptr<Pojazd> element);

    std::string raport() const;
    int rozmiar() const;

    std::vector<std::shared_ptr<Pojazd>> znajdzPo(PojazdPredykat predykat) const;
    std::vector<std::shared_ptr<Pojazd>> pobierzWszystkie() const;

    // Implementacja ISerializowalny
    void zapiszStan(const std::string& sciezka) const override;
    void wczytajStan(const std::string& sciezka) override;
    std::string serializuj() const override;
    void deserializuj(const std::string& dane) override;
};

#endif //ATOM_PN_1330_06_REPOZYTORIUMPOJAZDOW_H
