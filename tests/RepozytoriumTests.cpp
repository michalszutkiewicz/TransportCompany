//
// Created by MichalSw11 on 08.06.2026.
//

#include <boost/test/unit_test.hpp>
#include "repositories/RepozytoriumKlientow.h"
#include "repositories/RepozytoriumPojazdow.h"
#include "repositories/RepozytoriumPracownikow.h"
#include "Klient.h"
#include "BusDostawczy.h"
#include "Kierowca.h"
#include <fstream>

BOOST_AUTO_TEST_CASE(RepozytoriumCRUDTest) {
    RepozytoriumKlientow repo;
    auto k1 = std::make_shared<Klient>("1", "Jan", "Kowalski");
    auto k2 = std::make_shared<Klient>("2", "Anna", "Nowak");

    // Create
    repo.dodajKlienta(k1);
    repo.dodajKlienta(k2);
    BOOST_CHECK_EQUAL(repo.rozmiar(), 2);

    // Read
    BOOST_CHECK_EQUAL(repo.pobierzKlienta("1"), k1);
    BOOST_CHECK_EQUAL(repo.pobierzKlienta("3"), nullptr);
    BOOST_CHECK_EQUAL(repo.pobierzPoIndeksie(0), k1);

    // Delete
    repo.usunKlienta(k1);
    BOOST_CHECK_EQUAL(repo.rozmiar(), 1);
    BOOST_CHECK_EQUAL(repo.pobierzKlienta("1"), nullptr);
}

BOOST_AUTO_TEST_CASE(RepozytoriumWyszukiwanieTest) {
    RepozytoriumPracownikow repo;
    auto p1 = std::make_shared<Kierowca>("1", "Adam", 30.0, std::vector<std::string>{"B"});
    auto p2 = std::make_shared<Kierowca>("2", "Ewa", 50.0, std::vector<std::string>{"C"});
    repo.dodajPracownika(p1);
    repo.dodajPracownika(p2);

    // Wyszukiwanie po stawce
    auto wynik = repo.znajdzPo([](std::shared_ptr<Pracownik> p) {
        return p->pobierzStawke() > 40.0;
    });
    BOOST_CHECK_EQUAL(wynik.size(), 1);
    BOOST_CHECK_EQUAL(wynik[0], p2);

    // Wyszukiwanie brakujące
    auto wynik2 = repo.znajdzPo([](std::shared_ptr<Pracownik> p) {
        return p->pobierzImieNazwisko() == "Zenon";
    });
    BOOST_CHECK_EQUAL(wynik2.size(), 0);
}

BOOST_AUTO_TEST_CASE(RepozytoriumSerializacjaTest) {
    RepozytoriumPojazdow repo;
    repo.dodajPojazd(std::make_shared<BusDostawczy>("EL1", 10.0, 5.0));
    repo.dodajPojazd(std::make_shared<BusDostawczy>("EL2", 20.0, 10.0));

    std::string testFile = "repo_test.txt";
    repo.zapiszStan(testFile);

    RepozytoriumPojazdow repo2;
    repo2.wczytajStan(testFile);

    // Weryfikacja rozmiaru
    BOOST_CHECK_EQUAL(repo2.rozmiar(), 2);
    
    // Sprzątanie
    std::remove(testFile.c_str());
}
