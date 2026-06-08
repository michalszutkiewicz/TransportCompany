//
// Created by Kinga Ratajska on 15/04/2026.
//

#include "../include/Interfejs.h"
#include "../include/managers/MenedzerZlecen.h"
#include <iostream>

#include "../include/BusDostawczy.h"
#include "../include/Ciezarowka.h"
#include "../include/Kierowca.h"
#include "../include/TransportEkspresowy.h"
#include "../include/TransportStandardowy.h"

using namespace std;

InterfejsUI::InterfejsUI() {
    // Konstruktor może inicjować repozytoria lub ładować je z pliku
}

void InterfejsUI::uruchom() {
    bool dziala = true;
    while (dziala) {
        wyswietlMenu();
        int wybor;
        if (!(cin >> wybor)) {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        
        switch (wybor) {
            case 1:
                obsluzKreatorZlecenia();
                break;
            case 2:
                menuDodajZasob();
                break;
            case 3:
                menuPokazDane();
                break;
            case 4:
                zapiszStanSystemu("dane/");
                break;
            case 5:
                wczytajStanSystemu("dane/");
                break;
            case 0:
                dziala = false;
                break;
            default:
                cout << "Nieznana opcja." << endl;
        }
    }
}

void InterfejsUI::wyswietlMenu() {
    cout << "\n--- MENU GŁÓWNE ---" << endl;
    cout << "1. Kreator Zlecenia" << endl;
    cout << "2. Dodaj Zasob" << endl;
    cout << "3. Pokaz dane" << endl;
    cout << "4. Zapisz stan systemu" << endl;
    cout << "5. Wczytaj stan systemu" << endl;
    cout << "0. Wyjście z programu" << endl;
    cout << "Wybierz opcję: ";
}

// --- PODMENU DODAWANIA ZASOBÓW ---
void InterfejsUI::menuDodajZasob() {
    bool wPodmenu = true;
    while (wPodmenu) {
        cout << "\n--- DODAJ ZASÓB ---" << endl;
        cout << "1. Dodaj Pracownika" << endl;
        cout << "2. Dodaj Pojazd" << endl;
        cout << "3. Dodaj Klienta" << endl;
        cout << "0. Powrót" << endl;
        cout << "Wybierz opcję: ";

        int wybor;
        if (!(cin >> wybor)) {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        switch (wybor) {
            case 1:
                dodajPracownika();
                break;
            case 2:
                dodajPojazd();
                break;
            case 3:
                dodajKlienta();
                break;
            case 0:
                wPodmenu = false;
                break;
            default:
                cout << "Nieznana opcja." << endl;
        }
    }
}

// --- PODMENU WYŚWIETLANIA DANYCH ---
void InterfejsUI::menuPokazDane() {
    bool wPodmenu = true;
    while (wPodmenu) {
        cout << "\n--- POKAŻ DANE ---" << endl;
        cout << "1. Pokaz Zlecenia" << endl;
        cout << "2. Pokaz Pracownikow" << endl;
        cout << "3. Pokaz Pojazdy" << endl;
        cout << "4. Pokaz Klientow" << endl;
        cout << "0. Powrót" << endl;
        cout << "Wybierz opcję: ";

        int wybor;
        if (!(cin >> wybor)) {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        switch (wybor) {
            case 1:
                pokazZlecenia();
                break;
            case 2:
                pokazPracownikow();
                break;
            case 3:
                pokazPojazdy();
                break;
            case 4:
                pokazKlientow();
                break;
            case 0:
                wPodmenu = false;
                break;
            default:
                cout << "Nieznana opcja." << endl;
        }
    }
}

// --- METODY WYKORZYSTUJĄCE LOGIKĘ REPOZYTORIÓW DO WYŚWIETLANIA ---

void InterfejsUI::pokazZlecenia() {
    cout << "\n=== LISTA ZLECEŃ ===" << endl;
    if (repoZlecenia.rozmiar() == 0) {
        cout << "Brak zleceń w systemie." << endl;
    } else {
        cout << repoZlecenia.raport();
    }
    cout << "====================" << endl;
}

void InterfejsUI::pokazPracownikow() {
    cout << "\n=== LISTA PRACOWNIKÓW ===" << endl;
    if (repoPracownicy.rozmiar() == 0) {
        cout << "Brak pracowników w systemie." << endl;
    } else {
        cout << repoPracownicy.raport();
    }
    cout << "=========================" << endl;
}

void InterfejsUI::pokazPojazdy() {
    cout << "\n=== LISTA POJAZDÓW ===" << endl;
    if (repoPojazdy.rozmiar() == 0) {
        cout << "Brak pojazdów w systemie." << endl;
    } else {
        cout << repoPojazdy.raport();
    }
    cout << "======================" << endl;
}

void InterfejsUI::pokazKlientow() {
    cout << "\n=== LISTA KLIENTÓW ===" << endl;
    if (repoKlienci.rozmiar() == 0) {
        cout << "Brak klientów w systemie." << endl;
    } else {
        cout << repoKlienci.raport();
    }
    cout << "======================" << endl;
}

void InterfejsUI::obsluzKreatorZlecenia() {
    cout << "\n--- KREATOR ZLECENIA ---" << endl;

    string idZlecenia, idKlienta, idPojazdu, idPracownika;
    double waga, objetosc;
    string kategoria;
    MenedzerZlecen menedzer;

    // 1. Podstawowe dane zlecenia
    cout << "Podaj ID nowego zlecenia: ";
    cin >> idZlecenia;

    cout << "Podaj ID klienta: ";
    cin >> idKlienta;

    auto klient = repoKlienci.pobierzKlienta(idKlienta);

    cout << "Podaj wymaganą wagę ładunku (kg): ";
    cin >> waga;

    cout << "Podaj objętość ładunku (m3): ";
    cin >> objetosc;

    cout << "Podaj wymaganą kategorię pojazdu: ";
    cin >> kategoria;

    // 2. Obsługa obiektu Termin (Wczytywanie daty i godziny od użytkownika)
    namespace pt = boost::posix_time;
    string dataStart, godzinaStart;
    string dataKoniec, godzinaKoniec;
    pt::ptime czasOd, czasDo;
    bool poprawnyTermin = false;

    while (!poprawnyTermin) {
        cout << "\n[Termin rozpoczęcia]" << endl;
        cout << "Podaj datę (RRRR-MM-DD): ";
        cin >> dataStart;
        cout << "Podaj godzinę (GG:MM:SS): ";
        cin >> godzinaStart;

        cout << "\n[Termin zakończenia]" << endl;
        cout << "Podaj datę (RRRR-MM-DD): ";
        cin >> dataKoniec;
        cout << "Podaj godzinę (GG:MM:SS): ";
        cin >> godzinaKoniec;

        try {
            // Konwersja formatu "RRRR-MM-DD GG:MM:SS" na obiekt ptime
            czasOd = pt::time_from_string(dataStart + " " + godzinaStart);
            czasDo = pt::time_from_string(dataKoniec + " " + godzinaKoniec);

            if (czasDo <= czasOd) {
                cout << "[Błąd] Data zakończenia musi być późniejsza niż data rozpoczęcia!" << endl;
            } else {
                poprawnyTermin = true;
            }
        } catch (const std::exception& e) {
            cout << "[Błąd] Niepoprawny format danych! Upewnij się, że zachowujesz format RRRR-MM-DD oraz GG:MM:SS." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }

    Termin okresRealizacji(czasOd, czasDo);

    // 3. Dynamiczny wybór typu usługi przez pracownika
    std::shared_ptr<Usluga> wybranaUsluga = nullptr;
    int typUslugi = 0;
    while (typUslugi != 1 && typUslugi != 2) {
        cout << "\nWybierz typ usługi transportowej:" << endl;
        cout << "1. Transport Standardowy" << endl;
        cout << "2. Transport Ekspresowy" << endl;
        cout << "Wybór: ";
        if (!(cin >> typUslugi)) {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
    }

    double dystans, stawka;
    cout << "Podaj dystans (w km): ";
    cin >> dystans;
    cout << "Podaj stawkę podstawową za km: ";
    cin >> stawka;

    if (typUslugi == 1) {
        wybranaUsluga = std::make_shared<TransportStandardowy>("Transport standardowy " + idZlecenia, dystans, stawka);
    } else {
        double extra;
        cout << "Podaj dodatkową opłatę stałą (extra): ";
        cin >> extra;
        wybranaUsluga = std::make_shared<TransportEkspresowy>("Transport ekspresowy " + idZlecenia, dystans, stawka, extra);
    }

    // 4. Inicjalizacja Zlecenia jako shared_ptr (wszystkie 7 argumentów)
    auto noweZlecenie = std::make_shared<Zlecenie>(idZlecenia, okresRealizacji, klient, wybranaUsluga, waga, objetosc, kategoria);

    // 5. Przypisywanie Pojazdów
    cout << "\n--- PRZYPISYWANIE POJAZDÓW ---" << endl;
    do {
        cout << "Podaj ID pojazdu do przypisania (lub '0' aby zakończyć): ";
        cin >> idPojazdu;
        if (idPojazdu != "0") {
            auto pojazd = repoPojazdy.pobierzPojazd(idPojazdu);
            if (menedzer.probaPrzypisaniaPojazdu(*noweZlecenie, pojazd)) {
                cout << "[Sukces] Pojazd przypisany pomyślnie." << endl;
            } else {
                cout << "[Błąd] Pojazd niedostępny lub brak kierowcy z uprawnieniami." << endl;
            }
        }
    } while (idPojazdu != "0");

    // 6. Przypisywanie Pracowników
    cout << "\n--- PRZYPISYWANIE PRACOWNIKÓW ---" << endl;
    do {
        cout << "Podaj ID pracownika do przypisania (lub '0' aby zakończyć): ";
        cin >> idPracownika;
        if (idPracownika != "0") {
            auto pracownik = repoPracownicy.pobierzPracownik(idPracownika);
            if (menedzer.probaPrzypisaniaPracownika(*noweZlecenie, pracownik)) {
                cout << "[Sukces] Pracownik przypisany pomyślnie." << endl;
            } else {
                cout << "[Błąd] Pracownik niedostępny lub nie posiada wymaganych uprawnień." << endl;
            }
        }
    } while (idPracownika != "0");

    // 7. Finalna weryfikacja i zapis w repozytorium
    cout << "\n--- WERYFIKACJA ZLECENIA ---" << endl;
    if (menedzer.weryfikujGotowoscDoRealizacji(*noweZlecenie)) {
        repoZlecenia.dodajZlecenie(noweZlecenie);
        cout << "[Sukces] Zlecenie jest kompletne i zostało zapisane w repozytorium!" << endl;
    } else {
        cout << "[Uwaga] Zlecenie nie posiada wszystkich wymaganych zasobów (np. pojazdu z przypisanym kierowcą)." << endl;
        cout << "Zapisywanie w repozytorium jako projekt roboczy." << endl;
        repoZlecenia.dodajZlecenie(noweZlecenie);
    }
}

void InterfejsUI::dodajPracownika() {
    cout << "\n--- DODAWANIE PRACOWNIKA (KIEROWCY) ---" << endl;
    string pesel, imie, nazwisko, imieNazwisko;
    double stawka;
    vector<string> kategorie;

    cout << "Podaj ID pracownika (PESEL): ";
    cin >> pesel;

    cout << "Podaj imię: ";
    cin >> imie;

    cout << "Podaj nazwisko: ";
    cin >> nazwisko;

    imieNazwisko = imie + " " + nazwisko;

    cout << "Podaj stawkę godzinową: ";
    while (!(cin >> stawka)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Błąd! Podaj poprawną wartość liczbową: ";
    }

    cout << "Podaj posiadane kategorie prawa jazdy." << endl;
    cout << "Aby zakończyć wprowadzanie kategorii, wpisz '0'." << endl;

    string kategoria;
    while (true) {
        cout << "Kategoria (np. B, C, C+E): ";
        cin >> kategoria;
        if (kategoria == "0") {
            break;
        }
        kategorie.push_back(kategoria);
    }

    auto nowyKierowca = std::make_shared<Kierowca>(pesel, imieNazwisko, stawka, kategorie);
    repoPracownicy.dodajPracownika(nowyKierowca);

    cout << "[Sukces] Pracownik " << imieNazwisko << " został pomyślnie dodany do repozytorium!" << endl;
}

void InterfejsUI::dodajPojazd() {
    cout << "\n--- DODAWANIE POJAZDU ---" << endl;

    int typPojazdu = 0;
    while (typPojazdu != 1 && typPojazdu != 2) {
        cout << "Wybierz typ pojazdu do dodania:" << endl;
        cout << "1. Ciężarówka" << endl;
        cout << "2. Bus dostawczy" << endl;
        cout << "Wybór: ";
        if (!(cin >> typPojazdu)) {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
    }

    string nrRejestracyjny;
    double kosztAmortyzacji;

    cout << "Podaj numer rejestracyjny: ";
    cin >> nrRejestracyjny;

    cout << "Podaj koszt amortyzacji: ";
    while (!(cin >> kosztAmortyzacji)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Błąd! Podaj poprawną wartość liczbową: ";
    }

    if (typPojazdu == 1) {
        double maksLadownosc;
        string naczepaInput;
        bool wymagaNaczepy;

        cout << "Podaj maksymalną ładowność (w tonach): ";
        cin >> maksLadownosc;

        cout << "Czy wymaga naczepy? (t/n): ";
        cin >> naczepaInput;
        wymagaNaczepy = (naczepaInput == "t" || naczepaInput == "T");

        auto nowaCiezarowka = std::make_shared<Ciezarowka>(nrRejestracyjny, kosztAmortyzacji, maksLadownosc, wymagaNaczepy);
        repoPojazdy.dodajPojazd(nowaCiezarowka);

        cout << "[Sukces] Ciężarówka o nr rej. " << nrRejestracyjny << " dodana pomyślnie!" << endl;
    } else {
        double pojemnosc;

        cout << "Podaj pojemność (w m3): ";
        cin >> pojemnosc;

        auto nowyBus = std::make_shared<BusDostawczy>(nrRejestracyjny, kosztAmortyzacji, pojemnosc);
        repoPojazdy.dodajPojazd(nowyBus);

        cout << "[Sukces] Bus dostawczy o nr rej. " << nrRejestracyjny << " dodany pomyślnie!" << endl;
    }
}

void InterfejsUI::dodajKlienta() {
    cout << "\n--- DODAWANIE KLIENTA ---" << endl;
    string idKlienta, imie, nazwisko;

    cout << "Podaj ID klienta (np. KL001): ";
    cin >> idKlienta;

    cout << "Podaj imię: ";
    cin >> imie;

    cout << "Podaj nazwisko lub nazwę firmy: ";
    cin >> nazwisko;

    auto nowyKlient = std::make_shared<Klient>(idKlienta, imie, nazwisko);
    repoKlienci.dodajKlienta(nowyKlient);

    cout << "[Sukces] Klient " << imie << " " << nazwisko << " (" << idKlienta << ") został pomyślnie dodany do systemu!" << endl;
}

void InterfejsUI::zapiszStanSystemu(const std::string& sciezka) {
    std::cout << "\n[Zapis Systemu] Zapisywanie danych do katalogu: " << sciezka << " ..." << std::endl;

    repoKlienci.zapiszStan(sciezka + "klienci.txt");
    repoPracownicy.zapiszStan(sciezka + "pracownicy.txt");
    repoPojazdy.zapiszStan(sciezka + "pojazdy.txt");
    repoZlecenia.zapiszStan(sciezka + "zlecenia.txt");

    std::cout << "[Zapis Systemu] Zakończono pomyślnie.\n";
}

void InterfejsUI::wczytajStanSystemu(const std::string& sciezka) {
    std::cout << "\n[Odczyt Systemu] Wczytywanie danych z katalogu: " << sciezka << " ..." << std::endl;

    repoKlienci.wczytajStan(sciezka + "klienci.txt");
    repoPracownicy.wczytajStan(sciezka + "pracownicy.txt");
    repoPojazdy.wczytajStan(sciezka + "pojazdy.txt");
    repoZlecenia.wczytajStan(sciezka + "zlecenia.txt", repoKlienci, repoPojazdy, repoPracownicy);

    std::cout << "[Odczyt Systemu] Zakończono pomyślnie.\n";
}