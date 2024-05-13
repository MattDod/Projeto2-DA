#include <iostream>
#include "Menu.h"
#include <chrono>

int main() {
    Menu menu;

    System system;
    auto timestartshere = chrono::high_resolution_clock::now();
    menu.start(system);
    auto timefinishhere = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = timefinishhere - timestartshere;
    cout << "Elapsed Time: " << elapsed.count() << "\n";
    return 0;
}
