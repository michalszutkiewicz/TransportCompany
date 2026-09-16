cmake_minimum_required(VERSION 3.20)
project(TransportCompany)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Wymagane komponenty Boost oraz wbudowane biblioteki dynamicznego ladowania (dlopen na Linux)
find_package(Boost REQUIRED COMPONENTS date_time unit_test_framework)

# ---  GLOWNA BIBLIOTEKA RDZENIA (Core Library) ---
set(LIB_SOURCES
        library/src/Klient.cpp
        library/src/Pojazd.cpp
        library/src/Pracownik.cpp
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
        library/include/Exceptions.h
)

add_library(TransportLibrary STATIC ${LIB_SOURCES})
target_include_directories(TransportLibrary PUBLIC library/include ${Boost_INCLUDE_DIRS})
# CMAKE_DL_LIBS zapewnia poprawne linkowanie mechanizmu dlopen na systemach POSIX/Linux
target_link_libraries(TransportLibrary PUBLIC Boost::date_time ${CMAKE_DL_LIBS})

# --- MODULY DYNAMICZNE / WTYCZKI (Shared Libraries) ---
# Wtyczka 1: Transport Standardowy
add_library(TransportStandardowy SHARED
        library/src/TransportStandardowy.cpp
        library/src/plugins/TransportStandardowyPlugin.cpp
)
target_link_libraries(TransportStandardowy PRIVATE TransportLibrary)

# Wtyczka 2: Transport Ekspresowy
add_library(TransportEkspresowy SHARED
        library/src/TransportEkspresowy.cpp
        library/src/plugins/TransportEkspresowyPlugin.cpp
)
target_link_libraries(TransportEkspresowy PRIVATE TransportLibrary)

# Konfiguracja katalogu wyjsciowego dla wtyczek (.dll / .so trafia do folderu 'plugins')
set_target_properties(TransportStandardowy TransportEkspresowy PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/plugins"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/plugins"
)

# --- GLOWNY PROGRAM WYKONYWALNY ---
add_executable(TransportCompany library/main.cpp library/src/Interfejs.cpp)
target_link_libraries(TransportCompany PRIVATE TransportLibrary)

# Wymuszenie kompilacji wtyczek przed uruchomieniem glownego programu
add_dependencies(TransportCompany TransportStandardowy TransportEkspresowy)

# --- TESTY JEDNOSTKOWE ---
enable_testing()

add_executable(TransportTests
        tests/RepozytoriumTests.cpp
        tests/ZlecenieTests.cpp
        tests/MenedzerZlecenTests.cpp
        tests/IntegracjaTests.cpp
)

target_link_libraries(TransportTests PRIVATE
        TransportLibrary
        TransportStandardowy
        TransportEkspresowy
        Boost::date_time
        Boost::unit_test_framework
)

add_dependencies(TransportTests TransportStandardowy TransportEkspresowy)
add_test(NAME AllTransportTests COMMAND TransportTests)

# Kopiowanie danych do katalogu budowania
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/dane DESTINATION ${CMAKE_CURRENT_BINARY_DIR})