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
        library/include/Zasob.h
)