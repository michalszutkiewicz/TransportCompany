#include "repositories/RepozytoriumZlecen.h"
#include <algorithm>
#include <sstream>
#include <fstream>

using namespace std;

shared_ptr<Zlecenie> RepozytoriumZlecen::pobierzZlecenie(const string& id) const {
    // Zakładając że Zlecenie ma metodę pobierzId() - sprawdzę to w Zlecenie.h
    // Wcześniej widziałem idZlecenia w Zlecenie.h, ale nie widziałem gettera.
    // Dopiszę getter jeśli brakuje.
    for (const auto& el : elementy) {
        if (el && el->pobierzId() == id) {
            return el;
        }
    }
    return nullptr;
}

shared_ptr<Zlecenie> RepozytoriumZlecen::pobierzPoIndeksie(int i) const {
    if (i >= 0 && i < static_cast<int>(elementy.size())) {
        return elementy[i];
    }
    return nullptr;
}

void RepozytoriumZlecen::dodajZlecenie(shared_ptr<Zlecenie> element) {
    if (element) {
        elementy.push_back(element);
    }
}

void RepozytoriumZlecen::usunZlecenie(shared_ptr<Zlecenie> element) {
    if (!element) return;
    elementy.erase(remove(elementy.begin(), elementy.end(), element), elementy.end());
}

string RepozytoriumZlecen::raport() const {
    ostringstream oss;
    for (const auto& el : elementy) {
        if (el) {
            oss << el->pobierzPodsumowanie() << endl;
        }
    }
    return oss.str();
}

int RepozytoriumZlecen::rozmiar() const {
    return elementy.size();
}

vector<shared_ptr<Zlecenie>> RepozytoriumZlecen::znajdzPo(ZleceniePredykat predykat) const {
    vector<shared_ptr<Zlecenie>> znalezione;
    for (const auto& el : elementy) {
        if (el && predykat(el)) {
            znalezione.push_back(el);
        }
    }
    return znalezione;
}

vector<shared_ptr<Zlecenie>> RepozytoriumZlecen::pobierzWszystkie() const {
    return elementy;
}

void RepozytoriumZlecen::zapiszStan(const string& sciezka) {
    ofstream plik(sciezka);
    if (plik.is_open()) {
        plik << serializuj();
        plik.close();
    }
}

void RepozytoriumZlecen::wczytajStan(const string& sciezka) {
    ifstream plik(sciezka);
    if (plik.is_open()) {
        stringstream buffer;
        buffer << plik.rdbuf();
        deserializuj(buffer.str());
        plik.close();
    }
}

string RepozytoriumZlecen::serializuj() const {
    return "SERIALIZOWANE_DANE_ZLECEN";
}

void RepozytoriumZlecen::deserializuj(const string& dane) {

}
