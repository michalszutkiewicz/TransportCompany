#ifndef ATOM_PN_1330_06_KLIENT_H
#define ATOM_PN_1330_06_KLIENT_H
#pragma once
#include <string>

//klasa tak naprawde tylk do przechowywania danych a nie pracy na nich
class Klient {
private:
    std::string imie;
    std::string nazwisko;
    std::string idKlienta; //zrobimy tutaj albo pesel albo NIP ale jeszcze nie wiem co:)

public:
    //konstruktor
    Klient(std::string imie, std::string nazwisko, std::string id);

    // Gettery (robimy tylko do odczytu danych chyba)
    std::string pobierzImie() const { return imie; }
    std::string pobierzNazwisko() const { return nazwisko; }
    std::string pobierzId() const { return idKlienta; }
    //dzieki const metody nie napewno nie beda zmieniac danych istniejacych juz klientow tylko dopisywac nowe

    //metoda pomocnicza do wyświetlania danych w konsoli
    std::string pobierzPelneDane() const;
};

#endif //ATOM_PN_1330_06_KLIENT_H