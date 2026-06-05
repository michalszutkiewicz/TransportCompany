//
// Created by Kinga Ratajska on 15/04/2026.
//

#include "ObslugaPlikow.h"
#include <fstream>
#include <iostream>

using namespace std;

void ObslugaPlikow::zapiszStanSystemu(const Firma& f, const string& sciezka) {
    ofstream plik(sciezka);
    if (!plik.is_open()) return;

    // Pobieramy zrzuty serializacji z repozytoriów, w rzutowaniu do obiektu stałego
    // Aby to działało idealnie, gettery repozytoriów w Firmie powinny mieć też wersję 'const'
    // Przykład uproszczony:
    // plik << const_cast<Firma&>(f).pobierzRepozytoriumKlientow().serializuj() << "\n";

    plik.close();
}

Firma ObslugaPlikow::wczytajStanSystemu(const string& sciezka) {
    Firma nowaFirma;
    ifstream plik(sciezka);

    if (!plik.is_open()) {
        return nowaFirma;
    }

    // Logika wczytywania sekcji do poszczególnych repozytoriów
    // string linia;
    // ...
    // nowaFirma.pobierzRepozytoriumKlientow().deserializuj(daneZPliku);

    return nowaFirma;
}
