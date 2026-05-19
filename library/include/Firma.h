#pragma once
#include <vector>
#include <memory>
#include <string>

// Forward declarations
class Klient; //lepiej dodac odrazu klase a poziej wysylac ja do innego pliku niz tak w kolko bedzie sie wykonywac raz to raz to
class Pojazd;
class Pracownik;
class Zlecenie;

class Firma {
private:
    std::string nazwaFirmy;
    
    // Kontenery na dane (polimorfizmy)
    std::vector<std::shared_ptr<Klient>> klienci;
    std::vector<std::shared_ptr<Pojazd>> pojazdy;
    std::vector<std::shared_ptr<Pracownik>> prcaownicy;
    std::vector<std::shared_ptr<Zlecenie>> zlecenia;

public:
    Firma(std::string nazwa);
    ~Firma() = default;

    // zarządzanie Klientami
    void dodajKlienta(std::shared_ptr<Klient> klient);

    //zarządzanie Zasobami
    void rejestrujPojazd(std::shared_ptr<Pojazd> zasob);
    void zatrudnijPracownika(std::shared_ptr<Pracownik> zasob);

    std::shared_ptr<Klient> pobierzKlienta(std::string id);

    // zetody biznesowe
    double obliczCalkowityPrzychod() const;
};