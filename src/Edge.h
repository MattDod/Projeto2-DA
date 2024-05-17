/**
 * @file Edge.h
 * @brief Header file for the Edge class.
 *
 * This file defines the Edge class, which represents a connection between two nodes in a graph.
 *
 * @date 12-05-2024
 */

#ifndef PROJETODA2_EDGE_H
#define PROJETODA2_EDGE_H

#include "Node.h"
class Node;

/**
 * @class Edge
 * @brief Represents a connection between two nodes in a graph.
 */
class Edge {
public:
    /**
     * @brief Constructor for the Edge class.
     *
     * @param source Pointer to the source node.
     * @param target Pointer to the target node.
     * @param distance The distance between the source and target nodes.
     *
     * @details The time complexity of this function is O(1)
     *
     * This constructor initializes an Edge object with the provided source, target, and distance.
     */
    Edge(Node *source, Node *target, double distance);

    /**
     * @brief Gets the source node of the edge.
     *
     * @return Pointer to the source node.
     *
     * @details The time complexity of this function is O(1)
     *
     * This method retrieves the source attribute of the Edge object.
     */
    Node *getSourceNode() const;

    /**
     * @brief Gets the destination node of the edge.
     *
     * @return Pointer to the destination node.
     *
     * @details The time complexity of this function is O(1)
     *
     * This method retrieves the target attribute of the Edge object.
     */
    Node *getDest() const;

    /**
     * @brief Gets the distance associated with the edge.
     *
     * @return The distance between the source and target nodes.
     *
     * @details The time complexity of this function is O(1)
     *
     * This method retrieves the distance attribute of the Edge object.
     */
    double getDistance() const;

    /**
     * @brief Sets the capacity of the edge.
     *
     * @param capacity The capacity to be set.
     *
     * @details The time complexity of this function is O(1)
     *
     * This method sets the capacity attribute of the Edge object.
     */
    void setCapacity(double capacity);

    /**
     * @brief Sets the flow through the edge.
     *
     * @param flow The flow to be set.
     *
     * @details The time complexity of this function is O(1)
     *
     * This method sets the flow attribute of the Edge object.
     */
    void setFlow(double flow);

private:
    Node *source; ///< Pointer to the source node.
    Node *target; ///< Pointer to the target node.
    double distance; ///< The distance between the source and target nodes.
};

#endif //PROJETODA2_EDGE_H
