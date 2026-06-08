#include "repositories/RepozytoriumPojazdow.h"
#include <algorithm>
#include <sstream>
#include <fstream>

#include "BusDostawczy.h"
#include "Ciezarowka.h"

using namespace std;

shared_ptr<Pojazd> RepozytoriumPojazdow::pobierzPojazd(const string& id) const {
    for (const auto& el : elementy) {
        if (el && el->pobierzNrRejestracyjny() == id) {
            return el;
        }
    }
    return nullptr;
}

shared_ptr<Pojazd> RepozytoriumPojazdow::pobierzPoIndeksie(int i) const {
    if (i >= 0 && i < static_cast<int>(elementy.size())) {
        return elementy[i];
    }
    return nullptr;
}

void RepozytoriumPojazdow::dodajPojazd(shared_ptr<Pojazd> element) {
    if (element) {
        elementy.push_back(element);
    }
}

void RepozytoriumPojazdow::usunPojazd(shared_ptr<Pojazd> element) {
    if (!element) return;
    elementy.erase(remove(elementy.begin(), elementy.end(), element), elementy.end());
}

string RepozytoriumPojazdow::raport() const {
    ostringstream oss;
    for (const auto& el : elementy) {
        if (el) {
            oss << el->pobierzOpisPojazdu() << endl;
        }
    }
    return oss.str();
}

int RepozytoriumPojazdow::rozmiar() const {
    return elementy.size();
}

vector<shared_ptr<Pojazd>> RepozytoriumPojazdow::znajdzPo(PojazdPredykat predykat) const {
    vector<shared_ptr<Pojazd>> znalezione;
    for (const auto& el : elementy) {
        if (el && predykat(el)) {
            znalezione.push_back(el);
        }
    }
    return znalezione;
}

vector<shared_ptr<Pojazd>> RepozytoriumPojazdow::pobierzWszystkie() const {
    return elementy;
}

void RepozytoriumPojazdow::zapiszStan(const string& sciezka) const{
    ofstream plik(sciezka);
    if (plik.is_open()) {
        plik << serializuj();
        plik.close();
    }
}

void RepozytoriumPojazdow::wczytajStan(const string& sciezka) {
    ifstream plik(sciezka);
    if (plik.is_open()) {
        stringstream buffer;
        buffer << plik.rdbuf();
        deserializuj(buffer.str());
        plik.close();
    }
}

string RepozytoriumPojazdow::serializuj() const {
    ostringstream oss;
    for (const auto& el : elementy) {
        if (el) {
            oss << el->serializuj() << "\n";
        }
    }
    return oss.str();
}

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
