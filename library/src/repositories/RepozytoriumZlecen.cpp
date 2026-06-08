/**
* @file RepozytoriumZlecen.cpp
 * @brief Implementacja klasy RepozytoriumZlecen zarządzającej bazą zleceń transportowych.
 */
#include "../../include/repositories/RepozytoriumZlecen.h"
#include "../../include/repositories/RepozytoriumKlientow.h"
#include "../../include/repositories/RepozytoriumPojazdow.h"
#include "../../include/repositories/RepozytoriumPracownikow.h"
#include "../../include/TransportStandardowy.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm> // Dodane dla std::remove w usunZlecenie

using namespace std;

/**
 * @brief Wyszukuje zlecenie w repozytorium na podstawie jego unikalnego identyfikatora.
 * @param id Identyfikator zlecenia.
 * @return Shared pointer do znalezionego zlecenia lub nullptr, jeśli nie istnieje.
 */
shared_ptr<Zlecenie> RepozytoriumZlecen::pobierzZlecenie(const string& id) const {
    for (const auto& el : elementy) {
        if (el && el->pobierzId() == id) {
            return el;
        }
    }
    return nullptr;
}

/**
 * @brief Pobiera zlecenie na podstawie jego indeksu w kontenerze.
 * @param i Indeks zlecenia w liście.
 * @return Shared pointer do zlecenia lub nullptr, jeśli indeks jest poza zakresem.
 */
shared_ptr<Zlecenie> RepozytoriumZlecen::pobierzPoIndeksie(int i) const {
    if (i >= 0 && i < static_cast<int>(elementy.size())) {
        return elementy[i];
    }
    return nullptr;
}

/**
 * @brief Dodaje nowe zlecenie do repozytorium.
 * @param element Shared pointer do dodawanego obiektu typu Zlecenie.
 */
void RepozytoriumZlecen::dodajZlecenie(shared_ptr<Zlecenie> element) {
    if (element) {
        elementy.push_back(element);
    }
}

/**
 * @brief Usuwa wskazane zlecenie z repozytorium.
 * @param element Shared pointer do zlecenia, które ma zostać usunięte.
 */
void RepozytoriumZlecen::usunZlecenie(shared_ptr<Zlecenie> element) {
    if (!element) return;
    elementy.erase(remove(elementy.begin(), elementy.end(), element), elementy.end());
}

/**
 * @brief Generuje raport tekstowy zawierający podsumowanie wszystkich zleceń.
 * @return Sformatowany ciąg znaków z podsumowaniami zleceń.
 */
string RepozytoriumZlecen::raport() const {
    ostringstream oss;
    for (const auto& el : elementy) {
        if (el) {
            oss << el->pobierzPodsumowanie() << endl;
        }
    }
    return oss.str();
}

/**
 * @brief Zwraca liczbę zleceń w repozytorium.
 * @return Rozmiar kolekcji.
 */
int RepozytoriumZlecen::rozmiar() const {
    return elementy.size();
}

/**
 * @brief Wyszukuje zlecenia spełniające określone kryterium (predykat).
 * @param predykat Funkcja/funktor określający warunek wyszukiwania.
 * @return Wektor zleceń spełniających warunek.
 */
vector<shared_ptr<Zlecenie>> RepozytoriumZlecen::znajdzPo(ZleceniePredykat predykat) const {
    vector<shared_ptr<Zlecenie>> znalezione;
    for (const auto& el : elementy) {
        if (el && predykat(el)) {
            znalezione.push_back(el);
        }
    }
    return znalezione;
}

/**
 * @brief Pobiera listę wszystkich zleceń w repozytorium.
 * @return Wektor wskaźników do wszystkich zleceń.
 */
vector<shared_ptr<Zlecenie>> RepozytoriumZlecen::pobierzWszystkie() const {
    return elementy;
}

/**
 * @brief Zapisuje aktualny stan repozytorium do pliku.
 * @param sciezka Ścieżka do pliku docelowego.
 */
void RepozytoriumZlecen::zapiszStan(const string& sciezka) const {
    ofstream plik(sciezka);
    if (plik.is_open()) {
        plik << serializuj();
        plik.close();
    }
}

/**
 * @brief Serializuje obiekty zleceń do formatu tekstowego.
 * @return Ciąg znaków z danymi zleceń.
 */
string RepozytoriumZlecen::serializuj() const {
    ostringstream oss;
    for (const auto& el : elementy) {
        if (el) {
            oss << el->serializuj() << "\n";
        }
    }
    return oss.str();
}

void RepozytoriumZlecen::wczytajStan(const string& sciezka) {
    // Nie używamy tej wersji dla Zleceń
}

void RepozytoriumZlecen::deserializuj(const string& dane) {
    // Nie używamy tej wersji dla Zleceń
}

/**
 * @brief Wczytuje stan zleceń z pliku zewnętrznego, powiązując je z danymi zasobów.
 * * Metoda parsuje plik tekstowy, tworzy instancje klasy Zlecenie i przypisuje
 * do nich odpowiednich klientów, pojazdy oraz pracowników, korzystając z
 * przekazanych repozytoriów.
 * @param sciezka Ścieżka do pliku z danymi zleceń.
 * @param rKlienci Referencja do repozytorium klientów.
 * @param rPojazdy Referencja do repozytorium pojazdów.
 * @param rPracownicy Referencja do repozytorium pracowników.
 */
void RepozytoriumZlecen::wczytajStan(const std::string& sciezka,
                                     RepozytoriumKlientow& rKlienci,
                                     RepozytoriumPojazdow& rPojazdy,
                                     RepozytoriumPracownikow& rPracownicy) {

    std::ifstream plikZlecen(sciezka);
    if (!plikZlecen.is_open()) {
        std::cerr << "Nie udalo sie otworzyc pliku: " << sciezka << std::endl;
        return;
    }

    elementy.clear();

    std::string linia;
    while (std::getline(plikZlecen, linia)) {
        while (!linia.empty() && (linia.back() == '\r' || linia.back() == '\n')) {
            linia.pop_back();
        }
        if (linia.empty()) continue;

        std::stringstream liniaSs(linia);
        std::string idZlecenia, czyRozliczoneStr, wagaStr, objetoscStr, wymaganaKat;
        std::string dataOdStr, dataDoStr, idKlienta, liczbaPojazdowStr, listaPojazdowStr, liczbaPracownikowStr, listaPracownikowStr;

        std::getline(liniaSs, idZlecenia, ';');
        std::getline(liniaSs, czyRozliczoneStr, ';');
        std::getline(liniaSs, wagaStr, ';');
        std::getline(liniaSs, objetoscStr, ';');
        std::getline(liniaSs, wymaganaKat, ';');
        std::getline(liniaSs, dataOdStr, ';');
        std::getline(liniaSs, dataDoStr, ';');
        std::getline(liniaSs, idKlienta, ';');
        std::getline(liniaSs, liczbaPojazdowStr, ';');
        std::getline(liniaSs, listaPojazdowStr, ';');
        std::getline(liniaSs, liczbaPracownikowStr, ';');
        std::getline(liniaSs, listaPracownikowStr, ';');

        double waga = std::stod(wagaStr);
        double objetosc = std::stod(objetoscStr);
        bool czyRozl = (czyRozliczoneStr == "1");

        namespace pt = boost::posix_time;
        pt::ptime czasOd = pt::from_iso_extended_string(dataOdStr);
        pt::ptime czasDo = pt::from_iso_extended_string(dataDoStr);
        Termin terminZlecenia(czasOd, czasDo);

        auto klient = rKlienci.pobierzKlienta(idKlienta);
        auto usluga = std::make_shared<TransportStandardowy>("Usluga " + idZlecenia, 100.0, 3.5);
        auto noweZlecenie = std::make_shared<Zlecenie>(idZlecenia, terminZlecenia, klient, usluga, waga, objetosc, wymaganaKat);

        std::stringstream pojazdySs(listaPojazdowStr);
        std::string idPojazdu;
        while (std::getline(pojazdySs, idPojazdu, ',')) {
            if (!idPojazdu.empty()) {
                auto pojazd = rPojazdy.pobierzPojazd(idPojazdu);
                if (pojazd) noweZlecenie->dodajPojazd(pojazd);
            }
        }

        std::stringstream pracownicySs(listaPracownikowStr);
        std::string idPracownika;
        while (std::getline(pracownicySs, idPracownika, ',')) {
            if (!idPracownika.empty()) {
                auto pracownik = rPracownicy.pobierzPracownik(idPracownika);
                if (pracownik) noweZlecenie->dodajPracownika(pracownik);
            }
        }

        if (czyRozl) noweZlecenie->rozlicz();

        dodajZlecenie(noweZlecenie);
    }
    plikZlecen.close();
}