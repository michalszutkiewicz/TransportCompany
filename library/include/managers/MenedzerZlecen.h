#ifndef POBI_MENEDZERZLECEN_H
#define POBI_MENEDZERZLECEN_H

#pragma once
#include <memory>

// Forward declarations
class Zlecenie;
class Pojazd;
class Pracownik;

/**
 * @class MenedzerZlecen
 * @brief Odpowiada za koordynację procesu przypisywania zasobów do zleceń transportowych.
 * * Klasa pełni rolę fasady logiki biznesowej, weryfikując spójność danych (uprawnienia,
 * dostępność zasobów) przed zatwierdzeniem zlecenia do realizacji.
 * * @author Michał Szutkiewicz
 * @version 1.0
 */
class MenedzerZlecen {
public:
    /**
     * @brief Domyślny konstruktor menedżera.
     */
    MenedzerZlecen() = default;

    /**
     * @brief Przypisuje pojazd do zlecenia po weryfikacji kompatybilności.
     * * @param z Referencja do zlecenia, które ma zostać obsłużone.
     * @param p Inteligentny wskaźnik do obiektu Pojazd.
     * @return true jeśli przypisanie zakończyło się sukcesem, false w przypadku braku dostępności lub konfliktu.
     */
    bool probaPrzypisaniaPojazdu(Zlecenie& z, std::shared_ptr<Pojazd> p);

    /**
     * @brief Przypisuje pracownika do zlecenia w oparciu o posiadane kwalifikacje.
     * * @param z Referencja do zlecenia.
     * @param pr Inteligentny wskaźnik do obiektu Pracownik.
     * @return true jeśli pracownik został poprawnie powiązany ze zleceniem, false jeśli nie spełnia wymogów.
     */
    bool probaPrzypisaniaPracownika(Zlecenie& z, std::shared_ptr<Pracownik> pr);

    /**
     * @brief Sprawdza, czy zlecenie posiada wszystkie niezbędne zasoby do rozpoczęcia operacji.
     * * Weryfikuje kompletność powiązań między zleceniem a przydzielonym personelem i sprzętem.
     * * @param z Stała referencja do weryfikowanego zlecenia.
     * @return true jeśli zlecenie jest gotowe do statusu "w realizacji", false w przeciwnym razie.
     */
    bool weryfikujGotowoscDoRealizacji(const Zlecenie& z);

    /**
     * @brief Weryfikuje czy dany pracownik posiada uprawnienia do obsługi konkretnego pojazdu.
     * * @param pr Wskaźnik do pracownika.
     * @param p Wskaźnik do pojazdu.
     * @return true jeśli pracownik posiada wymagane uprawnienia, false jeśli brak odpowiednich kwalifikacji.
     */
    bool sprawdzUprawnienia(std::shared_ptr<Pracownik> pr, std::shared_ptr<Pojazd> p);

    /**
     * @brief Sprawdza dostępność wszystkich zasobów wymaganych przez zlecenie w zadanym terminie.
     * * @param z Stała referencja do zlecenia.
     * @return true jeśli wszystkie zasoby są wolne, false jeśli występuje kolizja terminów.
     */
    bool sprawdzDostepnoscZasobow(const Zlecenie& z) const;
};

#endif //POBI_MENEDZERZLECEN_H