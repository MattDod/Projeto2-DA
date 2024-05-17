#include <iostream>
#include <iomanip>
#include "System.h"
#include "Menu.h"

using namespace std;

void Menu::start(System system) {
    while (true) {
        system.close();
        cout << "========================================" << endl;
        cout << "             Graph Options              " << endl;
        cout << "========================================" << endl << endl;
        cout << "1: Toy Graphs" << endl;
        cout << "2: Medium Graphs" << endl;
        cout << "3: Real Graphs" << endl;
        cout << "0: Quit" << endl;
        int choice;
        cin >> choice;
        while (choice < 0 || choice > 3) {
            cout << "Please select a valid choice." << endl;
            cin >> choice;
        }
        switch (choice) {
            case 0:
                return;
            case 1:
                toyGraphMenu(system);
                break;
            case 2:
                mediumGraphMenu(system);
                break;
            case 3:
                realGraphMenu(system);
                break;
        }
    }
}

void Menu::toyGraphMenu(System system) {
    system.close();
    cout << endl << "========================================" << endl;
    cout << "           Toy Graph Options            " << endl;
    cout << "========================================" << endl << endl;
    cout << "1: Shipping" << endl;
    cout << "2: Tourism" << endl;
    cout << "3: Stadiums" << endl;
    int toyChoice;
    cin >> toyChoice;
    switch (toyChoice) {
        case 1:
            system.parseGraph("../data/toy_graphs/shipping.csv",  system.toy);
            break;
        case 2:
            system.parseGraph("../data/toy_graphs/tourism.csv",  system.toy);
            break;
        case 3:
            system.parseGraph("../data/toy_graphs/stadiums.csv",  system.toy);
            break;
        default:
            cout << "Invalid choice." << endl;
            break;
    }
    functionsMenu(system);
}

void Menu::mediumGraphMenu(System system) {
    system.close();
    system.parseGraph("../data/medium_graphs/nodes.csv",  system.medium);
    cout << endl << "========================================" << endl;
    cout << "         Medium Graph Options           " << endl;
    cout << "========================================" << endl << endl;
    cout << "1: 25 edges" << endl;
    cout << "2: 50 edges" << endl;
    cout << "3: 75 edges" << endl;
    cout << "4: 100 edges" << endl;
    cout << "5: 200 edges" << endl;
    cout << "6: 300 edges" << endl;
    cout << "7: 400 edges" << endl;
    cout << "8: 500 edges" << endl;
    cout << "9: 600 edges" << endl;
    cout << "10: 700 edges" << endl;
    cout << "11: 800 edges" << endl;
    cout << "12: 900 edges" << endl;
    int mediumChoice;
    cin >> mediumChoice;
    switch (mediumChoice) {
        case 1:
            system.parseGraphEdges("../data/medium_graphs/edges_25.csv");
            break;
        case 2:
            system.parseGraphEdges("../data/medium_graphs/edges_50.csv");
            break;
        case 3:
            system.parseGraphEdges("../data/medium_graphs/edges_75.csv");
            break;
        case 4:
            system.parseGraphEdges("../data/medium_graphs/edges_100.csv");
            break;
        case 5:
            system.parseGraphEdges("../data/medium_graphs/edges_200.csv");
            break;
        case 6:
            system.parseGraphEdges("../data/medium_graphs/edges_300.csv");
            break;
        case 7:
            system.parseGraphEdges("../data/medium_graphs/edges_400.csv");
            break;
        case 8:
            system.parseGraphEdges("../data/medium_graphs/edges_500.csv");
            break;
        case 9:
            system.parseGraphEdges("../data/medium_graphs/edges_600.csv");
            break;
        case 10:
            system.parseGraphEdges("../data/medium_graphs/edges_700.csv");
            break;
        case 11:
            system.parseGraphEdges("../data/medium_graphs/edges_800.csv");
            break;
        case 12:
            system.parseGraphEdges("../data/medium_graphs/edges_900.csv");
            break;
        default:
            cout << "Invalid choice." << endl;
            break;
    }
    functionsMenu(system);
}

void Menu::realGraphMenu(System system) {
    system.close();
    // Placeholder for real graph menu
    functionsMenu(system);
}

void Menu::functionsMenu(System system) {
    while (true) {
        cout << endl << "========================================" << endl;
        cout << "             Functions Menu             " << endl;
        cout << "========================================" << endl << endl;
        cout << "1: Backtracking algorithm " << endl;
        cout << "2: TSP Triangular Approximation" << endl;
        cout << "3: Christofides Algorithm" << endl;
        cout << "0: Quit" << endl;
        int choice;
        cin >> choice;
        while (choice < 0 || choice > 3) {
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
            case 3:
                system.callChristofides();
                break;
        }
    }
}
