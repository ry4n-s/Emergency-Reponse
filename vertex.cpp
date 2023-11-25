#include "vertex.hpp"
#include "edge.hpp"

Vertex::Vertex() : id(0), numEdges(0), isDeleted(false), edges(nullptr) {}

Vertex::Vertex(int id) : id(id), isDeleted(false), numEdges(0), edges(nullptr) {}

void Vertex::addEdge(int dest, double distance, double speed) {
    Edge* newEdges = new Edge[numEdges + 1];

    //manually copying the existing edges to the new array
    for (int i = 0; i < numEdges; ++i) {
        newEdges[i].dest = edges[i].dest;
        newEdges[i].distance = edges[i].distance;
        newEdges[i].speed = edges[i].speed;
        newEdges[i].adjustment = edges[i].adjustment;
    }

    //adding the new edge
    newEdges[numEdges++] = Edge(dest, distance, speed);

    //deleting the old edges array and pointing to the new one
    delete[] edges;
    edges = newEdges;
}



Vertex::Vertex(const Vertex& other)
    : id(other.id), numEdges(other.numEdges), edges(nullptr) {
                if (edges) {
            delete[] edges; //prevent memory leak
        }
    if (numEdges > 0) {
        edges = new Edge[numEdges];
        for (int i = 0; i < numEdges; ++i) {
            edges[i] = other.edges[i];
        }
    }
}

Vertex& Vertex::operator=(const Vertex& other) {
    if (this != &other) { //prevent self-assignment
        //free existing resources
        delete[] edges;
                    if (edges) {
                delete[] edges; //prevent memory leak
            }

        //copy data
        id = other.id;
        numEdges = other.numEdges;

        //copy edges (deep copy)
        edges = nullptr;
        if (numEdges > 0) {
            edges = new Edge[numEdges];
            for (int i = 0; i < numEdges; ++i) {
                edges[i] = other.edges[i];
            }
        }
    }
    return *this;
}

//destructor
Vertex::~Vertex() {
    delete[] edges;
}

void Vertex::clearEdges() {
    //deallocate memory used by edges
    delete[] edges;

    //reseta edges array to nullptr and numEdges to 0
    edges = nullptr;
    numEdges = 0;
}
