//
// Created by Kinga Ratajska on 15/04/2026.
//

#ifndef ATOM_PN_1330_06_OBSLUGAPLIKOW_H
#define ATOM_PN_1330_06_OBSLUGAPLIKOW_H


#pragma once
#include "Firma.h"
#include <string>

class ObslugaPlikow {
public:
    static void zapiszStanSystemu(const Firma& f, const std::string& sciezka);
    static Firma wczytajStanSystemu(const std::string& sciezka);
};

#endif //ATOM_PN_1330_06_OBSLUGAPLIKOW_H