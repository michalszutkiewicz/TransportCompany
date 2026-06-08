//
// Created by Kinga Ratajska on 15/04/2026.
//

#ifndef ATOM_PN_1330_06_INTERFEJS_H
#define ATOM_PN_1330_06_INTERFEJS_H

#pragma once
#include "repositories/RepozytoriumKlientow.h"
#include "repositories/RepozytoriumPojazdow.h"
#include "repositories/RepozytoriumPracownikow.h"
#include "repositories/RepozytoriumZlecen.h"

/**
 * @class InterfejsUI
 * @brief Główna klasa zarządzająca interfejsem użytkownika i przepływem aplikacji.
 * * Klasa integruje wszystkie repozytoria danych, obsługuje pętlę zdarzeń aplikacji
 * oraz zapewnia zestaw metod do nawigacji po menu i zarządzania zasobami systemu.
 * @author Kinga Ratajska
 * @version 1.0
 */
class InterfejsUI {
private:
    RepozytoriumKlientow repoKlienci;       ///< Repozytorium przechowujące dane klientów.
    RepozytoriumPojazdow repoPojazdy;       ///< Repozytorium przechowujące flotę pojazdów.
    RepozytoriumPracownikow repoPracownicy; ///< Repozytorium przechowujące kadrę pracowniczą.
    RepozytoriumZlecen repoZlecenia;        ///< Repozytorium przechowujące zlecenia transportowe.

public:
    /**
     * @brief Inicjalizuje interfejs użytkownika i przygotowuje strukturę danych.
     */
    InterfejsUI();

    /**
     * @brief Uruchamia główną pętlę aplikacji, oczekując na komendy użytkownika.
     */
    void uruchom();

    /**
     * @brief Wyświetla główne menu systemu w konsoli.
     */
    void wyswietlMenu();

    /**
     * @brief Inicjuje proces tworzenia nowego zlecenia, prowadząc użytkownika przez wymagane kroki.
     */
    void obsluzKreatorZlecenia();

    /**
     * @brief Obsługuje podmenu służące do dodawania nowych zasobów do systemu.
     */
    void menuDodajZasob();

    /**
     * @brief Obsługuje podmenu służące do przeglądania danych zapisanych w repozytoriach.
     */
    void menuPokazDane();

    /**
     * @brief Interaktywne dodawanie nowego pracownika do bazy kadr.
     */
    void dodajPracownika();

    /**
     * @brief Interaktywne dodawanie nowego pojazdu do floty.
     */
    void dodajPojazd();

    /**
     * @brief Interaktywne dodawanie nowego klienta do bazy.
     */
    void dodajKlienta();

    /**
     * @brief Wyświetla listę wszystkich zarejestrowanych zleceń.
     */
    void pokazZlecenia();

    /**
     * @brief Wyświetla listę wszystkich zarejestrowanych pracowników.
     */
    void pokazPracownikow();

    /**
     * @brief Wyświetla listę floty pojazdów.
     */
    void pokazPojazdy();

    /**
     * @brief Wyświetla listę zarejestrowanych klientów.
     */
    void pokazKlientow();

    /**
     * @brief Persystuje stan wszystkich repozytoriów systemu do pliku.
     * @param sciezka Ścieżka do pliku, w którym zostaną zapisane dane.
     */
    void zapiszStanSystemu(const std::string& sciezka);

    /**
     * @brief Wczytuje stan systemu z zewnętrznego pliku.
     * @param sciezka Ścieżka do pliku źródłowego z danymi.
     */
    void wczytajStanSystemu(const std::string& sciezka);
};

#endif //ATOM_PN_1330_06_INTERFEJS_H
