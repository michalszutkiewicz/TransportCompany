//
// Created by MichalSw11 on 04.06.2026.
//

#ifndef ATOM_PN_1330_06_REPOZYTORIUMPRACOWNIKOW_H
#define ATOM_PN_1330_06_REPOZYTORIUMPRACOWNIKOW_H

#pragma once
#include "ISerializowalny.h"
#include "Pracownik.h"
#include <vector>
#include <memory>
#include <functional>
#include <string>

using PracownikPredykat = std::function<bool(std::shared_ptr<Pracownik>)>;

class RepozytoriumPracownikow : public ISerializowalny {

private:
    std::vector<std::shared_ptr<Pracownik>> elementy;

public:
    std::shared_ptr<Pracownik> pobierzPracownik(const std::string& id) const;
    std::shared_ptr<Pracownik> pobierzPoIndeksie(int i) const;
    void dodajPracownika(std::shared_ptr<Pracownik> element);
    void usunPracownika(std::shared_ptr<Pracownik> element);

    std::string raport() const;
    int rozmiar() const;

    std::vector<std::shared_ptr<Pracownik>> znajdzPo(PracownikPredykat predykat) const;
    std::vector<std::shared_ptr<Pracownik>> pobierzWszystkie() const;

    // Implementacja ISerializowalny
    void zapiszStan(const std::string& sciezka) const override;
    void wczytajStan(const std::string& sciezka) override;
    std::string serializuj() const override;
    void deserializuj(const std::string& dane) override;
};

#endif //ATOM_PN_1330_06_REPOZYTORIUMPRACOWNIKOW_H
