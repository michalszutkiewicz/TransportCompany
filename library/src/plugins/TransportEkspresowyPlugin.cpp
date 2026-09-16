#include "TransportEkspresowy.h"
#include <boost/dll/alias.hpp>
#include <memory>

std::shared_ptr<Usluga> createService(const std::string& nazwa, double dystans, double stawka, double extra) {
    return std::make_shared<TransportEkspresowy>(nazwa, dystans, stawka, extra);
}

const char* getServiceName() {
    return "Ekspresowy";
}

extern "C" BOOST_SYMBOL_EXPORT const char* get_transport_name() {
    return "Ekspresowy";
}

extern "C" BOOST_SYMBOL_EXPORT std::shared_ptr<Usluga> create_transport_service(
    const std::string& nazwa, double dystans, double stawka, double extra)
{
    return std::make_shared<TransportEkspresowy>(nazwa, dystans, stawka, extra);
}