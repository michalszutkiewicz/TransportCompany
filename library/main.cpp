#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <boost/date_time/posix_time/posix_time.hpp>

// Nagłówki logiki
#include "Firma.h"
#include "Klient.h"
#include "Zlecenie.h"
#include "Termin.h"
#include "managers/MenedzerZlecen.h"

// Nagłówki polimorficzne zasoby
#include "Pojazd.h"
#include "Pracownik.h"
#include "Ciezarowka.h"
#include "Kierowca.h"

// Nagłówki polimorficzne uslugi
#include "TransportStandardowy.h"
#include "TransportEkspresowy.h"

namespace pt = boost::posix_time;
namespace gr = boost::gregorian;

int main() {
    std::cout << "--- System Zarzadzania Firma Transportowa ---" << std::endl;

    // 1. Inicjalizacja firmy i menedżera
    auto mojaFirma = std::make_shared<Firma>("Firma Transportowa");
    MenedzerZlecen menedzer;

    // 2. Dodawanie klienta
    auto klient1 = std::make_shared<Klient>("Jan", "Kowalski", "90010112345");
    mojaFirma->dodajKlienta(klient1);

    // 3. Dodawanie zasobów do floty
    auto tir = std::make_shared<Ciezarowka>("EL 12345", 150.0, 24.0, true);

    std::vector<std::string> kategorieKierowcy = {"B", "C", "C+E"};
    auto kierowca = std::make_shared<Kierowca>("85020254321", "Adam Nowak", 45.0, kategorieKierowcy);

    mojaFirma->rejestrujPojazd(tir);
    mojaFirma->zatrudnijPracownika(kierowca);

    // 4. Tworzenie usługi
    auto ekspres = std::make_shared<TransportEkspresowy>("Dostawa czesci", 500.0, 5.0, 200.0);

    // 5. Tworzenie i konfiguracja zlecenia
    pt::ptime czasRozpoczecia(gr::date(2026, 4, 30), pt::hours(8));
    pt::ptime czasZakonczenia(gr::date(2026, 4, 30), pt::hours(16));
    Termin okresZlecenia(czasRozpoczecia, czasZakonczenia);

    auto noweZlecenie = std::make_shared<Zlecenie>("Z/2026/01", okresZlecenia, klient1, ekspres);

    // 6. Bezpieczne przypisanie zasobów (WALIDACJA)
    std::cout << "\n--- PROBA PRZYPISANIA ZASOBOW PRZEZ MENEDZERA ---" << std::endl;

    // Próbujemy przypisać pojazd
    if (menedzer.probaPrzypisaniaPojazdu(*noweZlecenie, tir)) {
        std::cout << "[OK] Pojazd " << tir->pobierzOpisPojazdu() << " przypisany." << std::endl;
    } else {
        std::cout << "[BLAD] Nie mozna przypisac pojazdu!" << std::endl;
    }

    // Próbujemy przypisać pracownika
    if (menedzer.probaPrzypisaniaPracownika(*noweZlecenie, kierowca)) {
        std::cout << "[OK] Pracownik " << kierowca->pobierzRole() << " przypisany." << std::endl;
    } else {
        std::cout << "[BLAD] Nie mozna przypisac pracownika (brak uprawnien lub kolizja terminow)!" << std::endl;
    }

    // 7. Weryfikacja gotowości i rejestracja
    if (menedzer.weryfikujGotowoscDoRealizacji(*noweZlecenie)) {
        std::cout << "Status: Zlecenie GOTOWE do realizacji." << std::endl;
        mojaFirma->dodajZlecenie(noweZlecenie);
    } else {
        std::cout << "Status: Zlecenie NIEKOMPLETNE." << std::endl;
    }

    // 8. WYNIK TESTU
    std::cout << "\n--- PODSUMOWANIE ZLECENIA ---" << std::endl;
    std::cout << noweZlecenie->pobierzPodsumowanie() << std::endl;
    std::cout << "Szczegoly uslugi: " << ekspres->pobierzSzczegoly() << std::endl;

    return 0;
}
