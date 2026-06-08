//
// Created by MichalSw11 on 04.06.2026.
//

#ifndef ATOM_PN_1330_06_REPOZYTORIUMPOJAZDOW_H
#define ATOM_PN_1330_06_REPOZYTORIUMPOJAZDOW_H

#pragma once
#include "ISerializowalny.h"
#include "Pojazd.h"
#include <vector>
#include <memory>
#include <functional>
#include <string>

/**
 * @brief Alias dla predykatu filtrującego kolekcję pojazdów.
 */
using PojazdPredykat = std::function<bool(std::shared_ptr<Pojazd>)>;

/**
 * @class RepozytoriumPojazdow
 * @brief Klasa zarządzająca trwałą kolekcją obiektów typu Pojazd w systemie.
 * * Odpowiada za przechowywanie floty pojazdów, obsługę ich cyklu życia w repozytorium
 * oraz zapewnienie metod do filtrowania zasobów według specyficznych kryteriów.
 * @author Michał Szutkiewicz
 * @version 1.0
 */
class RepozytoriumPojazdow : public ISerializowalny {

private:
    std::vector<std::shared_ptr<Pojazd>> elementy; ///< Wewnętrzny kontener floty pojazdów.

public:
    /**
     * @brief Pobiera pojazd o określonym unikalnym identyfikatorze.
     * @param id Ciąg znaków będący identyfikatorem pojazdu.
     * @return Wskaźnik do znalezionego pojazdu lub nullptr, jeśli nie istnieje w repozytorium.
     */
    std::shared_ptr<Pojazd> pobierzPojazd(const std::string& id) const;

    /**
     * @brief Pobiera pojazd z kolekcji na podstawie indeksu w wektorze.
     * @param i Indeks elementu.
     * @return Wskaźnik do pojazdu na danej pozycji.
     */
    std::shared_ptr<Pojazd> pobierzPoIndeksie(int i) const;

    /**
     * @brief Dodaje nowy pojazd do floty zarządzanej przez repozytorium.
     * @param element Inteligentny wskaźnik do obiektu Pojazd.
     */
    void dodajPojazd(std::shared_ptr<Pojazd> element);

    /**
     * @brief Usuwa wskazany pojazd z repozytorium.
     * @param element Wskaźnik do pojazdu, który ma zostać wycofany z kolekcji.
     */
    void usunPojazd(std::shared_ptr<Pojazd> element);

    /**
     * @brief Generuje podsumowanie stanu floty w formie tekstowej.
     * @return Ciąg znaków zawierający statystyki repozytorium.
     */
    std::string raport() const;

    /**
     * @brief Zwraca liczbę wszystkich pojazdów w repozytorium.
     * @return Aktualny rozmiar kontenera.
     */
    int rozmiar() const;

    /**
     * @brief Wyszukuje pojazdy spełniające określone wymagania biznesowe (np. dostępność, typ).
     * @param predykat Funkcja określająca kryteria filtrowania.
     * @return Wektor wskaźników do pojazdów spełniających kryteria.
     */
    std::vector<std::shared_ptr<Pojazd>> znajdzPo(PojazdPredykat predykat) const;

    /**
     * @brief Pobiera pełną listę pojazdów znajdujących się w repozytorium.
     * @return Wektor wszystkich zarejestrowanych pojazdów.
     */
    std::vector<std::shared_ptr<Pojazd>> pobierzWszystkie() const;

    /**
     * @brief Zapisuje stan całego repozytorium pojazdów do pliku.
     * @param sciezka Ścieżka do pliku, w którym zostanie utrwalony stan floty.
     */
    void zapiszStan(const std::string& sciezka) const override;

    /**
     * @brief Wczytuje stan repozytorium pojazdów z pliku.
     * @param sciezka Ścieżka do pliku źródłowego.
     */
    void wczytajStan(const std::string& sciezka) override;

    /**
     * @brief Serializuje stan repozytorium do formatu tekstowego.
     * @return Ciąg znaków reprezentujący zserializowane dane floty.
     */
    std::string serializuj() const override;

    /**
     * @brief Deserializuje dane do stanu obiektu repozytorium.
     * @param dane Dane w formacie tekstowym.
     */
    void deserializuj(const std::string& dane) override;
};

#endif //ATOM_PN_1330_06_REPOZYTORIUMPOJAZDOW_H
