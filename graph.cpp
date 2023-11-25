#include "graph.hpp"
#include "minheap.hpp"
#include <iostream>
#define MAX_DIST 1e18

//constructor: initializes the graph with no vertices
Graph::Graph() : numVertices(0), vertices(nullptr) {}

//adds a vertex with the given id to the graph
void Graph::addVertex(int id) {
    int index = id - 1;  //0-based index

    //expand the array if the vertex ID is beyond the current array size
    if (index >= numVertices) {
        Vertex* newVertices = new Vertex[index + 1];
        for (int i = 0; i < numVertices; ++i) {
            newVertices[i] = vertices[i];  //copy existing vertices
        }
        //initialize new vertices
        for (int i = numVertices; i <= index; ++i) {
            newVertices[i].id = i;
            newVertices[i].isDeleted = false;
        }
        delete[] vertices;
        vertices = newVertices;
        numVertices = index + 1;  //update the number of vertices
    }
}

//adds an edge between src and dest with given distance and speed
void Graph::addEdge(int src, int dest, double distance, double speed) {
    src--; dest--;  //0-based indexing

    //restore and clear edges if vertices were previously deleted
    if (src < numVertices && vertices[src].isDeleted) {
        vertices[src].clearEdges();
        vertices[src].isDeleted = false;
    }
    if (dest < numVertices && vertices[dest].isDeleted) {
        vertices[dest].clearEdges();
        vertices[dest].isDeleted = false;
    }

    //add vertices if they don't exist
    addVertex(src + 1); //convert back to 1-based indexing when adding
    addVertex(dest + 1);

    //helper function to add an edge to a vertex
    auto addEdgeToVertex = [&](int from, int to) {
        bool edgeExists = false;
        for (int i = 0; i < vertices[from].numEdges; ++i) {
            if (vertices[from].edges[i].dest == to) {
                vertices[from].edges[i].distance = distance;
                vertices[from].edges[i].speed = speed;
                edgeExists = true;
                break;
            }
        }
        if (!edgeExists) {
            vertices[from].addEdge(to, distance, speed);
        }
    };

    //add edge to src and dest vertices
    addEdgeToVertex(src, dest);
    if (src != dest) {
        addEdgeToVertex(dest, src);
    }
}

//destructor: cleans up allocated memory
Graph::~Graph() {
    delete[] vertices;
}

//prints vertices adjacent to the given vertex
void Graph::printAdjacentVertices(int vertexId) {
    int index = vertexId - 1; //0-based indexing
    if (index >= 0 && index < numVertices && !vertices[index].isDeleted) {
        for (int i = 0; i < vertices[index].numEdges; ++i) {
            std::cout << (vertices[index].edges[i].dest + 1) << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "failure" << std::endl;
    }
}

//deletes a vertex by marking it as deleted
void Graph::deleteVertex(int vertexId) {
    int index = vertexId - 1; //0-based indexing
    if (index >= 0 && index < numVertices) {
        vertices[index].isDeleted = true;
        for (int i = 0; i < numVertices; ++i) {
            if (i != index) {
                vertices[i].removeEdge(vertexId); //remove edges to the deleted vertex
            }
        }
        std::cout << "success" << std::endl;
    } else {
        std::cout << "failure" << std::endl;
    }
}

void Vertex::removeEdge(int destId) {
    //0-based index
    destId--; 

    int indexToRemove = -1;
    for (int i = 0; i < numEdges; ++i) {
        if (edges[i].dest == destId) {
            indexToRemove = i;
            break;
        }
    }

    if (indexToRemove != -1) {
        for (int i = indexToRemove; i < numEdges - 1; ++i) {
            edges[i] = edges[i + 1]; //shift elements to cover the removed edge
        }
        numEdges--; //decrease the number of edges
    }
}

int* Graph::findShortestPath(int src, int dest) {
    //checks for valid vertices
    if (src < 0 || src >= numVertices || dest < 0 || dest >= numVertices) {
        return nullptr;
    }

    double* dist = new double[numVertices];
    bool* sptSet = new bool[numVertices];
    int* parent = new int[numVertices];
    MinHeap minHeap(numVertices);

    for (int i = 0; i < numVertices; i++) {
        dist[i] = MAX_DIST;
        sptSet[i] = false;
        parent[i] = -1;
        minHeap.insertKey(i, dist[i]);
    }

    //starts from the source vertex
    dist[src] = 0.0;
    minHeap.decreaseKey(src, 0.0);
    parent[src] = -1;


    while (!minHeap.isEmpty()) {
        int u = minHeap.extractMin();

        sptSet[u] = true;

        for (int v = 0; v < numVertices; v++) {
            if (!sptSet[v] && isEdge(u, v) && dist[u] + weight(u, v) < dist[v]) {
                parent[v] = u;
                dist[v] = dist[u] + weight(u, v);
                minHeap.decreaseKey(v, dist[v]);
            }
        }
    }

    delete[] dist;
    delete[] sptSet;
    return parent;
}

bool Graph::isEdge(int u, int v) {
    //internal 0-based indexing
    if (u < 0 || u >= numVertices) return false; //check for out-of-bounds access

    for (int i = 0; i < vertices[u].numEdges; ++i) {
        if (vertices[u].edges[i].dest == v) {
            return true;
        }
    }
    return false;
}

double Graph::weight(int u, int v) {
    for (int i = 0; i < vertices[u].numEdges; ++i) {
        if (vertices[u].edges[i].dest == v) {
            //adjusts the weight based on the traffic adjustment factor
            return vertices[u].edges[i].distance / vertices[u].edges[i].adjustment;
        }
    }
    return MAX_DIST; //if no edge is found, return a large value (infinity) representing no connection
}

bool Graph::updateTraffic(int a, int b, double A) {
    //0-based indexing
    a--; b--;

    bool updated = false;
    if (a < 0 || a >= numVertices || b < 0 || b >= numVertices || A < 0 || A > 1) {
        return false;
    }

    //updates both directions for an undirected graph
    for (int i = 0; i < vertices[a].numEdges; ++i) {
        if (vertices[a].edges[i].dest == b) {
            vertices[a].edges[i].adjustment = A;
            updated = true;
        }
    }
    for (int i = 0; i < vertices[b].numEdges; ++i) {
        if (vertices[b].edges[i].dest == a) {
            vertices[b].edges[i].adjustment = A;
            updated = true;
        }
    }

    return updated;
}

int Graph::getNumVertices() {
        return numVertices;
}
