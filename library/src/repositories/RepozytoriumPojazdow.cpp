/**
* @file RepozytoriumPojazdow.cpp
 * @brief Implementacja klasy RepozytoriumPojazdow zarządzającej zasobami transportowymi.
 */
#include "repositories/RepozytoriumPojazdow.h"
#include <algorithm>
#include <sstream>
#include <fstream>

#include "BusDostawczy.h"
#include "Ciezarowka.h"

using namespace std;

/**
 * @brief Wyszukuje pojazd w repozytorium na podstawie numeru rejestracyjnego.
 * @param id Numer rejestracyjny pojazdu.
 * @return Shared pointer do znalezionego pojazdu lub nullptr, jeśli nie istnieje.
 */
shared_ptr<Pojazd> RepozytoriumPojazdow::pobierzPojazd(const string& id) const {
    for (const auto& el : elementy) {
        if (el && el->pobierzNrRejestracyjny() == id) {
            return el;
        }
    }
    return nullptr;
}

/**
 * @brief Pobiera pojazd na podstawie jego indeksu w kontenerze.
 * @param i Indeks pojazdu w liście.
 * @return Shared pointer do pojazdu lub nullptr, jeśli indeks jest poza zakresem.
 */
shared_ptr<Pojazd> RepozytoriumPojazdow::pobierzPoIndeksie(int i) const {
    if (i >= 0 && i < static_cast<int>(elementy.size())) {
        return elementy[i];
    }
    return nullptr;
}

/**
 * @brief Dodaje nowy pojazd do repozytorium.
 * @param element Shared pointer do dodawanego obiektu typu Pojazd.
 */
void RepozytoriumPojazdow::dodajPojazd(shared_ptr<Pojazd> element) {
    if (element) {
        elementy.push_back(element);
    }
}

/**
 * @brief Usuwa wskazany pojazd z repozytorium.
 * @param element Shared pointer do pojazdu, który ma zostać usunięty.
 */
void RepozytoriumPojazdow::usunPojazd(shared_ptr<Pojazd> element) {
    if (!element) return;
    elementy.erase(remove(elementy.begin(), elementy.end(), element), elementy.end());
}

/**
 * @brief Generuje raport tekstowy z opisem wszystkich pojazdów w repozytorium.
 * @return Sformatowany ciąg znaków zawierający opisy pojazdów.
 */
string RepozytoriumPojazdow::raport() const {
    ostringstream oss;
    for (const auto& el : elementy) {
        if (el) {
            oss << el->pobierzOpisPojazdu() << endl;
        }
    }
    return oss.str();
}

/**
 * @brief Zwraca liczbę pojazdów w repozytorium.
 * @return Rozmiar kolekcji pojazdów.
 */
int RepozytoriumPojazdow::rozmiar() const {
    return elementy.size();
}

/**
 * @brief Wyszukuje pojazdy spełniające określone kryterium (predykat).
 * @param predykat Funkcja/funktor określający warunek wyszukiwania.
 * @return Wektor pojazdów spełniających warunek.
 */
vector<shared_ptr<Pojazd>> RepozytoriumPojazdow::znajdzPo(PojazdPredykat predykat) const {
    vector<shared_ptr<Pojazd>> znalezione;
    for (const auto& el : elementy) {
        if (el && predykat(el)) {
            znalezione.push_back(el);
        }
    }
    return znalezione;
}

/**
 * @brief Pobiera listę wszystkich pojazdów.
 * @return Wektor wskaźników do wszystkich pojazdów.
 */
vector<shared_ptr<Pojazd>> RepozytoriumPojazdow::pobierzWszystkie() const {
    return elementy;
}

/**
 * @brief Zapisuje aktualny stan repozytorium do pliku.
 * @param sciezka Ścieżka do pliku wyjściowego.
 */
void RepozytoriumPojazdow::zapiszStan(const string& sciezka) const{
    ofstream plik(sciezka);
    if (plik.is_open()) {
        plik << serializuj();
        plik.close();
    }
}

/**
 * @brief Wczytuje stan repozytorium z pliku tekstowego.
 * @param sciezka Ścieżka do pliku źródłowego.
 */
void RepozytoriumPojazdow::wczytajStan(const string& sciezka) {
    ifstream plik(sciezka);
    if (plik.is_open()) {
        stringstream buffer;
        buffer << plik.rdbuf();
        deserializuj(buffer.str());
        plik.close();
    }
}

/**
 * @brief Serializuje obiekty pojazdów do formatu tekstowego.
 * @return Ciąg znaków z serializowanymi danymi wszystkich pojazdów.
 */
string RepozytoriumPojazdow::serializuj() const {
    ostringstream oss;
    for (const auto& el : elementy) {
        if (el) {
            oss << el->serializuj() << "\n";
        }
    }
    return oss.str();
}

/**
 * @brief Deserializuje dane tekstowe i tworzy odpowiednie instancje klas (Ciezarowka, Bus).
 * * Metoda rozpoznaje typ pojazdu na podstawie flagi (np. "CIEZAROWKA", "BUS")
 * i tworzy odpowiedni obiekt za pomocą `make_shared`.
 * @param dane Ciąg znaków z danymi do deserializacji.
 */
void RepozytoriumPojazdow::deserializuj(const string& dane) {
    elementy.clear();
    stringstream ss(dane);
    string linia;

    while (getline(ss, linia)) {
        if (linia.empty()) continue;

        stringstream liniaSs(linia);
        string typ;
        getline(liniaSs, typ, ';');

        if (typ == "CIEZAROWKA") {
            string nrRej, kosztStr, ladownoscStr, naczepaStr;
            getline(liniaSs, nrRej, ';');
            getline(liniaSs, kosztStr, ';');
            getline(liniaSs, ladownoscStr, ';');
            getline(liniaSs, naczepaStr, ';');

            double koszt = stod(kosztStr);
            double ladownosc = stod(ladownoscStr);
            bool naczepa = (naczepaStr == "1");

            dodajPojazd(make_shared<Ciezarowka>(nrRej, koszt, ladownosc, naczepa));
        }
        else if (typ == "BUS") {
            string nrRej, kosztStr, pojStr;
            getline(liniaSs, nrRej, ';');
            getline(liniaSs, kosztStr, ';');
            getline(liniaSs, pojStr, ';');

            dodajPojazd(make_shared<BusDostawczy>(nrRej, stod(kosztStr), stod(pojStr)));
        }
    }
}
