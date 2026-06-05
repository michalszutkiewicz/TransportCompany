#ifndef ATOM_PN_1330_06_FIRMA_H
#define ATOM_PN_1330_06_FIRMA_H

#pragma once
#include "repositories/RepozytoriumKlientow.h"
#include "repositories/RepozytoriumPojazdow.h"
#include "repositories/RepozytoriumPracownikow.h"
#include "repositories/RepozytoriumZlecen.h"

class Firma {
private:
    RepozytoriumKlientow repoKlientow;
    RepozytoriumPojazdow repoPojazdow;
    RepozytoriumPracownikow repoPracownikow;
    RepozytoriumZlecen repoZlecen;

public:
    Firma();
    ~Firma() = default;

    // Dostęp do repozytoriów
    RepozytoriumKlientow& pobierzRepozytoriumKlientow();
    RepozytoriumPojazdow& pobierzRepozytoriumPojazdow();
    RepozytoriumPracownikow& pobierzRepozytoriumPracownikow();
    RepozytoriumZlecen& pobierzRepozytoriumZlecen();

    // Logika biznesowa
    double obliczCalkowityPrzychod() const;
};

#endif //ATOM_PN_1330_06_FIRMA_H