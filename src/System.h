//
// Created by kamert on 12-05-2024.
//

#ifndef PROJETODA2_SYSTEM_H
#define PROJETODA2_SYSTEM_H

#include "Graph.h"

using namespace std;
class System{


private:
    Graph graph;
public:
    System();
    enum graph_type{
        toy,
        medium,
        real
    };

    void parseGraph(const string &filename, enum graph_type type);
    void parseGraphEdges(const string &filename);
};


#endif //PROJETODA2_SYSTEM_H
