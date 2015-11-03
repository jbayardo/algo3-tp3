#ifndef ALGO3_TP3_DGRAPH_H
#define ALGO3_TP3_DGRAPH_H

#include <vector>
#include <list>
#include <algorithm>
#include <queue>

class DGraph {
public:
    DGraph() : adjacency(0) {};
    DGraph(std::size_t vertices) : adjacency(vertices) { };

    std::size_t inline size() const {
        return adjacency.size();
    }

    std::size_t inline outDegree(std::size_t a) const {
        return adjacency[a].size();
    }

    std::size_t inline inDegree(std::size_t a) const {
        return parents[a].size();
    }

    void connect(std::size_t a, std::size_t b) {
#ifdef DEBUG
        if (std::find(adjacency[a].begin(), adjacency[a].end(), b) != adjacency[a].end()) {
            throw std::runtime_error("Nodes already connected");
        }
#endif

        adjacency[a].push_back(b);
        parents[b].push_back(a);
    }

    const std::list<std::size_t>& neighbors(std::size_t a) const { return adjacency[a]; }
    // std::list<Graph> components(Graph &graph);
    // std::list<std::size_t> neighbors(std::size_t a) const { return adjacency[a]; }
private:
    std::vector<std::list<std::size_t>> adjacency;
    std::vector<std::list<std::size_t>> parents;
};

/**
 * @param graph Grafo de entrada
 * @complexity \Omega(n + m)
 * @return Lista de componentes conexas del grafo, como grafos separados
 */

std::list<DGraph> components(DGraph &graph);

#endif //ALGO3_TP3_GRAPH_H
