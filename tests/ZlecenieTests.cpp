/**
 * @file ZlecenieTests.cpp
 * @brief Testy jednostkowe klasy Zlecenie.
 * * Testy sprawdzają poprawność obliczeń finansowych, mechanizmy przypisywania
 * zasobów (pojazdów i pracowników) oraz poprawność określania statusu zlecenia
 * w zależności od czasu.
 */

#include <boost/test/unit_test.hpp>
#include "Zlecenie.h"
#include "Klient.h"
#include "TransportStandardowy.h"
#include "BusDostawczy.h"
#include "Kierowca.h"
#include "Termin.h"

/**
 * @brief Testuje logikę obliczania kosztów zlecenia.
 * * Weryfikuje:
 * - Poprawność obliczeń dla zleceń z przypisaną usługą.
 * - Zachowanie systemu w przypadku braku przypisanej usługi (zwracanie kosztu 0.0).
 */
BOOST_AUTO_TEST_CASE(ObliczanieKosztuTest) {
    pt::ptime d1(gr::date(2026, 6, 10), pt::hours(10));
    pt::ptime d2(gr::date(2026, 6, 10), pt::hours(14));
    Termin t(d1, d2);
    auto klient = std::make_shared<Klient>("1", "Jan", "Kowalski");
    auto usluga = std::make_shared<TransportStandardowy>("Standard", 100.0, 5.0); // 100km * 5.0 = 500.0

    Zlecenie zlecenie("Z1", t, klient, usluga, 100.0, 2.0, "B");

    BOOST_CHECK_CLOSE(zlecenie.obliczPelnyKoszt(), 500.0, 0.001);

    // Test przypadku braku usługi
    Zlecenie zlecenieBezUslugi("Z2", t, klient, nullptr, 100.0, 2.0, "B");
    BOOST_CHECK_EQUAL(zlecenieBezUslugi.obliczPelnyKoszt(), 0.0);
}

/**
 * @brief Testuje zarządzanie zasobami przypisanymi do zlecenia.
 * * Weryfikuje:
 * - Prawidłowe dodawanie pojazdów i pracowników.
 * - Mechanizm rezerwacji terminów (czy zasoby są oznaczane jako zajęte).
 * - Odporność na dodawanie pustych (nullptr) wskaźników.
 */
BOOST_AUTO_TEST_CASE(ZarzadzanieZasobamiTest) {
    pt::ptime d1(gr::date(2026, 6, 10), pt::hours(10));
    pt::ptime d2(gr::date(2026, 6, 10), pt::hours(14));
    Termin t(d1, d2);
    auto klient = std::make_shared<Klient>("1", "Jan", "Kowalski");
    auto usluga = std::make_shared<TransportStandardowy>("Standard", 100.0, 5.0);
    Zlecenie zlecenie("Z1", t, klient, usluga, 100.0, 2.0, "B");

    auto pojazd = std::make_shared<BusDostawczy>("EL12345", 50.0, 10.0);
    auto kierowca = std::make_shared<Kierowca>("12345678901", "Adam Nowak", 30.0, std::vector<std::string>{"B"});

    zlecenie.dodajPojazd(pojazd);
    zlecenie.dodajPracownika(kierowca);

    BOOST_CHECK_EQUAL(zlecenie.pobierzPojazdy().size(), 1);
    BOOST_CHECK_EQUAL(zlecenie.pobierzPracownicy().size(), 1);
    BOOST_CHECK_EQUAL(zlecenie.pobierzPojazdy()[0], pojazd);
    BOOST_CHECK_EQUAL(zlecenie.pobierzPracownicy()[0], kierowca);

    // Weryfikacja odporności na nullptr
    zlecenie.dodajPojazd(nullptr);
    zlecenie.dodajPracownika(nullptr);
    BOOST_CHECK_EQUAL(zlecenie.pobierzPojazdy().size(), 1);
    BOOST_CHECK_EQUAL(zlecenie.pobierzPracownicy().size(), 1);

    // Weryfikacja, czy zasoby zostały poprawnie zarezerwowane w terminie t
    BOOST_CHECK(pojazd->czyDostepny(t) == false);
    BOOST_CHECK(kierowca->czyDostepny(t) == false);
}

/**
 * @brief Testuje logikę statusów oraz rozliczania zlecenia.
 * * Sprawdza:
 * - Poprawne określanie statusu ("OCZEKUJĄCE", "ZAKOŃCZONE", "ROZLICZONE").
 * - Zmianę stanu zlecenia po wywołaniu metody rozlicz().
 */
BOOST_AUTO_TEST_CASE(StatusIRozliczanieTest) {
    auto klient = std::make_shared<Klient>("1", "Jan", "Kowalski");
    auto usluga = std::make_shared<TransportStandardowy>("Standard", 100.0, 5.0);

    // Status OCZEKUJĄCE (termin w dalekiej przyszłości)
    Termin tPrzyszly(pt::ptime(gr::date(2099, 1, 1)), pt::ptime(gr::date(2099, 1, 2)));
    Zlecenie z1("Z1", tPrzyszly, klient, usluga, 100.0, 2.0, "B");
    BOOST_CHECK_EQUAL(z1.pobierzStatus(), "OCZEKUJĄCE");

    // Status ZAKOŃCZONE (termin w dalekiej przeszłości)
    Termin tPrzeszly(pt::ptime(gr::date(1999, 1, 1)), pt::ptime(gr::date(1999, 1, 2)));
    Zlecenie z2("Z2", tPrzeszly, klient, usluga, 100.0, 2.0, "B");
    BOOST_CHECK_EQUAL(z2.pobierzStatus(), "ZAKOŃCZONE (oczekuje na rozliczenie)");

    // Rozliczanie i status ROZLICZONE
    BOOST_CHECK_EQUAL(z2.czyJestRozliczone(), false);
    z2.rozlicz();
    BOOST_CHECK_EQUAL(z2.czyJestRozliczone(), true);
    BOOST_CHECK_EQUAL(z2.pobierzStatus(), "ROZLICZONE");
}