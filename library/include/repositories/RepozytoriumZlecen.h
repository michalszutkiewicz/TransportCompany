//
// Created by MichalSw11 on 04.06.2026.
//

#ifndef ATOM_PN_1330_06_REPOZYTORIUMZLECEN_H
#define ATOM_PN_1330_06_REPOZYTORIUMZLECEN_H

#pragma once
#include "ISerializowalny.h"
#include "Zlecenie.h"
#include <vector>
#include <memory>
#include <functional>
#include <string>
#include "Usluga.h"

class RepozytoriumKlientow;
class RepozytoriumPojazdow;
class RepozytoriumPracownikow;

/**
 * @brief Alias dla predykatu filtrującego kolekcję zleceń.
 */
using ZleceniePredykat = std::function<bool(std::shared_ptr<Zlecenie>)>;

/**
 * @class RepozytoriumZlecen
 * @brief Klasa zarządzająca trwałą kolekcją obiektów typu Zlecenie.
 * * Pełni kluczową rolę w systemie, integrując dane z innych repozytoriów (Klientów, Pojazdów, Pracowników)
 * w celu odtworzenia pełnego stanu realizacji zleceń.
 * @author Michał Szutkiewicz
 * @version 1.0
 */
class RepozytoriumZlecen : public ISerializowalny {

private:
    std::vector<std::shared_ptr<Zlecenie>> elementy; ///< Wewnętrzny kontener przechowujący zlecenia.

public:
    /**
     * @brief Pobiera zlecenie o określonym unikalnym identyfikatorze.
     * @param id Ciąg znaków będący ID zlecenia.
     * @return Wskaźnik do obiektu Zlecenie lub nullptr, jeśli nie istnieje.
     */
    std::shared_ptr<Zlecenie> pobierzZlecenie(const std::string& id) const;

    /**
     * @brief Pobiera zlecenie z kolekcji na podstawie jego pozycji w wektorze.
     * @param i Indeks elementu.
     * @return Wskaźnik do zlecenia na danej pozycji.
     */
    std::shared_ptr<Zlecenie> pobierzPoIndeksie(int i) const;

    /**
     * @brief Dodaje nowe zlecenie do systemu.
     * @param element Inteligentny wskaźnik do obiektu Zlecenie.
     */
    void dodajZlecenie(std::shared_ptr<Zlecenie> element);

    /**
     * @brief Usuwa wskazane zlecenie z repozytorium.
     * @param element Wskaźnik do zlecenia, które ma zostać usunięte.
     */
    void usunZlecenie(std::shared_ptr<Zlecenie> element);

    /**
     * @brief Generuje raport ze stanu zleceń (np. liczby zleceń w poszczególnych statusach).
     * @return Ciąg znaków z podsumowaniem pracy systemu.
     */
    std::string raport() const;

    /**
     * @brief Zwraca liczbę wszystkich zleceń w systemie.
     * @return Aktualny rozmiar kontenera.
     */
    int rozmiar() const;

    /**
     * @brief Wyszukuje zlecenia spełniające określone kryteria biznesowe.
     * @param predykat Funkcja określająca kryteria filtrowania.
     * @return Wektor wskaźników do zleceń spełniających predykat.
     */
    std::vector<std::shared_ptr<Zlecenie>> znajdzPo(ZleceniePredykat predykat) const;

    /**
     * @brief Pobiera pełną listę wszystkich zarejestrowanych zleceń.
     * @return Wektor inteligentnych wskaźników do zleceń.
     */
    std::vector<std::shared_ptr<Zlecenie>> pobierzWszystkie() const;

    /**
     * @brief Zapisuje stan repozytorium zleceń do pliku.
     * @param sciezka Ścieżka do pliku docelowego.
     */
    void zapiszStan(const std::string& sciezka) const override;

    /**
     * @brief Podstawowa metoda wczytywania stanu (może wymagać pełnej rekonfiguracji powiązań).
     * @param sciezka Ścieżka do pliku źródłowego.
     */
    void wczytajStan(const std::string& sciezka) override;

    /**
     * @brief Rozszerzona metoda wczytywania stanu, integrująca dane z innymi repozytoriami.
     * * Służy do poprawnego przypisania obiektów (klientów, pojazdów, pracowników) do zleceń
     * podczas odczytu danych z zewnętrznego źródła.
     * @param sciezka Ścieżka do pliku danych.
     * @param rKlienci Referencja do repozytorium klientów.
     * @param rPojazdy Referencja do repozytorium pojazdów.
     * @param rPracownicy Referencja do repozytorium pracowników.
     */
    void wczytajStan(const std::string& sciezka,
                     RepozytoriumKlientow& rKlienci,
                     RepozytoriumPojazdow& rPojazdy,
                     RepozytoriumPracownikow& rPracownicy);

    /**
     * @brief Serializuje stan repozytorium zleceń.
     * @return Ciąg znaków reprezentujący zserializowane dane.
     */
    std::string serializuj() const override;

    /**
     * @brief Odtwarza stan obiektu z surowych danych wejściowych.
     * @param dane Dane w formacie tekstowym do deserializacji.
     */
    void deserializuj(const std::string& dane) override;
};

#endif //ATOM_PN_1330_06_REPOZYTORIUMZLECEN_H
