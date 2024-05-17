/**
 * @file Graph.h
 * @brief Header file for the Graph class.
 *
 * This file defines the Graph class, which represents a graph data structure.
 *
 * @date 12-05-2024
 */

#ifndef PROJETODA2_GRAPH_H
#define PROJETODA2_GRAPH_H

#include <vector>
#include <queue>
#include <string>
#include "Node.h"

/**
 * @class Graph
 * @brief Represents a graph data structure.
 */
class Graph {
private:
public:
    /**
     * @brief Method to add a node to the graph.
     *
     * @param node Pointer to the node to be added.
     *
     * @details The time complexity of this function is O(1)
     *
     * This method adds a node to the graph.
     */
    void addNode(Node *node);

    /**
     * @brief Method to add an edge between two nodes.
     *
     * @param source The ID of the source node.
     * @param dest The ID of the destination node.
     * @param latitude The latitude of the destination node.
     * @param longitude The longitude of the destination node.
     * @return True if the edge is added successfully, false otherwise.
     *
     * @details The time complexity of this function is O(1)
     *
     * This method adds an edge between two nodes in the graph.
     */
    bool addEdge(std::string &source, std::string &dest, double &latitude, double &longitude);

    std::vector<Node *> nodes; ///< Vector containing pointers to all nodes in the graph.


    /**
     * @brief Getter method to retrieve all nodes in the graph.
     *
     * @return A vector containing pointers to all nodes in the graph.
     *
     * @details The time complexity of this function is O(1)
     *
     * This method retrieves all nodes in the graph.
     */
    const std::vector<Node *> getNodes() const;

    /**
     * @brief Method to find a node by its ID.
     *
     * @param id The ID of the node to find.
     * @return Pointer to the node if found, nullptr otherwise.
     *
     * @details The time complexity of this function is O(n)
     *
     * This method finds a node in the graph by its ID.
     */
    Node *findNode(const int &id) const;

    /**
     * @brief Method to add a bidirectional edge between two nodes.
     *
     * @param id The ID of the source node.
     * @param id2 The ID of the destination node.
     * @param dist The distance between the source and destination nodes.
     * @return True if the edge is added successfully, false otherwise.
     *
     * @details The time complexity of this function is O(1)
     *
     * This method adds a bidirectional edge between two nodes in the graph.
     */
    bool addBidirectionalEdge(int id, int id2, double dist);

    /**
     * @brief Method to clear the graph.
     *
     * @details The time complexity of this function is O(n)
     *
     * This method clears all nodes and edges from the graph.
     */
    void clear();

    /**
     * @brief Method to copy another graph.
     *
     * @param g The graph to be copied.
     *
     * @details The time complexity of this function is O(n^2)
     *
     * This method copies all nodes and edges from another graph.
     */
    void copyGraph(const Graph &g);

    /**
     * @brief Method to solve the Traveling Salesman Problem (TSP) using backtracking.
     *
     * @param path The resulting TSP path.
     * @return The total distance of the TSP path.
     *
     * @details The time complexity of this function is O(n!)
     *
     * This method solves the TSP using backtracking algorithm.
     */
    double tspBT(std::vector<int> &path);

    /**
     * @brief Helper method for solving the TSP using backtracking.
     *
     * @param path The current path being explored.
     * @param currentNode The ID of the current node.
     * @param curSum The current sum of distances.
     * @param bestSum The best sum found so far.
     * @param nodesVisited The number of nodes visited.
     * @return The best sum found.
     *
     * @details The time complexity of this function is O(n)
     *
     * This method is a helper function for TSP backtracking algorithm.
     */
    double tspBacktracking(std::vector<int> &path, int currentNode, double curSum, double bestSum, int nodesVisited);

    /**
     * @brief Method to calculate the Haversine distance between two nodes.
     *
     * @param node1 Pointer to the first node.
     * @param node2 Pointer to the second node.
     * @return The Haversine distance between the two nodes.
     *
     * @details The time complexity of this function is O(1)
     *
     * This method calculates the Haversine distance between two nodes.
     */
    double haversineDistance(const Node* node1, const Node* node2);

    /**
     * @brief Method to solve the TSP using triangular approximation.
     *
     * @param path The resulting TSP path.
     * @return The total distance of the TSP path.
     *
     * @details The time complexity of this function is O(n^2 * log n)
     *
     * This method solves the TSP using triangular approximation algorithm.
     */
    double tspTriangularApproximation(std::vector<int> &path);

    double tspChristofides(std::vector<int> &path);
};

#endif //PROJETODA2_GRAPH_H
