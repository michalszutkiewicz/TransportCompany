#include "repositories/RepozytoriumPracownikow.h"
#include <algorithm>
#include <sstream>
#include <fstream>

#include "Kierowca.h"

using namespace std;

shared_ptr<Pracownik> RepozytoriumPracownikow::pobierzPracownik(const string& id) const {
    for (const auto& el : elementy) {
        if (el && el->pobierzPesel() == id) {
            return el;
        }
    }
    return nullptr;
}

shared_ptr<Pracownik> RepozytoriumPracownikow::pobierzPoIndeksie(int i) const {
    if (i >= 0 && i < static_cast<int>(elementy.size())) {
        return elementy[i];
    }
    return nullptr;
}

void RepozytoriumPracownikow::dodajPracownika(shared_ptr<Pracownik> element) {
    if (element) {
        elementy.push_back(element);
    }
}

void RepozytoriumPracownikow::usunPracownika(shared_ptr<Pracownik> element) {
    if (!element) return;
    elementy.erase(remove(elementy.begin(), elementy.end(), element), elementy.end());
}

string RepozytoriumPracownikow::raport() const {
    ostringstream oss;
    for (const auto& el : elementy) {
        if (el) {
            oss << el->pobierzPelneDane() << endl;
        }
    }
    return oss.str();
}

int RepozytoriumPracownikow::rozmiar() const {
    return elementy.size();
}

vector<shared_ptr<Pracownik>> RepozytoriumPracownikow::znajdzPo(PracownikPredykat predykat) const {
    vector<shared_ptr<Pracownik>> znalezione;
    for (const auto& el : elementy) {
        if (el && predykat(el)) {
            znalezione.push_back(el);
        }
    }
    return znalezione;
}

vector<shared_ptr<Pracownik>> RepozytoriumPracownikow::pobierzWszystkie() const {
    return elementy;
}

void RepozytoriumPracownikow::zapiszStan(const string& sciezka) const{
    ofstream plik(sciezka);
    if (plik.is_open()) {
        plik << serializuj();
        plik.close();
    }
}

void RepozytoriumPracownikow::wczytajStan(const string& sciezka) {
    ifstream plik(sciezka);
    if (plik.is_open()) {
        stringstream buffer;
        buffer << plik.rdbuf();
        deserializuj(buffer.str());
        plik.close();
    }
}

string RepozytoriumPracownikow::serializuj() const {
    ostringstream oss;
    for (const auto& el : elementy) {
        if (el) {
            oss << el->serializuj() << "\n";
        }
    }
    return oss.str();
}

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
