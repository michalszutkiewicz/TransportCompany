cmake_minimum_required(VERSION 3.20)
project(ATOM_PN_1330_06)

set(CMAKE_CXX_STANDARD 17)

include_directories(library/include)

add_executable(ATOM_PN_1330_06
        library/main.cpp
        library/src/Firma.cpp
        library/src/Interfejs.cpp
        library/src/Klient.cpp
        library/src/ObslugaPlikow.cpp
        library/src/Pojazd.cpp
        library/src/Pracownik.cpp
        library/src/TransportEkspresowy.cpp
        library/src/TransportStandardowy.cpp
        library/src/Zlecenie.cpp
        library/src/Ciezarowka.cpp
        library/src/BusDostawczy.cpp
        library/src/Kierowca.cpp
        library/src/Termin.cpp
        library/src/Usluga.cpp
        library/src/managers/MenedzerZlecen.cpp
        library/src/repositories/RepozytoriumPojazdow.cpp
        library/src/repositories/RepozytoriumKlientow.cpp
        library/src/repositories/RepozytoriumPracownikow.cpp
        library/src/repositories/RepozytoriumZlecen.cpp
)