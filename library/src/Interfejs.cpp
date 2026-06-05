//
// Created by Kinga Ratajska on 15/04/2026.
//

#include "Interfejs.h"
#include <iostream>

using namespace std;

InterfejsUI::InterfejsUI() {
    // Konstruktor może inicjować repozytoria lub ładować je z pliku
}

void InterfejsUI::uruchom() {
    bool dziala = true;
    while (dziala) {
        wyswietlMenu();
        int wybor;
        if (!(cin >> wybor)) {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        
        switch (wybor) {
            case 1:
                obsluzKreatorZlecenia();
                break;
            case 0:
                dziala = false;
                break;
            default:
                cout << "Nieznana opcja." << endl;
        }
    }
}

void InterfejsUI::wyswietlMenu() {
    cout << "--- MENU GŁÓWNE ---" << endl;
    cout << "1. Kreator Zlecenia" << endl;
    cout << "0. Wyjście" << endl;
    cout << "Wybierz opcję: ";
}

void InterfejsUI::obsluzKreatorZlecenia() {
    cout << "Uruchomiono kreator zlecenia..." << endl;
    // Logika dodawania do repoZlecenia
}
