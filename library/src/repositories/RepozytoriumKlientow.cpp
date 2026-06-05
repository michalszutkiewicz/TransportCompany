#include "repositories/RepozytoriumKlientow.h"
#include <algorithm>
#include <sstream>
#include <fstream>

using namespace std;

shared_ptr<Klient> RepozytoriumKlientow::pobierzKlienta(const string& id) const {
    for (const auto& el : elementy) {
        if (el && el->pobierzId() == id) {
            return el;
        }
    }
    return nullptr;
}

shared_ptr<Klient> RepozytoriumKlientow::pobierzPoIndeksie(int i) const {
    if (i >= 0 && i < static_cast<int>(elementy.size())) {
        return elementy[i];
    }
    return nullptr;
}

void RepozytoriumKlientow::dodajKlienta(shared_ptr<Klient> element) {
    if (element) {
        elementy.push_back(element);
    }
}

void RepozytoriumKlientow::usunKlienta(shared_ptr<Klient> element) {
    if (!element) return;
    elementy.erase(remove(elementy.begin(), elementy.end(), element), elementy.end());
}

string RepozytoriumKlientow::raport() const {
    ostringstream oss;
    for (const auto& el : elementy) {
        if (el) {
            oss << el->pobierzPelneDane() << endl;
        }
    }
    return oss.str();
}

int RepozytoriumKlientow::rozmiar() const {
    return elementy.size();
}

vector<shared_ptr<Klient>> RepozytoriumKlientow::znajdzPo(KlientPredykat predykat) const {
    vector<shared_ptr<Klient>> znalezione;
    for (const auto& el : elementy) {
        if (el && predykat(el)) {
            znalezione.push_back(el);
        }
    }
    return znalezione;
}

vector<shared_ptr<Klient>> RepozytoriumKlientow::pobierzWszystkie() const {
    return elementy;
}

void RepozytoriumKlientow::zapiszStan(const string& sciezka) {
    ofstream plik(sciezka);
    if (plik.is_open()) {
        plik << serializuj();
        plik.close();
    }
}

void RepozytoriumKlientow::wczytajStan(const string& sciezka) {
    ifstream plik(sciezka);
    if (plik.is_open()) {
        stringstream buffer;
        buffer << plik.rdbuf();
        deserializuj(buffer.str());
        plik.close();
    }
}

string RepozytoriumKlientow::serializuj() const {
    return "SERIALIZOWANE_DANE_KLIENTOW";
}

void RepozytoriumKlientow::deserializuj(const string& dane) {
    // Implementacja deserializacji
}
