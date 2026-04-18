#pragma once
#include <vector>
#include <memory>
#include <string>

// Forward declarations
class Klient; //lepiej dodac odrazu klase a poziej wysylac ja do innego pliku niz tak w kolko bedzie sie wykonywac raz to raz to
class Zasob;
class Zlecenie;

class Firma {
private:
    std::string nazwaFirmy;
    
    // Kontenery na dane (polimorfizmy)
    std::vector<std::shared_ptr<Klient>> klienci;
    std::vector<std::shared_ptr<Zasob>> zasoby;
    std::vector<std::shared_ptr<Zlecenie>> zlecenia;

public:
    Firma(std::string nazwa);
    ~Firma() = default;

    // zarządzanie Klientami
    void dodajKlienta(std::shared_ptr<Klient> klient);
    std::shared_ptr<Klient> znajdzKlienta(const std::string& id);
    const std::vector<std::shared_ptr<Klient>>& pobierzWszystkichKlientow() const;

    //zarządzanie Zasobami
    void dodajZasob(std::shared_ptr<Zasob> zasob);
    std::vector<std::shared_ptr<Zasob>> znajdzDostepneZasoby() const;

    // zarządzanie Zleceniami
    void utworzZlecenie(std::shared_ptr<Zlecenie> zlecenie);
    const std::vector<std::shared_ptr<Zlecenie>>& pobierzWszystkieZlecenia() const;

    // zetody biznesowe
    double obliczCalkowityPrzychod() const;
};