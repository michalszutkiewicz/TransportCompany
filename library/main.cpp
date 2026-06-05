#include <iostream>
#include <memory>
#include "Interfejs.h"

int main() {
    std::cout << "--- System Zarzadzania Firma Transportowa ---" << std::endl;

    // Zgodnie z UML, InterfejsUI zarządza teraz repozytoriami
    // i odpowiada za interakcję z użytkownikiem.
    InterfejsUI ui;
    
    // Uruchomienie głównej pętli programu
    ui.uruchom();

    return 0;
}
