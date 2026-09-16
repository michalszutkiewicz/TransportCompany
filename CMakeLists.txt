cmake_minimum_required(VERSION 3.20)
project(TransportCompany)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED COMPONENTS date_time unit_test_framework)

set(LIB_SOURCES
        library/src/Klient.cpp
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
        library/include/Exceptions.h
)

add_library(TransportLibrary STATIC ${LIB_SOURCES})
target_include_directories(TransportLibrary PUBLIC library/include ${Boost_INCLUDE_DIRS})
target_link_libraries(TransportLibrary PUBLIC Boost::date_time)

add_executable(TransportCompany library/main.cpp library/src/Interfejs.cpp)
target_link_libraries(TransportCompany PRIVATE TransportLibrary)

enable_testing()

add_executable(TransportTests
        tests/RepozytoriumTests.cpp
        tests/ZlecenieTests.cpp
        tests/MenedzerZlecenTests.cpp
        tests/IntegracjaTests.cpp
)

target_link_libraries(TransportTests PRIVATE TransportLibrary Boost::date_time Boost::unit_test_framework)

add_test(NAME AllTransportTests COMMAND TransportTests)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/dane DESTINATION ${CMAKE_CURRENT_BINARY_DIR})