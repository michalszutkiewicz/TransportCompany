#ifndef ATOM_PN_1330_06_KIEROWCA_H
#define ATOM_PN_1330_06_KIEROWCA_H

#pragma once
#include <string>
#include <vector>
#include "Pracownik.h"

/**
 * @class Kierowca
 * @brief Klasa reprezentująca pracownika pełniącego rolę kierowcy.
 * * Rozszerza klasę Pracownik o listę posiadanych uprawnień (kategorii prawa jazdy),
 * co umożliwia automatyczną weryfikację możliwości obsługi konkretnych pojazdów.
 * @author Michał Szutkiewicz
 * @version 1.0
 */
class Kierowca : public Pracownik {
private:
    std::vector<std::string> kategoriePrawaJazdy; ///< Lista kategorii prawa jazdy posiadanych przez kierowcę.

public:
    /**
     * @brief Konstruktor obiektu Kierowca.
     * @param pesel Unikalny identyfikator PESEL pracownika.
     * @param imieNazwisko Imię i nazwisko kierowcy.
     * @param stawkaGodzinowa Wynagrodzenie za godzinę pracy.
     * @param kategorie Wektor posiadanych kategorii prawa jazdy.
     */
    Kierowca(std::string pesel, std::string imieNazwisko, double stawkaGodzinowa, std::vector<std::string> kategorie);

    /**
     * @brief Sprawdza, czy kierowca posiada kwalifikacje do realizacji zlecenia.
     * * Weryfikacja następuje poprzez porównanie wymagań zlecenia z posiadanymi kategoriami.
     * @param z Stała referencja do zlecenia.
     * @return true jeśli kierowca spełnia wymogi, false w przeciwnym razie.
     */
    bool czyUmieWykonacZlecenie(const Zlecenie& z) const override;

    /**
     * @brief Weryfikuje czy kierowca posiada konkretną kategorię prawa jazdy.
     * @param wymaganaKategoria Kategoria wymagana do obsługi pojazdu.
     * @return true jeśli kierowca posiada wskazaną kategorię, false w przeciwnym razie.
     */
    bool mozeWykonacPrace(std::string wymaganaKategoria) const override;

    /**
     * @brief Zwraca nazwę roli pełnionej przez pracownika.
     * @return Stała tekstowa "Kierowca".
     */
    std::string pobierzRole() const override;

    /**
     * @brief Zwraca pełne dane o pracowniku, w tym informacje o uprawnieniach.
     * @return Sformatowany opis pracownika.
     */
    std::string pobierzPelneDane() const override;

    /**
     * @brief Serializuje stan obiektu do formatu tekstowego.
     * @return Ciąg znaków zawierający dane personalne oraz listę kategorii prawa jazdy.
     */
    std::string serializuj() const override;
};

#endif //ATOM_PN_1330_06_KIEROWCA_H