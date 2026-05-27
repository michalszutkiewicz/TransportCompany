#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <boost/date_time/posix_time/posix_time.hpp> // Niezbędne dla klasy Termin

// Nagłówki logiki
#include "Firma.h"
#include "Klient.h"
#include "Zlecenie.h"
#include "Termin.h" // Dodany brakujący nagłówek

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

    // 1. Inicjalizacja firmy
    auto mojaFirma = std::make_shared<Firma>("Firma Transportowa");

    // 2. Dodawanie klienta
    auto klient1 = std::make_shared<Klient>("Jan", "Kowalski", "90010112345");
    mojaFirma->dodajKlienta(klient1);

    // 3. Dodawanie zasobów do floty
    auto tir = std::make_shared<Ciezarowka>("EL 12345", 150.0, 24.0, true);

    std::vector<std::string> kategorieKierowcy = {"B", "C", "C+E"};
    auto kierowca = std::make_shared<Kierowca>("85020254321", "Adam Nowak", 45.0, kategorieKierowcy);

    mojaFirma->rejestrujPojazd(tir);
    mojaFirma->zatrudnijPracownika(kierowca);

    // 4. Tworzenie usługi (Tu działa polimorfizm!)
    // Wybieramy transport ekspresowy: 500km, 5.0 PLN/km, 200 PLN opłaty stałej
    auto ekspres = std::make_shared<TransportEkspresowy>("Dostawa czesci", 500.0, 5.0, 200.0);

    // 5. Tworzenie i konfiguracja zlecenia
    // Tworzymy obiekty czasu dla Terminu (np. 30 kwietnia 2026 od 08:00 do 16:00)
    pt::ptime czasRozpoczecia(gr::date(2026, 4, 30), pt::hours(8));
    pt::ptime czasZakonczenia(gr::date(2026, 4, 30), pt::hours(16));
    Termin okresZlecenia(czasRozpoczecia, czasZakonczenia);


    auto noweZlecenie = std::make_shared<Zlecenie>("Z/2026/01", okresZlecenia, klient1, ekspres);

    // Przypisujemy zasoby (automatycznie rezerwują termin w wektorze zajeteTerminy)
    noweZlecenie->dodajPojazd(tir);
    noweZlecenie->dodajPracownika(kierowca);

    // Rejestrujemy zlecenie w systemie firmy
    mojaFirma->dodajZlecenie(noweZlecenie);

    // 6. WYNIK TESTU
    std::cout << "\n--- PODSUMOWANIE ZLECENIA ---" << std::endl;
    std::cout << noweZlecenie->pobierzPodsumowanie() << std::endl;
    std::cout << "Szczegoly uslugi: " << ekspres->pobierzSzczegoly() << std::endl;

    // Sprawdzenie statusu zasobów w zadanym terminie
    std::cout << "\nStatus zasobu TIR w tym terminie: "
              << (tir->czyDostepny(okresZlecenia) ? "Wolny" : "ZAJETY (KOLIZJA)") << std::endl;

    return 0;
}