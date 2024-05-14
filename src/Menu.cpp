//
// Created by kamert on 12-05-2024.
//
#include <iostream>
#include <iomanip>
#include "System.h"
#include "Menu.h"

using namespace std;

void Menu::start(System system){
    while(true) {
        cout << endl << "Menu:" << endl << endl;
        cout << "1: Backtracking algorithm " << endl;
        cout << "2: TSP Triangular Approximation" << endl;
        cout << "0: Quit" << endl;
        int choice;
        cin >> choice;
        while (0 < choice && choice > 2) {
            cout << "Please select a valid choice." << endl;
            cin >> choice;
        }
        switch (choice) {
            case 0:
                return;
            case 1:
                system.callBacktracking();
                break;
            case 2:
                system.callTriangularApproximation();
                break;
        }
    }
}
