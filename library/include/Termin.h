#ifndef POBI_TERMIN_H
#define POBI_TERMIN_H

#pragma once
#include <boost/date_time/posix_time/posix_time.hpp>

namespace pt = boost::posix_time;
namespace gr = boost::gregorian;

class Termin {
private:
    pt::ptime dataOd;
    pt::ptime dataDo;

public:
    Termin(pt::ptime dataOd, pt::ptime dataDo);

    // Sprawdzanie czy nie koliduje z innym juz istniejacym terminem
    bool czyKoliduje(const Termin &inny) const;

};

#endif //POBI_TERMIN_H