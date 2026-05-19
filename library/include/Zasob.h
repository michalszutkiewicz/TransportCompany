#pragma once
#include <string>

#ifndef ATOM_PN_1330_06_ZASOB_H
#define ATOM_PN_1330_06_ZASOB_H

class Zasob {
protected:
    std::string id;
    bool czyDostepny;

public:
    Zasob(std::string id) : id(id), czyDostepny(true) {}
    virtual ~Zasob() = default;

    virtual bool czySpełniaWymagania(double wymaganie) const = 0;

    void ustawDostepnosc(bool status) { czyDostepny = status; }
    bool sprawdzCzyWolny() const { return czyDostepny; }
    std::string pobierzId() const { return id; }
};

#endif //ATOM_PN_1330_06_ZASOB_H