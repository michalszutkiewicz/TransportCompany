/**
* @file RepozytoriumPracownikow.cpp
 * @brief Implementacja klasy RepozytoriumPracownikow do zarządzania bazą pracowników.
 */
#include "repositories/RepozytoriumPracownikow.h"
#include <algorithm>
#include <sstream>
#include <fstream>

#include "Kierowca.h"

using namespace std;

/**
 * @brief Wyszukuje pracownika w repozytorium na podstawie jego unikalnego identyfikatora (PESEL).
 * @param id Identyfikator (PESEL) pracownika.
 * @return Shared pointer do znalezionego pracownika lub nullptr, jeśli nie istnieje.
 */
shared_ptr<Pracownik> RepozytoriumPracownikow::pobierzPracownik(const string& id) const {
    for (const auto& el : elementy) {
        if (el && el->pobierzPesel() == id) {
            return el;
        }
    }
    return nullptr;
}

/**
 * @brief Pobiera pracownika na podstawie jego indeksu w kontenerze.
 * @param i Indeks pracownika w liście.
 * @return Shared pointer do pracownika lub nullptr, jeśli indeks jest poza zakresem.
 */
shared_ptr<Pracownik> RepozytoriumPracownikow::pobierzPoIndeksie(int i) const {
    if (i >= 0 && i < static_cast<int>(elementy.size())) {
        return elementy[i];
    }
    return nullptr;
}

/**
 * @brief Dodaje nowego pracownika do repozytorium.
 * @param element Shared pointer do dodawanego obiektu typu Pracownik.
 */
void RepozytoriumPracownikow::dodajPracownika(shared_ptr<Pracownik> element) {
    if (element) {
        elementy.push_back(element);
    }
}

/**
 * @brief Usuwa wskazanego pracownika z repozytorium.
 * @param element Shared pointer do pracownika, który ma zostać usunięty.
 */
void RepozytoriumPracownikow::usunPracownika(shared_ptr<Pracownik> element) {
    if (!element) return;
    elementy.erase(remove(elementy.begin(), elementy.end(), element), elementy.end());
}

/**
 * @brief Generuje raport tekstowy zawierający pełne dane wszystkich pracowników.
 * @return Sformatowany ciąg znaków z danymi kadrowymi.
 */
string RepozytoriumPracownikow::raport() const {
    ostringstream oss;
    for (const auto& el : elementy) {
        if (el) {
            oss << el->pobierzPelneDane() << endl;
        }
    }
    return oss.str();
}

/**
 * @brief Zwraca liczbę pracowników zarejestrowanych w repozytorium.
 * @return Rozmiar kolekcji pracowników.
 */
int RepozytoriumPracownikow::rozmiar() const {
    return elementy.size();
}

/**
 * @brief Wyszukuje pracowników spełniających określone kryterium (predykat).
 * @param predykat Funkcja/funktor określający warunek wyszukiwania.
 * @return Wektor pracowników spełniających warunek.
 */
vector<shared_ptr<Pracownik>> RepozytoriumPracownikow::znajdzPo(PracownikPredykat predykat) const {
    vector<shared_ptr<Pracownik>> znalezione;
    for (const auto& el : elementy) {
        if (el && predykat(el)) {
            znalezione.push_back(el);
        }
    }
    return znalezione;
}

/**
 * @brief Pobiera listę wszystkich pracowników w repozytorium.
 * @return Wektor wskaźników do wszystkich pracowników.
 */
vector<shared_ptr<Pracownik>> RepozytoriumPracownikow::pobierzWszystkie() const {
    return elementy;
}

/**
 * @brief Zapisuje aktualny stan repozytorium do pliku.
 * @param sciezka Ścieżka do pliku docelowego.
 */
void RepozytoriumPracownikow::zapiszStan(const string& sciezka) const{
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
void RepozytoriumPracownikow::wczytajStan(const string& sciezka) {
    ifstream plik(sciezka);
    if (plik.is_open()) {
        stringstream buffer;
        buffer << plik.rdbuf();
        deserializuj(buffer.str());
        plik.close();
    }
}

/**
 * @brief Serializuje obiekty pracowników do formatu tekstowego.
 * @return Sformatowany ciąg danych wszystkich pracowników.
 */
string RepozytoriumPracownikow::serializuj() const {
    ostringstream oss;
    for (const auto& el : elementy) {
        if (el) {
            oss << el->serializuj() << "\n";
        }
    }
    return oss.str();
}

/**
 * @brief Deserializuje dane tekstowe i wypełnia repozytorium instancjami klas pochodnych (np. Kierowca).
 * * Metoda parsuje dane o pracowniku (typ;pesel;imie;stawka;kategorie) i
 * tworzy odpowiednie obiekty w zależności od typu pracownika.
 * @param dane Ciąg znaków z danymi do deserializacji.
 */
void RepozytoriumPracownikow::deserializuj(const string& dane) {
    elementy.clear();
    stringstream ss(dane);
    string linia;

    while (getline(ss, linia)) {
        if (linia.empty()) continue;

        stringstream liniaSs(linia);
        string typ;

        getline(liniaSs, typ, ';');

        if (typ == "KIEROWCA") {
            string pesel, imieNazwisko, stawkaStr, kategorieStr;

            getline(liniaSs, pesel, ';');
            getline(liniaSs, imieNazwisko, ';');
            getline(liniaSs, stawkaStr, ';');
            getline(liniaSs, kategorieStr, ';');

            double stawka = stod(stawkaStr);

            vector<string> kategorie;
            stringstream katSs(kategorieStr);
            string kat;
            while (getline(katSs, kat, ',')) {
                if (!kat.empty()) {
                    kategorie.push_back(kat);
                }
            }

            auto nowyKierowca = make_shared<Kierowca>(pesel, imieNazwisko, stawka, kategorie);
            dodajPracownika(nowyKierowca);
        }
    }
}
