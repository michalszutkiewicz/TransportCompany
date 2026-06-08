#include <iostream>
#include <memory>
#include "Interfejs.h"

int main() {
    std::cout << "--- System Zarzadzania Firma Transportowa ---" << std::endl;

    InterfejsUI ui;

    ui.uruchom();

    return 0;
}
