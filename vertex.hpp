#ifndef VERTEX_HPP
#define VERTEX_HPP

#include "edge.hpp"

class Vertex {
public:
    int id; //vertex identifier
    bool isDeleted;
    int numEdges; //number of edges
    Edge* edges; //dynamic array of edges

    Vertex();
    Vertex(int id);
    void addEdge(int dest, double distance, double speed);
    ~Vertex();
    Vertex(const Vertex& other);
    Vertex& operator=(const Vertex& other);
    void removeEdge(int dest);
    void clearEdges();
};

#endif // VERTEX_HPP
