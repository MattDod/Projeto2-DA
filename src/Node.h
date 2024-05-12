//
// Created by kamert on 12-05-2024.
//

#ifndef PROJETODA2_NODE_H
#define PROJETODA2_NODE_H
class Node {
public:

    Node(std::string name, double id, std::string code, double demand, double population, NodeType type);
    Node(std::string name, std::string municipality, double id, std::string code, double maxDeliveryCapacity, NodeType type); // Constructor for water reservoirs
    Node(double id, std::string code, NodeType type); // Constructor for delivery sites
    Node(std::string code, NodeType type); // Constructor for super source/sink



    std::string getName() const;

    double getId() const;



    Pipeline * addPipe(Node *dest, double capacity, double direction);
    bool isVisited() const;
    void setVisited(bool value);
    void setPath(Pipeline *path);
    std::vector<Pipeline *> getAdj() const;
    std::vector<Pipeline *> getIncoming() const;

private:
    std::string name;
    std::string municipality;
    std::string code;
    double id;

    double maxDeliveryCapacity; // For water reservoirs
    double demand; // For delivery sites
    double population; // For delivery sites and cities
    double currentFlow; // For pumping stations
    bool visited = false;
    Pipeline *path = nullptr;
    std::vector<Edge *> adj;
    std::vector<Edge *> incoming;
};
#endif //PROJETODA2_NODE_H
