#include <algorithm>
#include "Graph.h"

Graph::Graph() : adjacency(0) { }

Graph::Graph(std::size_t vertices) : adjacency(vertices) { }

std::size_t inline Graph::size() const {
    return adjacency.size();
}

std::size_t inline Graph::degree(std::size_t a) const {
    return adjacency[a].size();
}

void Graph::connect(std::size_t a, std::size_t b) {
#ifdef DEBUG
    if (std::find(adjacency[a].begin(), adjacency[a].end(), b) != adjacency[a].end()) {
            throw std::runtime_error("Nodes already connected");
        }
#endif

    adjacency[a].push_back(b);
    adjacency[b].push_back(a);
}

const std::list<std::size_t> inline &Graph::neighbors(std::size_t a) const {
    return adjacency[a];
}