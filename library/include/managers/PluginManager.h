#ifndef TRANSPORTCOMPANY_PLUGINMANAGER_H
#define TRANSPORTCOMPANY_PLUGINMANAGER_H
#define BOOST_DLL_USE_STD_FS

#pragma once
#include "Usluga.h"
#include <boost/dll/shared_library.hpp>
#include <filesystem>
#include <functional>
#include <map>
#include <memory>
#include <vector>
#include <iostream>

namespace fs = std::filesystem;

class PluginManager {
public:
    // Sygnatura funkcji fabrycznej (musi zgadzać się z sygnaturą w pluginie)
    using FactoryFunc = std::shared_ptr<Usluga>(const std::string&, double, double, double);

    void zaladujWtyczki(const fs::path& sciezkaKatalogu) {
        if (!fs::exists(sciezkaKatalogu)) {
            std::cerr << "[PluginManager] Katalog nie istnieje: " << sciezkaKatalogu << "\n";
            return;
        }

        for (const auto& plik : fs::directory_iterator(sciezkaKatalogu)) {
            auto rozszerzenie = plik.path().extension();
            if (rozszerzenie == ".dll" || rozszerzenie == ".so") {
                try {
                    // Ładowanie biblioteki dynamicznej w runtime
                    auto biblioteka = std::make_shared<boost::dll::shared_library>(
                        plik.path().string(),
                        boost::dll::load_mode::append_decorations
                    );

                    // Sprawdzenie, czy eksportuje wymagane symbole fabryczne
                    if (biblioteka->has("create_transport_service") && biblioteka->has("get_transport_name")) {
                        auto pobierzNazwe = biblioteka->get<const char*()>("get_transport_name");
                        std::string nazwaTypu = pobierzNazwe();

                        fabryki_[nazwaTypu] = biblioteka->get<FactoryFunc>("create_transport_service");
                        zaladowaneBiblioteki_.push_back(biblioteka); // Utrzymujemy bibliotekę w pamięci

                        std::cout << "[PluginManager] Zaladowano wtyczke: " << nazwaTypu
                                  << " (" << plik.path().filename().string() << ")\n";
                    }
                } catch (const std::exception& e) {
                    std::cerr << "[PluginManager] Blad ladowania " << plik.path() << ": " << e.what() << "\n";
                }
            }
        }
    }

    std::shared_ptr<Usluga> utworzUsluge(const std::string& typ, const std::string& nazwa, double dystans, double stawka, double extra = 0.0) {
        if (fabryki_.find(typ) != fabryki_.end()) {
            return fabryki_[typ](nazwa, dystans, stawka, extra);
        }
        return nullptr;
    }

    std::vector<std::string> pobierzDostepneTypy() const {
        std::vector<std::string> lista;
        for (const auto& [nazwa, _] : fabryki_) {
            lista.push_back(nazwa);
        }
        return lista;
    }

private:
    std::map<std::string, std::function<FactoryFunc>> fabryki_;
    inline static std::vector<std::shared_ptr<boost::dll::shared_library>> zaladowaneBiblioteki_;
};

#endif //TRANSPORTCOMPANY_PLUGINMANAGER_H