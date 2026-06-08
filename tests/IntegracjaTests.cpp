/**
* @file IntegracjaTests.cpp
 * @brief Testy integracyjne systemu zarządzania transportem.
 * * Testy sprawdzają poprawność współpracy między MenedzeremZlecen,
 * Repozytoriami, Zleceniami oraz klasami zasobów (Pojazd, Pracownik).
 */

#include <boost/test/unit_test.hpp>
#include "managers/MenedzerZlecen.h"
#include "repositories/RepozytoriumZlecen.h"
#include "Zlecenie.h"
#include "Klient.h"
#include "TransportStandardowy.h"
#include "BusDostawczy.h"
#include "Kierowca.h"
#include "Termin.h"
#include "Exceptions.h"

/**
 * @brief Scenariusz pełnego cyklu życia zlecenia.
 * * Weryfikuje poprawne przypisanie zasobów, walidację gotowości
 * do realizacji oraz proces rozliczenia zlecenia.
 */
BOOST_AUTO_TEST_CASE(ScenariuszPelnyTest) {
    MenedzerZlecen menedzer;
    
    // Inicjalizacja terminów i zasobów
    pt::ptime d1(gr::date(2026, 6, 10), pt::hours(10));
    pt::ptime d2(gr::date(2026, 6, 10), pt::hours(14));
    Termin t(d1, d2);
    
    auto klient = std::make_shared<Klient>("K1", "Jan", "Kowalski");
    auto pojazd = std::make_shared<BusDostawczy>("EL12345", 50.0, 10.0);
    auto pracownik = std::make_shared<Kierowca>("P1", "Adam Nowak", 30.0, std::vector<std::string>{"B"});
    auto usluga = std::make_shared<TransportStandardowy>("Standard", 100.0, 5.0);

    // Utworzenie zlecenia
    Zlecenie zlecenie("Z1", t, klient, usluga, 100.0, 2.0, "B");

    // Przypisanie zasobów przez menedżera
    bool pOk = menedzer.probaPrzypisaniaPojazdu(zlecenie, pojazd);
    bool prOk = menedzer.probaPrzypisaniaPracownika(zlecenie, pracownik);
    
    BOOST_CHECK(pOk);
    BOOST_CHECK(prOk);

    // Weryfikacja gotowości
    BOOST_CHECK(menedzer.weryfikujGotowoscDoRealizacji(zlecenie));

    // Rozliczenie i sprawdzenie statusu
    zlecenie.rozlicz();
    BOOST_CHECK(zlecenie.czyJestRozliczone());
    
    // Weryfikacja: Rozliczone zlecenie nie powinno być ponownie "gotowe do realizacji"
    BOOST_CHECK(menedzer.weryfikujGotowoscDoRealizacji(zlecenie) == false);
}

/**
 * @brief Scenariusz niepowodzenia przypisania zasobu (kolizja terminów).
 * * Weryfikuje, czy menedżer poprawnie blokuje przypisanie pojazdu,
 * który jest już zajęty w danym terminie przez inne zlecenie.
 */
BOOST_AUTO_TEST_CASE(ScenariuszNiepowodzeniaTest) {
    MenedzerZlecen menedzer;
    
    pt::ptime d1(gr::date(2026, 6, 10), pt::hours(10));
    pt::ptime d2(gr::date(2026, 6, 10), pt::hours(14));
    Termin t(d1, d2);
    
    auto klient = std::make_shared<Klient>("K1", "Jan", "Kowalski");
    auto pojazd = std::make_shared<BusDostawczy>("EL12345", 50.0, 10.0);
    auto usluga = std::make_shared<TransportStandardowy>("Standard", 100.0, 5.0);

    Zlecenie z1("Z1", t, klient, usluga, 100.0, 2.0, "B");
    Zlecenie z2("Z2", t, klient, usluga, 100.0, 2.0, "B");

    // Pierwsze przypisanie poprawne
    menedzer.probaPrzypisaniaPojazdu(z1, pojazd);
    
    // Sprawdzenie wyrzucenia wyjątku dla kolizji czasowej
    BOOST_CHECK_THROW(menedzer.probaPrzypisaniaPojazdu(z2, pojazd), ResourceUnavailableException);
}
