#ifndef ATOM_PN_1330_06_REPOZYTORIUMPRACOWNIKOW_H
#define ATOM_PN_1330_06_REPOZYTORIUMPRACOWNIKOW_H

#pragma once
#include "ISerializowalny.h"
#include "Pracownik.h"
#include <vector>
#include <memory>
#include <functional>
#include <string>

/**
 * @brief Alias dla predykatu filtrującego kolekcję pracowników.
 */
using PracownikPredykat = std::function<bool(std::shared_ptr<Pracownik>)>;

/**
 * @class RepozytoriumPracownikow
 * @brief Klasa zarządzająca trwałą kolekcją obiektów typu Pracownik w systemie.
 * * Odpowiada za utrzymywanie bazy personelu, oferując funkcje wyszukiwania kwalifikacji
 * oraz obsługę operacji zapisu i odczytu stanu bazy pracowników.
 * @author Michał Szutkiewicz
 * @version 1.0
 */
class RepozytoriumPracownikow : public ISerializowalny {

private:
    std::vector<std::shared_ptr<Pracownik>> elementy; ///< Wewnętrzny kontener przechowujący personel.

public:
    /**
     * @brief Pobiera pracownika o określonym unikalnym identyfikatorze.
     * @param id Ciąg znaków będący ID pracownika.
     * @return Wskaźnik do obiektu Pracownik lub nullptr, jeśli nie istnieje.
     */
    std::shared_ptr<Pracownik> pobierzPracownik(const std::string& id) const;

    /**
     * @brief Pobiera pracownika z kolekcji na podstawie jego pozycji w wektorze.
     * @param i Indeks elementu.
     * @return Wskaźnik do pracownika na danej pozycji.
     */
    std::shared_ptr<Pracownik> pobierzPoIndeksie(int i) const;

    /**
     * @brief Dodaje nowego pracownika do zasobów kadrowych systemu.
     * @param element Inteligentny wskaźnik do obiektu Pracownik.
     */
    void dodajPracownika(std::shared_ptr<Pracownik> element);

    /**
     * @brief Usuwa wskazanego pracownika z repozytorium.
     * @param element Wskaźnik do pracownika, który ma zostać usunięty.
     */
    void usunPracownika(std::shared_ptr<Pracownik> element);

    /**
     * @brief Generuje podsumowanie stanu kadrowego w formie tekstowej.
     * @return Ciąg znaków z raportem o liczbie i statusie pracowników.
     */
    std::string raport() const;

    /**
     * @brief Zwraca liczbę wszystkich pracowników zarejestrowanych w systemie.
     * @return Aktualny rozmiar kontenera.
     */
    int rozmiar() const;

    /**
     * @brief Wyszukuje pracowników spełniających określone warunki (np. dostępność, uprawnienia).
     * @param predykat Funkcja określająca kryteria filtrowania.
     * @return Wektor wskaźników do pracowników spełniających predykat.
     */
    std::vector<std::shared_ptr<Pracownik>> znajdzPo(PracownikPredykat predykat) const;

    /**
     * @brief Pobiera pełną listę wszystkich pracowników znajdujących się w repozytorium.
     * @return Wektor inteligentnych wskaźników do wszystkich pracowników.
     */
    std::vector<std::shared_ptr<Pracownik>> pobierzWszystkie() const;

    /**
     * @brief Zapisuje stan całego repozytorium pracowników do pliku.
     * @param sciezka Ścieżka do pliku docelowego.
     */
    void zapiszStan(const std::string& sciezka) const override;

    /**
     * @brief Wczytuje stan repozytorium pracowników z pliku zewnętrznego.
     * @param sciezka Ścieżka do pliku źródłowego.
     */
    void wczytajStan(const std::string& sciezka) override;

    /**
     * @brief Serializuje stan repozytorium do formatu tekstowego.
     * @return Ciąg znaków reprezentujący zserializowane dane kadr.
     */
    std::string serializuj() const override;

    /**
     * @brief Odtwarza stan obiektu z surowych danych wejściowych.
     * @param dane Dane w formacie tekstowym do deserializacji.
     */
    void deserializuj(const std::string& dane) override;
};

#endif //ATOM_PN_1330_06_REPOZYTORIUMPRACOWNIKOW_H