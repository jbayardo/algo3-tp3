#ifndef ALGO3_TP3_GRAPH_H
#define ALGO3_TP3_GRAPH_H

#include <vector>
#include <list>
#include <algorithm>
#include <queue>

class Graph {
public:
    Graph() : adjacency(0) {};
    Graph(std::size_t vertices) : adjacency(vertices) { };

    std::size_t size() const { return adjacency.size(); }
    std::size_t degree(std::size_t a) const { return adjacency[a].size(); }

    void connect(std::size_t a, std::size_t b) {
#ifdef DEBUG
        if (std::find(adjacency[a].begin(), adjacency[a].end(), b) != adjacency[a].end()) {
            throw std::runtime_error("Nodes already connected");
        }
#endif

        adjacency[a].push_back(b);
        adjacency[b].push_back(a);
    }

    const std::list<std::size_t>& neighbors(std::size_t a) const { return adjacency[a]; }
    // std::list<Graph> components(Graph &graph);
    // std::list<std::size_t> neighbors(std::size_t a) const { return adjacency[a]; }
private:
    std::vector<std::list<std::size_t>> adjacency;
};

/**
 * @param graph Grafo de entrada
 * @complexity \Omega(n + m)
 * @return Lista de componentes conexas del grafo, como grafos separados
 */

std::list<Graph> components(Graph &graph);

#endif //ALGO3_TP3_GRAPH_H
