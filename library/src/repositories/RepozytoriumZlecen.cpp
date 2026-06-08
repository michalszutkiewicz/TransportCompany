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

shared_ptr<Zlecenie> RepozytoriumZlecen::pobierzZlecenie(const string& id) const {
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

void RepozytoriumZlecen::zapiszStan(const string& sciezka) const {
    ofstream plik(sciezka);
    if (plik.is_open()) {
        plik << serializuj();
        plik.close();
    }
}

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