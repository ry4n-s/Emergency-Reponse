#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "vertex.hpp"

class Graph {
public:
    int numVertices; //number of vertices
    Vertex* vertices; //dynamic array of vertices

    Graph();
    void addVertex(int id);
    void addEdge(int src, int dest, double distance, double speed);
    ~Graph();
    void printAdjacentVertices(int vertexId);
    void deleteVertex(int vertexId);
    int* findShortestPath(int src, int dest); //returns an array of vertices representing the path
    bool isEdge(int u, int v);
    double weight(int u, int v);
    bool updateTraffic(int a, int b, double A);
    int getNumVertices();
};

#endif // GRAPH_HPP
