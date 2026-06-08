//
// Created by MichalSw11 on 08.06.2026.
//

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test.hpp>
#include "managers/MenedzerZlecen.h"
#include "Zlecenie.h"
#include "Klient.h"
#include "TransportStandardowy.h"
#include "BusDostawczy.h"
#include "Ciezarowka.h"
#include "Kierowca.h"
#include "Termin.h"

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

    // Poprawne przypisanie pojazdu
    BOOST_CHECK(menedzer.probaPrzypisaniaPojazdu(zlecenie, pojazd) == true);
    
    // Próba przypisania tego samego pojazdu (zajęty)
    Zlecenie zlecenie2("Z2", t, klient, usluga, 50.0, 1.0, "B");
    BOOST_CHECK(menedzer.probaPrzypisaniaPojazdu(zlecenie2, pojazd) == false);

    // Przypisanie pracownika z odpowiednimi uprawnieniami
    BOOST_CHECK(menedzer.probaPrzypisaniaPracownika(zlecenie, kierowcaB) == true);

    // Przypisanie pracownika bez uprawnień do pojazdu B (kierowca C ma tylko C)
    Zlecenie zlecenie3("Z3", t, klient, usluga, 1000.0, 20.0, "C");
    auto ciezarowka = std::make_shared<Ciezarowka>("EL99999", 100.0, 20.0, true);
    menedzer.probaPrzypisaniaPojazdu(zlecenie3, ciezarowka);
    
    // SprawdzUprawnienia
    BOOST_CHECK(menedzer.sprawdzUprawnienia(kierowcaC, ciezarowka) == true);
    BOOST_CHECK(menedzer.sprawdzUprawnienia(kierowcaB, ciezarowka) == false);
}

BOOST_AUTO_TEST_CASE(WeryfikujGotowoscTest) {
    MenedzerZlecen menedzer;
    pt::ptime d1(gr::date(2026, 6, 10), pt::hours(10));
    pt::ptime d2(gr::date(2026, 6, 10), pt::hours(14));
    Termin t(d1, d2);
    auto klient = std::make_shared<Klient>("1", "Jan", "Kowalski");
    auto usluga = std::make_shared<TransportStandardowy>("Standard", 100.0, 5.0);
    
    // 1. Zlecenie bez pojazdów
    Zlecenie z1("Z1", t, klient, usluga, 100.0, 2.0, "B");
    BOOST_CHECK(menedzer.weryfikujGotowoscDoRealizacji(z1) == false);

    // 2. Zlecenie z pojazdem, ale bez kierowcy
    auto pojazd = std::make_shared<BusDostawczy>("EL12345", 50.0, 10.0);
    z1.dodajPojazd(pojazd);
    BOOST_CHECK(menedzer.weryfikujGotowoscDoRealizacji(z1) == false);

    // 3. Zlecenie z pojazdem i kierowcą bez uprawnień
    auto kierowcaC = std::make_shared<Kierowca>("2", "Kierowca C", 40.0, std::vector<std::string>{"C"});
    z1.dodajPracownika(kierowcaC);
    BOOST_CHECK(menedzer.weryfikujGotowoscDoRealizacji(z1) == false);

    // 4. Zlecenie w pełni wyposażone
    auto kierowcaB = std::make_shared<Kierowca>("1", "Kierowca B", 30.0, std::vector<std::string>{"B"});
    Zlecenie z2("Z2", t, klient, usluga, 100.0, 2.0, "B");
    z2.dodajPojazd(pojazd);
    z2.dodajPracownika(kierowcaB);
    BOOST_CHECK(menedzer.weryfikujGotowoscDoRealizacji(z2) == true);

    // 5. Zlecenie rozliczone (nie powinno być gotowe do realizacji wg opisu)
    z2.rozlicz();
    BOOST_CHECK(menedzer.weryfikujGotowoscDoRealizacji(z2) == false);
}
