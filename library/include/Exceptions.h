/**
* @file Exceptions.h
 * @brief Hierarchia wyjątków dla systemu zarządzania transportem.
 */

#ifndef ATOM_PN_1330_06_EXCEPTIONS_H
#define ATOM_PN_1330_06_EXCEPTIONS_H

#include <stdexcept>
#include <string>

/**
 * @class TransportException
 * @brief Główna klasa bazowa dla wszystkich wyjątków w systemie.
 */
class TransportException : public std::runtime_error {
public:
    explicit TransportException(const std::string& message)
        : std::runtime_error(message) {}
};

/**
 * @class InvalidTermException
 * @brief Wyjątek rzucany, gdy podano nieprawidłowy przedział czasowy.
 */
class InvalidTermException : public TransportException {
public:
    explicit InvalidTermException(const std::string& message)
        : TransportException("Blad terminu: " + message) {}
};

/**
 * @class ResourceUnavailableException
 * @brief Wyjątek rzucany, gdy dany zasób (pojazd, pracownik) jest zajęty.
 */
class ResourceUnavailableException : public TransportException {
public:
    explicit ResourceUnavailableException(const std::string& message)
        : TransportException("Brak dostepnosci zasobu: " + message) {}
};

/**
 * @class PermissionDeniedException
 * @brief Wyjątek rzucany w przypadku braku wymaganych uprawnien (np. brak kategorii prawa jazdy).
 */
class PermissionDeniedException : public TransportException {
public:
    explicit PermissionDeniedException(const std::string& message)
        : TransportException("Brak uprawnien: " + message) {}
};

#endif //ATOM_PN_1330_06_EXCEPTIONS_H