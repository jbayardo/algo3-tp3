#ifndef ALGO3_TP3_PROBLEM_H
#define ALGO3_TP3_PROBLEM_H

#include "ColorStorage.h"
#include "Graph.h"
#include <vector>
#include <list>
#include <stack>

class Problem {
public:
    Problem(std::string input) {
        std::ifstream handle;
        handle.open(input, std::ifstream::in);

        if (!handle.is_open()) {
            throw std::runtime_error("Fallo al abrir el archivo de tests");
        }

        std::size_t vertices, edges, nColors;

        handle >> vertices >> edges >> nColors;

        if (c <= 0) {
            throw std::runtime_error("Error reading file: number of colors must be higher than 0");
        }

        colors = ColorStorage(vertices);

        for (auto vertex = 0; vertex < vertices; ++vertex) {
            std::size_t readColors;
            handle >> readColors;

            if (readColors <= 0) {
                throw std::runtime_error("Error reading file: number of current colors must be higher than 0");
            }

            std::list<std::size_t> current;

            for (auto color = 0; color < readColors; ++color) {
                std::size_t color;
                handle >> color;

                if (color >= nColors) {
                    throw std::runtime_error("Invalid color number");
                }

                current.push_back(color);
            }

            colors.add(vertex, current);
        }

        graph = Graph(vertices);

        for (auto edge = 0; edge < edges; ++edge) {
            std::size_t from, to;
            handle >> from >> to;

            if (from >= vertices || to >= vertices) {
                throw std::runtime_error("Invalid edge");
            }

            graph.connect(from, to);
        }

        handle.close();
    }

    twoSat() {
        int vertexN = 0;
        for(int x = 0; x < graph.size; ++x) {
            vertexN += graph.neighbors(x).size() == 1? 1 : 4;
        }
        std::vector<int> vertexCourse(vertexN, -1);
        Graph implicationGraph(vertexN);



    }

    korasaju(Graph implicationGraph) {
        std::stack S;
        int now = 0;
        std::vector<bool> checked(implicationGraph.size(), false);
        S.push_back(0);
        while(!S.empty()) {
            
        }
    }
private:
    Graph graph;
    ColorStorage colors;
};


#endif //ALGO3_TP3_PROBLEM_H
