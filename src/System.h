/**
 * @file System.h
 * @brief Header file for the System class.
 *
 * This file defines the System class, which represents the main system controlling the graph operations.
 *
 * @date 12-05-2024
 */

#ifndef PROJETODA2_SYSTEM_H
#define PROJETODA2_SYSTEM_H

#include "Graph.h"
using namespace std;

/**
 * @class System
 * @brief Represents the main system controlling the graph operations.
 */
class System {
private:
    Graph graph; ///< The graph managed by the system.

public:
    /**
     * @brief Constructor for the System class.
     * @details The time complexity of this function is O(1)
     */
    System();

    /**
     * @brief Enum defining different types of graphs.
     */
    enum graph_type {
        toy, ///< Toy graph.
        medium, ///< Medium graph.
        real ///< Real graph.
    };

    /**
     * @brief Getter method to retrieve the graph managed by the system.
     *
     * @return The graph managed by the system.
     * @details The time complexity of this function is O(1)
     */
    Graph getGraph() const { return graph; };

    /**
     * @brief Method to parse a graph from a file.
     *
     * @param filename The name of the file containing graph data.
     * @param type The type of graph to parse.
     * @param limit The maximum number of nodes to parse (used for medium graphs) -> default to -1 do differentiate limited to unlimited reads.
     * @details The time complexity of this function is O(V + E), where V is the number of nodes and E is the number of edges.
     */
    void parseGraph(const string &filename, enum graph_type type, int limit = -1);

    /**
     * @brief Method to parse graph edges from a file.
     *
     * @param filename The name of the file containing graph edge data.
     * @param skip Boolean value indicating whether to skip the first line of the file (for real world graphs).
     * @details The time complexity of this function is O(E), where E is the number of edges.
     */
    void parseGraphEdges(const string &filename, bool skip);

    /**
     * @brief Method to call the triangular approximation algorithm.
     */
    void callTriangularApproximation();

    /**
     * @brief Method to call the backtracking algorithm.
     */
    void callBacktracking();

    /**
     * @brief Method to call the Christofides algorithm.
     */
    void callChristofides();

    /**
     * @brief Method to call the nearest neighbor algorithm.
     *
     * @param node The starting node for the algorithm.
     */
    void callNearestNeighbor(int node);

    /**
     * @brief Method to close the system.
     * @details The time complexity of this function is O(1)
     */
    void close();
};

#endif //PROJETODA2_SYSTEM_H
