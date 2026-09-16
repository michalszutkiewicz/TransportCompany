#include "TransportStandardowy.h"
#include <boost/dll/alias.hpp>
#include <memory>

// Funkcja fabryczna tworząca instancję usługi
// (Dostosuj parametry konstruktora do swojej klasy, np. dystans, waga)
std::shared_ptr<Usluga> createService(const std::string& nazwa, double dystans, double stawka, double extra) {
    (void)extra; // w transporcie standardowym parametr extra jest ignorowany
    return std::make_shared<TransportStandardowy>(nazwa, dystans, stawka);
}

// Funkcja zwracająca identyfikator/nazwę wyświetlaną w menu
const char* getServiceName() {
    return "Standardowy";
}

// Eksport symboli ze stabilnym C ABI
extern "C" BOOST_SYMBOL_EXPORT const char* get_transport_name() {
    return "Standardowy";
}

extern "C" BOOST_SYMBOL_EXPORT std::shared_ptr<Usluga> create_transport_service(
    const std::string& nazwa, double dystans, double stawka, double extra)
{
    (void)extra;
    return std::make_shared<TransportStandardowy>(nazwa, dystans, stawka);
}