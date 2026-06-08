#include "../include/Zlecenie.h"
#include "../include/Klient.h"
#include "../include/Usluga.h"
#include "../include/Pojazd.h"
#include "../include/Pracownik.h"
#include <sstream>

Zlecenie::Zlecenie(std::string id, Termin okres, std::shared_ptr<Klient> k, std::shared_ptr<Usluga> u, double waga, double obj, std::string kat)
    : idZlecenia(id), okresRealizacji(okres), klient(k), usluga(u), czyRozliczone(false), wymaganaWaga(waga), objetosc(obj), wymaganaKategoria(kat) {}

void Zlecenie::dodajPojazd(std::shared_ptr<Pojazd> p) {
    if (p) {
        przypisanePojazdy.push_back(p);
        p->zarezerwujTermin(okresRealizacji);
    }
}

void Zlecenie::dodajPracownika(std::shared_ptr<Pracownik> pr) {
    if (pr) {
        przypisaniPracownicy.push_back(pr);
        pr->zarezerwujTermin(okresRealizacji);
    }
}

double Zlecenie::obliczPelnyKoszt() const {
    if (usluga) {
        return usluga->obliczKoszt();
    }
    return 0.0;
}

void Zlecenie::rozlicz() {
    czyRozliczone = true;
}

Termin Zlecenie::pobierzOkres() const {
    return okresRealizacji;
}

std::string Zlecenie::pobierzStatus() const {
    if (czyRozliczone) {
        return "ROZLICZONE";
    }

    boost::posix_time::ptime teraz = boost::posix_time::second_clock::local_time();

    if (teraz > okresRealizacji.pobierzCzasDo()) {
        return "ZAKOŃCZONE (oczekuje na rozliczenie)";
    } else if (teraz < okresRealizacji.pobierzCzasOd()) {
        return "OCZEKUJĄCE";
    } else {
        return "W TOKU";
    }
}

std::string Zlecenie::pobierzPodsumowanie() const {
    std::ostringstream oss;
    oss << "[ZLECENIE " << idZlecenia << "] - Status: "
        << pobierzStatus() << "\n"
        << "  -> Klient: " << (klient ? klient->pobierzId() : "BRAK KLIENTA") << "\n"
        << "  -> Ładunek: " << wymaganaWaga << " kg, " << objetosc << " m3 (Wymagana kat: " << wymaganaKategoria << ")\n"
        << "  -> Termin Od: " << boost::posix_time::to_simple_string(okresRealizacji.pobierzCzasOd())
        << " Do: " << boost::posix_time::to_simple_string(okresRealizacji.pobierzCzasDo()) << "\n"
        << "  -> Przypisane Pojazdy (" << przypisanePojazdy.size() << "): ";

    for (const auto& pojazd : przypisanePojazdy) {
        if (pojazd) oss << pojazd->pobierzNumerRejestracyjny() << " ";
    }

    oss << "\n  -> Przypisani Pracownicy (" << przypisaniPracownicy.size() << "): ";
    for (const auto& pracownik : przypisaniPracownicy) {
        if (pracownik) oss << pracownik->pobierzIdPracownika() << " ";
    }
    oss << "\n------------------------------------------------";

    return oss.str();
}

std::string Zlecenie::serializuj() const {
    std::ostringstream oss;

    oss << idZlecenia << ";"
        << czyRozliczone << ";"
        << wymaganaWaga << ";"
        << objetosc << ";"
        << wymaganaKategoria << ";"
        << okresRealizacji.serializuj() << ";";

    if (klient) {
        oss << klient->pobierzId() << ";";
    } else {
        oss << "BRAK;";
    }

    oss << przypisanePojazdy.size() << ";";
    for (const auto& pojazd : przypisanePojazdy) {
        if (pojazd) oss << pojazd->pobierzNumerRejestracyjny() << ",";
    }
    oss << ";";

    oss << przypisaniPracownicy.size() << ";";
    for (const auto& pracownik : przypisaniPracownicy) {
        if (pracownik) oss << pracownik->pobierzIdPracownika() << ",";
    }

    return oss.str();
}