/**
* @file MenedzerZlecenTests.cpp
 * @brief Testy jednostkowe klasy MenedzerZlecen.
 * * Testy sprawdzają logikę przydzielania zasobów (pojazdów i pracowników) do zleceń
 * oraz weryfikują warunki gotowości zleceń do realizacji.
 */

#include <boost/test/unit_test.hpp>
#include "managers/MenedzerZlecen.h"
#include "Zlecenie.h"
#include "Klient.h"
#include "TransportStandardowy.h"
#include "BusDostawczy.h"
#include "Ciezarowka.h"
#include "Kierowca.h"
#include "Termin.h"
#include "Exceptions.h"

/**
 * @brief Testuje proces przypisywania zasobów do zlecenia.
 * * Weryfikuje:
 * - Poprawne przypisanie dostępnego pojazdu.
 * - Blokadę przypisania pojazdu, który jest już zarezerwowany w danym terminie.
 * - Logikę uprawnień (kierowca musi posiadać odpowiednią kategorię dla przypisanego pojazdu).
 */
BOOST_AUTO_TEST_CASE(PrzypisanieZasobowTest) {
   MenedzerZlecen menedzer;
    pt::ptime d1(gr::date(2026, 6, 10), pt::hours(10));
    pt::ptime d2(gr::date(2026, 6, 10), pt::hours(14));
    Termin t(d1, d2);
    auto klient = std::make_shared<Klient>("1", "Jan", "Kowalski");
    auto usluga = std::make_shared<TransportStandardowy>("Standard", 100.0, 5.0);
    Zlecenie zlecenie("Z1", t, klient, usluga, 100.0, 2.0, "B");

    auto pojazd = std::make_shared<BusDostawczy>("EL12345", 50.0, 10.0);
    auto kierowcaB = std::make_shared<Kierowca>("1", "Kierowca B", 30.0, std::vector<std::string>{"B"});
    auto kierowcaC = std::make_shared<Kierowca>("2", "Kierowca C", 40.0, std::vector<std::string>{"C"});

    // Poprawne przypisanie pojazdu (nie rzuca wyjątku)
    BOOST_CHECK_NO_THROW(menedzer.probaPrzypisaniaPojazdu(zlecenie, pojazd));

    // Próba przypisania tego samego pojazdu do innego zlecenia (kolizja czasowa)
    Zlecenie zlecenie2("Z2", t, klient, usluga, 50.0, 1.0, "B");
    BOOST_CHECK_THROW(menedzer.probaPrzypisaniaPojazdu(zlecenie2, pojazd), ResourceUnavailableException);

    // Przypisanie pracownika z odpowiednimi uprawnieniami
    BOOST_CHECK_NO_THROW(menedzer.probaPrzypisaniaPracownika(zlecenie, kierowcaB));

    // Weryfikacja sprawdzania uprawnień wprost na metodzie
    auto ciezarowka = std::make_shared<Ciezarowka>("EL99999", 100.0, 20.0, true);
    BOOST_CHECK(menedzer.sprawdzUprawnienia(kierowcaC, ciezarowka) == true);
    BOOST_CHECK(menedzer.sprawdzUprawnienia(kierowcaB, ciezarowka) == false);

    // Testowanie rzucania PermissionDeniedException
    Zlecenie zlecenie3("Z3", t, klient, usluga, 1000.0, 20.0, "C");
    zlecenie3.dodajPracownika(kierowcaB);
    // Próba przypisania ciężarówki (wymaga kat. "C"), żaden pracownik zlecenia nie ma uprawnień:
    BOOST_CHECK_THROW(menedzer.probaPrzypisaniaPojazdu(zlecenie3, ciezarowka), PermissionDeniedException);
}

/**
 * @brief Testuje weryfikację gotowości zlecenia do realizacji.
 * * Sprawdza, czy zlecenie jest uznawane za gotowe tylko wtedy, gdy:
 * - Posiada przypisany pojazd.
 * - Posiada przypisanego pracownika z odpowiednimi uprawnieniami do pojazdu.
 * - Zlecenie nie zostało wcześniej rozliczone.
 */
BOOST_AUTO_TEST_CASE(WeryfikujGotowoscTest) {
    MenedzerZlecen menedzer;
    pt::ptime d1(gr::date(2026, 6, 10), pt::hours(10));
    pt::ptime d2(gr::date(2026, 6, 10), pt::hours(14));
    Termin t(d1, d2);
    auto klient = std::make_shared<Klient>("1", "Jan", "Kowalski");
    auto usluga = std::make_shared<TransportStandardowy>("Standard", 100.0, 5.0);
    
    // 1. Zlecenie bez pojazdów -> niegotowe
    Zlecenie z1("Z1", t, klient, usluga, 100.0, 2.0, "B");
    BOOST_CHECK(menedzer.weryfikujGotowoscDoRealizacji(z1) == false);

    // 2. Zlecenie z pojazdem, ale bez kierowcy -> niegotowe
    auto pojazd = std::make_shared<BusDostawczy>("EL12345", 50.0, 10.0);
    z1.dodajPojazd(pojazd);
    BOOST_CHECK(menedzer.weryfikujGotowoscDoRealizacji(z1) == false);

    // 3. Zlecenie z pojazdem i kierowcą bez uprawnień -> niegotowe
    auto kierowcaC = std::make_shared<Kierowca>("2", "Kierowca C", 40.0, std::vector<std::string>{"C"});
    z1.dodajPracownika(kierowcaC);
    BOOST_CHECK(menedzer.weryfikujGotowoscDoRealizacji(z1) == false);

    // 4. Zlecenie w pełni wyposażone -> gotowe
    auto kierowcaB = std::make_shared<Kierowca>("1", "Kierowca B", 30.0, std::vector<std::string>{"B"});
    Zlecenie z2("Z2", t, klient, usluga, 100.0, 2.0, "B");
    z2.dodajPojazd(pojazd);
    z2.dodajPracownika(kierowcaB);
    BOOST_CHECK(menedzer.weryfikujGotowoscDoRealizacji(z2) == true);

    // 5. Zlecenie rozliczone -> niegotowe do realizacji
    z2.rozlicz();
    BOOST_CHECK(menedzer.weryfikujGotowoscDoRealizacji(z2) == false);
}
