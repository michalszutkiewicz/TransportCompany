/**
 * @file RepozytoriumTests.cpp
 * @brief Testy jednostkowe klas repozytoriów.
 * * Testy weryfikują poprawność operacji na kolekcjach, mechanizmy
 * wyszukiwania oparte na predykatach oraz poprawność zapisu i odczytu stanu do plików.
 */

#include <boost/test/unit_test.hpp>
#include "repositories/RepozytoriumKlientow.h"
#include "repositories/RepozytoriumPojazdow.h"
#include "repositories/RepozytoriumPracownikow.h"
#include "Klient.h"
#include "BusDostawczy.h"
#include "Kierowca.h"
#include <fstream>

/**
 * @brief Testuje podstawowe operacje CRUD (Create, Read, Delete) w repozytorium klientów.
 */
BOOST_AUTO_TEST_CASE(RepozytoriumCRUDTest) {
    RepozytoriumKlientow repo;
    auto k1 = std::make_shared<Klient>("1", "Jan", "Kowalski");
    auto k2 = std::make_shared<Klient>("2", "Anna", "Nowak");

    // Test Create
    repo.dodajKlienta(k1);
    repo.dodajKlienta(k2);
    BOOST_CHECK_EQUAL(repo.rozmiar(), 2);

    // Test Read
    BOOST_CHECK_EQUAL(repo.pobierzKlienta("1"), k1);
    BOOST_CHECK_EQUAL(repo.pobierzKlienta("3"), nullptr);
    BOOST_CHECK_EQUAL(repo.pobierzPoIndeksie(0), k1);

    // Test Delete
    repo.usunKlienta(k1);
    BOOST_CHECK_EQUAL(repo.rozmiar(), 1);
    BOOST_CHECK_EQUAL(repo.pobierzKlienta("1"), nullptr);
}

/**
 * @brief Testuje wyszukiwanie w repozytorium pracowników za pomocą predykatów.
 * * Sprawdza poprawność filtrowania danych według określonych kryteriów biznesowych
 * (np. wysokość stawki godzinowej).
 */
BOOST_AUTO_TEST_CASE(RepozytoriumWyszukiwanieTest) {
    RepozytoriumPracownikow repo;
    auto p1 = std::make_shared<Kierowca>("1", "Adam", 30.0, std::vector<std::string>{"B"});
    auto p2 = std::make_shared<Kierowca>("2", "Ewa", 50.0, std::vector<std::string>{"C"});
    repo.dodajPracownika(p1);
    repo.dodajPracownika(p2);

    // Wyszukiwanie pracowników ze stawką > 40.0
    auto wynik = repo.znajdzPo([](std::shared_ptr<Pracownik> p) {
        return p->pobierzStawke() > 40.0;
    });
    BOOST_CHECK_EQUAL(wynik.size(), 1);
    BOOST_CHECK_EQUAL(wynik[0], p2);

    // Wyszukiwanie pracownika, który nie istnieje
    auto wynik2 = repo.znajdzPo([](std::shared_ptr<Pracownik> p) {
        return p->pobierzImieNazwisko() == "Zenon";
    });
    BOOST_CHECK_EQUAL(wynik2.size(), 0);
}

/**
 * @brief Testuje serializację i deserializację stanu repozytorium pojazdów.
 * * Weryfikuje, czy po zapisie do pliku i ponownym wczytaniu,
 * struktura i zawartość repozytorium pozostają niezmienione.
 */
BOOST_AUTO_TEST_CASE(RepozytoriumSerializacjaTest) {
    RepozytoriumPojazdow repo;
    repo.dodajPojazd(std::make_shared<BusDostawczy>("EL1", 10.0, 5.0));
    repo.dodajPojazd(std::make_shared<BusDostawczy>("EL2", 20.0, 10.0));

    std::string testFile = "repo_test.txt";
    repo.zapiszStan(testFile);

    // Wczytanie do nowego repozytorium
    RepozytoriumPojazdow repo2;
    repo2.wczytajStan(testFile);

    // Weryfikacja spójności danych
    BOOST_CHECK_EQUAL(repo2.rozmiar(), 2);

    // Sprzątanie pliku tymczasowego
    std::remove(testFile.c_str());
}