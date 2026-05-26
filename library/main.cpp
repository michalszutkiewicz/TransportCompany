#include <iostream>
#include <memory>
#include <vector>

//naglowki logiki
#include "Firma.h"
#include "Klient.h"
#include "Zlecenie.h"

//nagłówki polimorficzne-zasoby
#include "Pojazd.h"
#include "Pracownik.h"
#include "Ciezarowka.h"
#include "Kierowca.h"

//nagłówki polimorficzne -uslugi
#include "TransportStandardowy.h"
#include "TransportEkspresowy.h"

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
    auto noweZlecenie = std::make_shared<Zlecenie>(1,"Z/2026/01", "2026-04-30", klient1, ekspres);

    // Przypisujemy zasoby (automatycznie zmieniają status na zajęte)
    noweZlecenie->dodajZasob(tir);
    noweZlecenie->dodajZasob(kierowca);

    // Rejestrujemy zlecenie w systemie firmy
    mojaFirma->utworzZlecenie(noweZlecenie);

    // 6. WYNIK TESTU
    std::cout << "\n--- PODSUMOWANIE ZLECENIA ---" << std::endl;
    std::cout << noweZlecenie->pobierzPodsumowanie() << std::endl;
    std::cout << "Szczegoly uslugi: " << ekspres->pobierzSzczegoly() << std::endl;

    // Sprawdzenie statusu zasobów po rezerwacji
    std::cout << "\nStatus zasobu TIR: " << (tir->sprawdzCzyWolny() ? "Wolny" : "ZAJETY") << std::endl;

    std::cout << "\n--- Test zakonczony sukcesem ---" << std::endl;
*/
    return 0;
}