#include <algorithm>
#include "Graph.h"

Graph::Graph() : adjacency(0) { }

Graph::Graph(std::size_t vertices) : adjacency(vertices) { }

void Graph::connect(std::size_t a, std::size_t b) {
#ifdef DEBUG
    if (a >= size()) {
        throw std::out_of_range("Indice fuera de rango");
    }

    if (b >= size()) {
        throw std::out_of_range("Indice fuera de rango");
    }

    if (std::find(adjacency[a].begin(), adjacency[a].end(), b) != adjacency[a].end()) {
            throw std::runtime_error("Nodes already connected");
        }
#endif

    adjacency[a].push_back(b);
    adjacency[b].push_back(a);
}

std::vector<std::size_t> Graph::descendingByDegree() const {
    std::vector<std::size_t> vertex_order(size());

    auto comp = [this](std::size_t i, std::size_t j) {
        return this->degree(i) > this->degree(j);
    };

    std::sort(vertex_order.begin(), vertex_order.end(), comp);

    return vertex_order;
}

Graph::~Graph() { }