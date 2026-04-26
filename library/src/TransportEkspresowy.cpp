#include "../include/TransportEkspresowy.h"
#include <sstream>

TransportEkspresowy::TransportEkspresowy(std::string nazwa, double dystans, double stawka, double extra)
    : Usluga(nazwa, dystans), stawkaEkspresowa(stawka), oplataStala(extra) {}

double TransportEkspresowy::obliczKoszt() const {
    //koszt jest wyższy o oplate stałą za priorytet wiec musimy dodac
    return (dystans * stawkaEkspresowa) + oplataStala;
}

std::string TransportEkspresowy::pobierzSzczegoly() const {
    std::stringstream ss;
    ss << "Typ: EKSPRESOWY | Dystans: " << dystans << " km | Dopłata stała: " << oplataStala << " PLN";
    return ss.str();
}