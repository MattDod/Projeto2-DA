/**
 * @file Node.h
 * @brief Header file for the Node class.
 *
 * This file defines the Node class, which represents a node in a graph.
 *
 * @date 12-05-2024
 */

#ifndef PROJETODA2_NODE_H
#define PROJETODA2_NODE_H

#include <string>
#include <vector>
#include "Edge.h"

class Edge;

/**
 * @class Node
 * @brief Represents a node in a graph.
 */
class Node {
public:
    /**
     * @brief Constructor for the Node class.
     *
     * @param id The ID of the node.
     * @details The time complexity of this function is O(1)
     */
    Node(int id);

    /**
     * @brief Constructor for the Node class.
     *
     * @param id The ID of the node.
     * @param longitude The longitude coordinate of the node.
     * @param latitude The latitude coordinate of the node.
     * @details The time complexity of this function is O(1)
     */
    Node(int id, double longitude, double latitude);

    /**
     * @brief Getter method to retrieve the name of the node.
     *
     * @return The name of the node.
     * @details The time complexity of this function is O(1)
     */
    std::string getName() const;

    /**
     * @brief Getter method to retrieve the ID of the node.
     *
     * @return The ID of the node.
     * @details The time complexity of this function is O(1)
     */
    int getId() const;

    /**
     * @brief Method to add an edge between this node and a destination node.
     *
     * @param dest Pointer to the destination node.
     * @param distance The distance to the destination node.
     * @return Pointer to the created edge.
     * @details The time complexity of this function is O(1)
     */
    Edge *addEdge(Node *dest, double distance);

    /**
     * @brief Method to check if the node has been visited.
     *
     * @return True if the node has been visited, false otherwise.
     * @details The time complexity of this function is O(1)
     */
    bool isVisited() const;

    /**
     * @brief Method to set the visited status of the node.
     *
     * @param value The value to set for visited status.
     * @details The time complexity of this function is O(1)
     */
    void setVisited(bool value);

    /**
     * @brief Method to set the path associated with the node.
     *
     * @param value Pointer to the edge representing the path.
     * @details The time complexity of this function is O(1)
     */
    void setPath(Edge *value);

    /**
     * @brief Method to set the distance (used in Prim's algorithm) of the node.
     *
     * @param value
     * @details The time complexity of this function is O(1)
     */
    void setDistance(double value);

    /**
     * @brief Method to retrieve the adjacent edges of the node.
     *
     * @return A vector containing pointers to the adjacent edges.
     * @details The time complexity of this function is O(1)
     */
    std::vector<Edge *> getAdj() const;

    /**
     * @brief Method to retrieve the incoming edges of the node.
     *
     * @return A vector containing pointers to the incoming edges.
     * @details The time complexity of this function is O(1)
     */
    std::vector<Edge *> getIncoming() const;

    /**
     * @brief Getter method to retrieve the latitude coordinate of the node.
     *
     * @return The latitude coordinate of the node.
     * @details The time complexity of this function is O(1)
     */
    double getLatitude() const;

    /**
     * @brief Getter method to retrieve the longitude coordinate of the node.
     *
     * @return The longitude coordinate of the node.
     * @details The time complexity of this function is O(1)
     */
    double getLongitude() const;

    /**
     * @brief Getter method to retrieve the distance associated with the node.
     *
     * @return The distance associated with the node.
     * @details The time complexity of this function is O(1)
     */
    Edge* getPath() const;

    /**
     * @brief Getter method to retrieve the distance associated with the node.
     *
     * @return The distance associated with the node.
     * @details The time complexity of this function is O(1)
     */
     double getDistance() const;

    /**
     * @brief Method to find an edge connecting this node to a destination node.
     *
     * @param dest The destination node ID.
     * @return Pointer to the edge if found, nullptr otherwise.
     * @details The time complexity of this function is O(E), where E is the number of adjacent edges.
     */
    Edge *findEdge(int dest);

    friend class PriorityQueue;

    bool operator < (const Node &node) const {
        return this->distance < node.distance;
    }

private:
    std::string name; ///< The name of the node.
    double longitude; ///< The longitude coordinate of the node.
    double latitude; ///< The latitude coordinate of the node.
    int id; ///< The ID of the node.
    bool visited = false; ///< Flag indicating whether the node has been visited.
    Edge *path = nullptr; ///< Pointer to the edge representing the path associated with the node.
    std::vector<Edge *> adj; ///< Vector containing pointers to adjacent edges.
    std::vector<Edge *> incoming; ///< Vector containing pointers to incoming edges.
    double distance = std::numeric_limits<double>::max(); ///< Distance used in Prim's algorithm.
    int pqIndex = -1; ///< The index of the node in the priority queue.
};

#endif //PROJETODA2_NODE_H
