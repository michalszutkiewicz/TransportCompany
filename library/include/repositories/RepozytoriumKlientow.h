//
// Created by MichalSw11 on 04.06.2026.
//

#ifndef ATOM_PN_1330_06_REPOZYTORIUMKLIENTOW_H
#define ATOM_PN_1330_06_REPOZYTORIUMKLIENTOW_H

#pragma once
#include "ISerializowalny.h"
#include "Klient.h"
#include <vector>
#include <memory>
#include <functional>
#include <string>

/** * @brief Alias dla predykatu filtrującego kolekcję klientów.
 */
using KlientPredykat = std::function<bool(std::shared_ptr<Klient>)>;

/**
 * @class RepozytoriumKlientow
 * @brief Klasa zarządzająca trwałą kolekcją obiektów typu Klient w systemie.
 * * Pełni rolę warstwy dostępu do danych, zapewniając operacje CRUD oraz mechanizmy
 * serializacji stanu repozytorium.
 * @author Michał Szutkiewicz
 * @version 1.0
 */
class RepozytoriumKlientow : public ISerializowalny {

private:
    std::vector<std::shared_ptr<Klient>> elementy; ///< Wewnętrzny kontener przechowujący inteligentne wskaźniki do klientów.

public:
    /**
     * @brief Pobiera klienta o określonym identyfikatorze unikalnym.
     * @param id Ciąg znaków reprezentujący ID klienta.
     * @return Wskaźnik do znalezionego klienta lub nullptr, jeśli nie istnieje.
     */
    std::shared_ptr<Klient> pobierzKlienta(const std::string& id) const;

    /**
     * @brief Pobiera klienta z kolekcji na podstawie pozycji w wektorze.
     * @param i Indeks elementu.
     * @return Wskaźnik do klienta na danej pozycji.
     */
    std::shared_ptr<Klient> pobierzPoIndeksie(int i) const;

    /**
     * @brief Dodaje nowego klienta do repozytorium.
     * @param element Inteligentny wskaźnik do dodawanego obiektu Klient.
     */
    void dodajKlienta(std::shared_ptr<Klient> element);

    /**
     * @brief Usuwa wskazanego klienta z kolekcji.
     * @param element Wskaźnik do obiektu, który ma zostać usunięty.
     */
    void usunKlienta(std::shared_ptr<Klient> element);

    /**
     * @brief Generuje podsumowanie stanu repozytorium w formie tekstowej.
     * @return Ciąg znaków z raportem (np. liczba klientów).
     */
    std::string raport() const;

    /**
     * @brief Zwraca liczbę wszystkich zarejestrowanych klientów.
     * @return Aktualny rozmiar kontenera.
     */
    int rozmiar() const;

    /**
     * @brief Wyszukuje klientów spełniających zadane kryterium.
     * @param predykat Funkcja lambda lub wskaźnik do funkcji określający warunek wyszukiwania.
     * @return Wektor wskaźników do klientów spełniających predykat.
     */
    std::vector<std::shared_ptr<Klient>> znajdzPo(KlientPredykat predykat) const;

    /**
     * @brief Zwraca kopię listy wszystkich klientów znajdujących się w repozytorium.
     * @return Wektor inteligentnych wskaźników.
     */
    std::vector<std::shared_ptr<Klient>> pobierzWszystkie() const;

    /**
     * @brief Zapisuje stan całego repozytorium do zewnętrznego pliku.
     * @param sciezka Ścieżka do pliku docelowego.
     */
    void zapiszStan(const std::string& sciezka) const override;

    /**
     * @brief Wczytuje stan repozytorium z pliku zewnętrznego.
     * @param sciezka Ścieżka do pliku źródłowego.
     */
    void wczytajStan(const std::string& sciezka) override;

    /**
     * @brief Konwertuje stan obiektu do formatu szeregowego (np. JSON/XML).
     * @return Ciąg znaków reprezentujący zserializowane dane.
     */
    std::string serializuj() const override;

    /**
     * @brief Odtwarza stan obiektu z surowych danych wejściowych.
     * @param dane Dane w formacie tekstowym do deserializacji.
     */
    void deserializuj(const std::string& dane) override;
};

#endif //ATOM_PN_1330_06_REPOZYTORIUMKLIENTOW_H