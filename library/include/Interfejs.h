//
// Created by Kinga Ratajska on 15/04/2026.
//

#ifndef ATOM_PN_1330_06_INTERFEJS_H
#define ATOM_PN_1330_06_INTERFEJS_H

#pragma once
#include "repositories/RepozytoriumKlientow.h"
#include "repositories/RepozytoriumPojazdow.h"
#include "repositories/RepozytoriumPracownikow.h"
#include "repositories/RepozytoriumZlecen.h"

class InterfejsUI {
private:
    RepozytoriumKlientow repoKlienci;
    RepozytoriumPojazdow repoPojazdy;
    RepozytoriumPracownikow repoPracownicy;
    RepozytoriumZlecen repoZlecenia;

public:
    InterfejsUI();

    void uruchom();
    void wyswietlMenu();
    void obsluzKreatorZlecenia();
};

#endif //ATOM_PN_1330_06_INTERFEJS_H
