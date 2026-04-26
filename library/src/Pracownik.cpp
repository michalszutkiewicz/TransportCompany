#include "../include/Pracownik.h"

Pracownik::Pracownik(std::string id, std::string dane, std::string psl, bool uprawnienia)
    : Zasob(id), imieNazwisko(dane), pesel(psl), posiadaUprawnieniaCE(uprawnienia) {}

bool Pracownik::czySpełniaWymagania(double progUmiejetnosci) const {
    // Pracownik musi być wolny i posiadać uprawnienia
    return sprawdzCzyWolny() && posiadaUprawnieniaCE;
}