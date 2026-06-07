//
// Created by Kinga Ratajska on 15/04/2026.
//

#include "ObslugaPlikow.h"
#include "TransportStandardowy.h"
#include "TransportEkspresowy.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;

void ObslugaPlikow::zapiszStanSystemu(const Firma& f, const string& sciezka) {
    Firma& modyfikowalnaFirma = const_cast<Firma&>(f);

    cout << "\n[Zapis Systemu] Zapisywanie danych do katalogu: " << sciezka << " ..." << endl;

    modyfikowalnaFirma.pobierzRepozytoriumKlientow().zapiszStan(sciezka + "klienci.txt");
    modyfikowalnaFirma.pobierzRepozytoriumPracownikow().zapiszStan(sciezka + "pracownicy.txt");
    modyfikowalnaFirma.pobierzRepozytoriumPojazdow().zapiszStan(sciezka + "pojazdy.txt");
    modyfikowalnaFirma.pobierzRepozytoriumZlecen().zapiszStan(sciezka + "zlecenia.txt");

    cout << "[Zapis Systemu] Zakończono pomyślnie." << endl;
}

Firma ObslugaPlikow::wczytajStanSystemu(const string& sciezka) {
    Firma nowaFirma;

    cout << "\n[Odczyt Systemu] Wczytywanie danych z katalogu: " << sciezka << " ..." << endl;

    nowaFirma.pobierzRepozytoriumKlientow().wczytajStan(sciezka + "klienci.txt");
    nowaFirma.pobierzRepozytoriumPracownikow().wczytajStan(sciezka + "pracownicy.txt");
    nowaFirma.pobierzRepozytoriumPojazdow().wczytajStan(sciezka + "pojazdy.txt");

    ifstream plikZlecen(sciezka + "zlecenia.txt");
    if (plikZlecen.is_open()) {
        string linia;
        while (getline(plikZlecen, linia)) {

            while (!linia.empty() && (linia.back() == '\r' || linia.back() == '\n')) {
                linia.pop_back();
            }
            if (linia.empty()) continue;

            stringstream liniaSs(linia);
            string idZlecenia, czyRozliczoneStr, wagaStr, objetoscStr, wymaganaKat;
            string dataOdStr, dataDoStr, idKlienta, liczbaPojazdowStr, listaPojazdowStr, liczbaPracownikowStr, listaPracownikowStr;

            getline(liniaSs, idZlecenia, ';');
            getline(liniaSs, czyRozliczoneStr, ';');
            getline(liniaSs, wagaStr, ';');
            getline(liniaSs, objetoscStr, ';');
            getline(liniaSs, wymaganaKat, ';');
            getline(liniaSs, dataOdStr, ';');
            getline(liniaSs, dataDoStr, ';');
            getline(liniaSs, idKlienta, ';');
            getline(liniaSs, liczbaPojazdowStr, ';');
            getline(liniaSs, listaPojazdowStr, ';');
            getline(liniaSs, liczbaPracownikowStr, ';');
            getline(liniaSs, listaPracownikowStr, ';');

            double waga = stod(wagaStr);
            double objetosc = stod(objetoscStr);
            bool czyRozl = (czyRozliczoneStr == "1");

            namespace pt = boost::posix_time;
            pt::ptime czasOd = pt::from_iso_extended_string(dataOdStr);
            pt::ptime czasDo = pt::from_iso_extended_string(dataDoStr);
            Termin terminZlecenia(czasOd, czasDo);

            auto klient = nowaFirma.pobierzRepozytoriumKlientow().pobierzKlienta(idKlienta);
            auto usluga = std::make_shared<TransportStandardowy>("Usluga " + idZlecenia, 100.0, 3.5);
            auto noweZlecenie = make_shared<Zlecenie>(idZlecenia, terminZlecenia, klient, usluga, waga, objetosc, wymaganaKat);

            stringstream pojazdySs(listaPojazdowStr);
            string idPojazdu;
            while (getline(pojazdySs, idPojazdu, ',')) {
                if (!idPojazdu.empty()) {
                    auto pojazd = nowaFirma.pobierzRepozytoriumPojazdow().pobierzPojazd(idPojazdu);
                    if (pojazd) noweZlecenie->dodajPojazd(pojazd);
                }
            }

            stringstream pracownicySs(listaPracownikowStr);
            string idPracownika;
            while (getline(pracownicySs, idPracownika, ',')) {
                if (!idPracownika.empty()) {
                    auto pracownik = nowaFirma.pobierzRepozytoriumPracownikow().pobierzPracownik(idPracownika);
                    if (pracownik) noweZlecenie->dodajPracownika(pracownik);
                }
            }

            if (czyRozl) noweZlecenie->rozlicz();

            nowaFirma.pobierzRepozytoriumZlecen().dodajZlecenie(noweZlecenie);
        }
        plikZlecen.close();
    }

    cout << "[Odczyt Systemu] Zakończono pomyślnie." << endl;
    return nowaFirma;
}
