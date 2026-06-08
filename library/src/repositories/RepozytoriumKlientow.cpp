/**
 * @file RepozytoriumKlientow.cpp
 * @brief Implementacja klasy RepozytoriumKlientow do zarządzania bazą klientów.
 */

#include "repositories/RepozytoriumKlientow.h"
#include <algorithm>
#include <sstream>
#include <fstream>

using namespace std;

/**
 * @brief Wyszukuje klienta w repozytorium na podstawie jego unikalnego identyfikatora.
 * @param id Identyfikator klienta.
 * @return Shared pointer do znalezionego klienta lub nullptr, jeśli nie istnieje.
 */
shared_ptr<Klient> RepozytoriumKlientow::pobierzKlienta(const string& id) const {
    for (const auto& el : elementy) {
        if (el && el->pobierzId() == id) {
            return el;
        }
    }
    return nullptr;
}

/**
 * @brief Pobiera klienta na podstawie jego indeksu w kontenerze.
 * @param i Indeks klienta w liście.
 * @return Shared pointer do klienta lub nullptr, jeśli indeks jest poza zakresem.
 */
shared_ptr<Klient> RepozytoriumKlientow::pobierzPoIndeksie(int i) const {
    if (i >= 0 && i < static_cast<int>(elementy.size())) {
        return elementy[i];
    }
    return nullptr;
}

/**
 * @brief Dodaje nowego klienta do repozytorium.
 * @param element Shared pointer do dodawanego obiektu Klient.
 */
void RepozytoriumKlientow::dodajKlienta(shared_ptr<Klient> element) {
    if (element) {
        elementy.push_back(element);
    }
}

/**
 * @brief Usuwa wskazanego klienta z repozytorium.
 * @param element Shared pointer do klienta, który ma zostać usunięty.
 */
void RepozytoriumKlientow::usunKlienta(shared_ptr<Klient> element) {
    if (!element) return;
    elementy.erase(remove(elementy.begin(), elementy.end(), element), elementy.end());
}

/**
 * @brief Generuje raport tekstowy zawierający dane wszystkich klientów.
 * @return Sformatowany ciąg znaków z danymi klientów.
 */
string RepozytoriumKlientow::raport() const {
    ostringstream oss;
    for (const auto& el : elementy) {
        if (el) {
            oss << el->pobierzPelneDane() << endl;
        }
    }
    return oss.str();
}

/**
 * @brief Zwraca liczbę klientów znajdujących się w repozytorium.
 * @return Rozmiar kolekcji.
 */
int RepozytoriumKlientow::rozmiar() const {
    return elementy.size();
}

/**
 * @brief Wyszukuje klientów spełniających określony warunek (predykat).
 * @param predykat Funkcja/funktor określający kryterium wyszukiwania.
 * @return Wektor klientów spełniających warunek.
 */
vector<shared_ptr<Klient>> RepozytoriumKlientow::znajdzPo(KlientPredykat predykat) const {
    vector<shared_ptr<Klient>> znalezione;
    for (const auto& el : elementy) {
        if (el && predykat(el)) {
            znalezione.push_back(el);
        }
    }
    return znalezione;
}

/**
 * @brief Pobiera listę wszystkich klientów w repozytorium.
 * @return Wektor wskaźników do wszystkich klientów.
 */
vector<shared_ptr<Klient>> RepozytoriumKlientow::pobierzWszystkie() const {
    return elementy;
}

/**
 * @brief Zapisuje aktualny stan repozytorium do pliku.
 * @param sciezka Ścieżka do pliku docelowego.
 */
void RepozytoriumKlientow::zapiszStan(const string& sciezka) const {
    ofstream plik(sciezka);
    if (plik.is_open()) {
        plik << serializuj();
        plik.close();
    }
}

/**
 * @brief Wczytuje stan repozytorium z pliku zewnętrznego.
 * @param sciezka Ścieżka do pliku źródłowego.
 */
void RepozytoriumKlientow::wczytajStan(const string& sciezka) {
    ifstream plik(sciezka);
    if (plik.is_open()) {
        stringstream buffer;
        buffer << plik.rdbuf();
        deserializuj(buffer.str());
        plik.close();
    }
}

/**
 * @brief Serializuje obiekty klientów do formatu tekstowego.
 * @return Sformatowany ciąg danych klientów.
 */
string RepozytoriumKlientow::serializuj() const {
    ostringstream oss;
    for (const auto& el : elementy) {
        if (el) {
            oss << el->serializuj() << "\n";
        }
    }
    return oss.str();
}

/**
 * @brief Deserializuje dane tekstowe i wypełnia repozytorium obiektami Klient.
 * * Parsuje dane rozdzielone średnikami (id;imie;nazwisko).
 * @param dane Ciąg znaków z danymi do deserializacji.
 */
void RepozytoriumKlientow::deserializuj(const string& dane) {
    elementy.clear();
    stringstream ss(dane);
    string linia;

    while (getline(ss, linia)) {
        while (!linia.empty() && (linia.back() == '\r' || linia.back() == '\n')) {
            linia.pop_back();
        }

        if (linia.empty()) continue;

        stringstream liniaSs(linia);
        string id, imie, nazwisko;

        getline(liniaSs, id, ';');
        getline(liniaSs, imie, ';');
        getline(liniaSs, nazwisko, ';');

        if (!nazwisko.empty() && nazwisko.back() == '\r') {
            nazwisko.pop_back();
        }

        auto nowyKlient = make_shared<Klient>(id, imie, nazwisko);
        dodajKlienta(nowyKlient);
    }
}
