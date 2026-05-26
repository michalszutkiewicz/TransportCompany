#include "../include/Termin.h"
#include <stdexcept>

Termin::Termin(pt::ptime dataOd, pt::ptime dataDo) : dataOd(dataOd), dataDo(dataDo) {
    // data początkowa nie może być późniejsza niż data końcowa.
    if (this->dataOd > this->dataDo) {
        throw std::invalid_argument("Data poczatkowa nie moze byc pozniejsza niz data koncowa!");
    }
}

bool Termin::czyKoliduje(const Termin &inny) const {
    // używamy ostrych nierówności, co pozwala na płynne "przekazanie" zasobu,
    // jeśli inny termin zaczyna się dokładnie w momencie zakończenia obecnego.
    return (this->dataOd < inny.dataDo) && (this->dataDo > inny.dataOd);
}