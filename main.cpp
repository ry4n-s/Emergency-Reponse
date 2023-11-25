#include "graph.hpp"
#include "illegal_exception.hpp"
#include <iostream>
#include <fstream>
#include <string>

int main() {
    Graph myGraph;
    std::string command;

    while (std::cin >> command) {
        if (command == "END") {
            break;  //ends the program
        } else if (command == "LOAD") {
            std::string filename;
            std::cin >> filename;
            std::ifstream file(filename);

            if (file) {
                int a, b;
                double d, s;

                //load edges from file
                while (file >> a >> b >> d >> s) {
                    myGraph.addEdge(a, b, d, s);
                }
                file.close();
                std::cout << "success" << std::endl;
            } else {
                std::cout << "File not found" << std::endl;
            }
            continue;
        }

        if (command == "INSERT") {
            int a, b;
            double d, s;
            std::cin >> a >> b >> d >> s;

            try {
                //insert an edge, throw exception if arguments are illegal
                if (a <= 0 || a > 500000 || b <= 0 || b > 500000 || d <= 0 || s <= 0) {
                    throw illegal_exception();
                }
                myGraph.addEdge(a, b, d, s);
                std::cout << "success" << std::endl;
            } catch (const illegal_exception& ex) {
                std::cout << ex.what() << std::endl;
            }
        } else if (command == "PRINT") {
            int a;
            std::cin >> a;

            try {
                //print adjacent vertices, throw exception if vertex is illegal
                if (a <= 0 || a > 500000) {
                    throw illegal_exception();
                }
                myGraph.printAdjacentVertices(a);
            } catch (const illegal_exception& ex) {
                std::cout << ex.what() << std::endl;
            }
        } else if (command == "DELETE") {
            int a;
            std::cin >> a;

            try {
                //delete a vertex, throw exception if vertex is illegal
                if (a <= 0 || a > 500000) {
                    throw illegal_exception();
                }
                myGraph.deleteVertex(a);
            } catch (const illegal_exception& ex) {
                std::cout << ex.what() << std::endl;
            }
        } else if (command == "PATH") {
            int src, dest;
            std::cin >> src >> dest;

            try {
                //find path, throw exception if vertices are illegal
                if (src <= 0 || src > 500000 || dest <= 0 || dest > 500000) {
                    throw illegal_exception();
                }

                int* parent = myGraph.findShortestPath(src - 1, dest - 1);
                if (!parent) {
                    std::cout << "failure" << std::endl;
                    continue;
                }

                if (parent[dest - 1] == -1) {
                    std::cout << "failure" << std::endl;
                } else {
                    int pathSize = 0;
                    for (int current = dest - 1; current != -1; current = parent[current]) {
                        pathSize++;
                    }

                    int* path = new int[pathSize];
                    int current = dest - 1;

                    for (int i = pathSize - 1; i >= 0; --i) {
                        path[i] = current + 1;
                        current = parent[current];
                    }

                    for (int i = 0; i < pathSize; ++i) {
                        std::cout << path[i] << (i < pathSize - 1 ? " " : "");
                    }
                    std::cout << std::endl;
                    delete[] path;
                }
                delete[] parent;
            } catch (const illegal_exception& ex) {
                std::cout << ex.what() << std::endl;
            }
        } else if (command == "TRAFFIC") {
            int a, b;
            double A;
            std::cin >> a >> b >> A;

            //handle traffic update command
            try {
                if (a <= 0 || a > 500000 || b <= 0 || b > 500000) {
                    throw illegal_exception();
                }

                if (A < 0 || A > 1) {
                    std::cout << "failure" << std::endl;
                } else if (myGraph.updateTraffic(a, b, A)) {
                    std::cout << "success" << std::endl;
                } else {
                    std::cout << "failure" << std::endl;
                }
            } catch (const illegal_exception& ex) {
                std::cout << ex.what() << std::endl;
            }
        } else if (command == "UPDATE") {
            std::string filename;
            std::cin >> filename;
            std::ifstream file(filename);
            bool updated = false;

            if (file) {
                int a, b;
                double A;

                //update traffic from file
                while (file >> a >> b >> A) {
                    if (a <= 0 || a > 500000 || b <= 0 || b > 500000 || A < 0 || A > 1) {
                        continue;
                    }
                    if (myGraph.updateTraffic(a, b, A)) {
                        updated = true;
                    }
                }
                file.close();
            } else {
                std::cout << "failure" << std::endl;
                continue;
            }

            std::cout << (updated ? "success" : "failure") << std::endl;
        } else if (command == "LOWEST") {
            int a, b;
            std::cin >> a >> b;

            try {
                //find lowest path weight, throw exception if vertices are illegal
                if (a <= 0 || a > 500000 || b <= 0 || b > 500000) {
                    throw illegal_exception();
                }

                int* parent = myGraph.findShortestPath(a - 1, b - 1);
                if (!parent) {
                    std::cout << "failure" << std::endl;
                    continue;
                }

                if (parent[b - 1] == -1) {
                    std::cout << "failure" << std::endl;
                } else {
                    double totalWeight = 0;
                    for (int current = b - 1; current != a - 1; current = parent[current]) {
                        totalWeight += myGraph.weight(parent[current], current);
                    }
                    std::cout << "lowest is " << totalWeight << std::endl;
                }
                delete[] parent;
            } catch (const illegal_exception& ex) {
                std::cout << ex.what() << std::endl;
            }
        } else {
            std::cout << "illegal argument" << std::endl;
        }
    }

    return 0;
}
