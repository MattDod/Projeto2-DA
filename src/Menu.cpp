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
            system.parseGraph("../data/medium_graphs/nodes.csv",  system.medium, 25);
            system.parseGraphEdges("../data/medium_graphs/edges_25.csv", false);
            break;
        case 2:
            system.parseGraph("../data/medium_graphs/nodes.csv",  system.medium, 50);
            system.parseGraphEdges("../data/medium_graphs/edges_50.csv", false);
            break;
        case 3:
            system.parseGraph("../data/medium_graphs/nodes.csv",  system.medium, 75);
            system.parseGraphEdges("../data/medium_graphs/edges_75.csv", false);
            break;
        case 4:
            system.parseGraph("../data/medium_graphs/nodes.csv",  system.medium, 100);
            system.parseGraphEdges("../data/medium_graphs/edges_100.csv", false);
            break;
        case 5:
            system.parseGraph("../data/medium_graphs/nodes.csv",  system.medium, 200);
            system.parseGraphEdges("../data/medium_graphs/edges_200.csv", false);
            break;
        case 6:
            system.parseGraph("../data/medium_graphs/nodes.csv",  system.medium, 300);
            system.parseGraphEdges("../data/medium_graphs/edges_300.csv", false);
            break;
        case 7:
            system.parseGraph("../data/medium_graphs/nodes.csv",  system.medium, 400);
            system.parseGraphEdges("../data/medium_graphs/edges_400.csv", false);
            break;
        case 8:
            system.parseGraph("../data/medium_graphs/nodes.csv",  system.medium, 500);
            system.parseGraphEdges("../data/medium_graphs/edges_500.csv", false);
            break;
        case 9:
            system.parseGraph("../data/medium_graphs/nodes.csv",  system.medium, 600);
            system.parseGraphEdges("../data/medium_graphs/edges_600.csv", false);
            break;
        case 10:
            system.parseGraph("../data/medium_graphs/nodes.csv",  system.medium, 700);
            system.parseGraphEdges("../data/medium_graphs/edges_700.csv", false);
            break;
        case 11:
            system.parseGraph("../data/medium_graphs/nodes.csv",  system.medium, 800);
            system.parseGraphEdges("../data/medium_graphs/edges_800.csv", false);
            break;
        case 12:
            system.parseGraph("../data/medium_graphs/nodes.csv",  system.medium, 900);
            system.parseGraphEdges("../data/medium_graphs/edges_900.csv", false);
            break;
        default:
            cout << "Invalid choice." << endl;
            break;
    }
    functionsMenu(system);
}

void Menu::realGraphMenu(System system) {
    cout << endl << "========================================" << endl;
    cout << "        Real-World Graph Options        " << endl;
    cout << "========================================" << endl << endl;
    cout << "1: Graph 1" << endl;
    cout << "2: Graph 2" << endl;
    cout << "3: Graph 3" << endl;
    int realChoice;
    cin >> realChoice;
    switch (realChoice) {
        case 1:
            system.parseGraph("../data/real_world_graphs/graph1/nodes.csv",  system.real);
            system.parseGraphEdges("../data/real_world_graphs/graph1/edges.csv", true);
            break;
        case 2:
            system.parseGraph("../data/real_world_graphs/graph2/nodes.csv",  system.real);
            system.parseGraphEdges("../data/real_world_graphs/graph2/edges.csv", true);
            break;
        case 3:
            system.parseGraph("../data/real_world_graphs/graph3/nodes.csv",  system.real);
            system.parseGraphEdges("../data/real_world_graphs/graph3/edges.csv", true);
            break;
        default:
            cout << "Invalid choice." << endl;
            break;
    }
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
        cout << "4: Nearest Neighbor Algorithm" << endl;
        cout << "0: Quit" << endl;
        int choice;
        cin >> choice;
        while (choice < 0 || choice > 4) {
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
            case 4:
                cout << "Enter the starting node: ";
                int node;
                cin >> node;
                while(system.getGraph().findNode(node) == nullptr) {
                    cout << "Invalid node. Please enter a valid node: ";
                    cin >> node;
                }
                system.callNearestNeighbor(node);
                break;
        }
    }
}
