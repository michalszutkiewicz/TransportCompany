//
// Created by MichalSw11 on 08.06.2026.
//

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test.hpp>
#include "managers/MenedzerZlecen.h"
#include "repositories/RepozytoriumZlecen.h"
#include "Zlecenie.h"
#include "Klient.h"
#include "TransportStandardowy.h"
#include "BusDostawczy.h"
#include "Kierowca.h"
#include "Termin.h"

BOOST_AUTO_TEST_CASE(ScenariuszPelnyTest) {
    MenedzerZlecen menedzer;
    
    // 1. Utworzenie obiektów
    pt::ptime d1(gr::date(2026, 6, 10), pt::hours(10));
    pt::ptime d2(gr::date(2026, 6, 10), pt::hours(14));
    Termin t(d1, d2);
    
    auto klient = std::make_shared<Klient>("K1", "Jan", "Kowalski");
    auto pojazd = std::make_shared<BusDostawczy>("EL12345", 50.0, 10.0);
    auto pracownik = std::make_shared<Kierowca>("P1", "Adam Nowak", 30.0, std::vector<std::string>{"B"});
    auto usluga = std::make_shared<TransportStandardowy>("Standard", 100.0, 5.0);

    // 2. Utworzenie zlecenia
    Zlecenie zlecenie("Z1", t, klient, usluga, 100.0, 2.0, "B");

    // 3. Użycie MenedzerZlecen do przypisania
    bool pOk = menedzer.probaPrzypisaniaPojazdu(zlecenie, pojazd);
    bool prOk = menedzer.probaPrzypisaniaPracownika(zlecenie, pracownik);
    
    BOOST_CHECK(pOk);
    BOOST_CHECK(prOk);

    // 4. Weryfikacja gotowości
    BOOST_CHECK(menedzer.weryfikujGotowoscDoRealizacji(zlecenie));

    // 5. Rozliczenie
    zlecenie.rozlicz();
    BOOST_CHECK(zlecenie.czyJestRozliczone());
    
    // Status po rozliczeniu
    BOOST_CHECK(menedzer.weryfikujGotowoscDoRealizacji(zlecenie) == false);
}

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

    // Przypisanie pojazdu do z1
    menedzer.probaPrzypisaniaPojazdu(z1, pojazd);
    
    // Próba przypisania tego samego pojazdu do z2 w tym samym terminie
    bool fail = menedzer.probaPrzypisaniaPojazdu(z2, pojazd);
    BOOST_CHECK(fail == false);
}
