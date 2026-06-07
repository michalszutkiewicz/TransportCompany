#ifndef ATOM_PN_1330_06_KLIENT_H
#define ATOM_PN_1330_06_KLIENT_H

#pragma once
#include <string>
#include <vector>
#include <memory>

class Klient {
private:
    std::string idKlienta;
    std::string imie;
    std::string nazwisko;

public:
    Klient(std::string id, std::string imie, std::string nazwisko);
    virtual ~Klient() = default;

    std::string pobierzId() const { return idKlienta; }
    std::string pobierzImie() const { return imie; }
    std::string pobierzNazwisko() const { return nazwisko; }
    
    std::string pobierzPelneDane() const;

    virtual std::string serializuj() const;
};

#endif //ATOM_PN_1330_06_KLIENT_H
