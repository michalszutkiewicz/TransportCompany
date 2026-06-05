//
// Created by MichalSw11 on 05.06.2026.
//

#ifndef ATOM_PN_1330_06_ISERIALIZOWANY_H
#define ATOM_PN_1330_06_ISERIALIZOWANY_H

#pragma once
#include <string>

class ISerializowalny {
public:
    virtual ~ISerializowalny() = default;

    virtual void zapiszStan(const std::string& sciezka) = 0;
    virtual void wczytajStan(const std::string& sciezka) = 0;

    // Metody pomocnicze do serializacji danych wewnętrznych
    virtual std::string serializuj() const = 0;
    virtual void deserializuj(const std::string& dane) = 0;
};

#endif //ATOM_PN_1330_06_ISERIALIZOWANY_H
