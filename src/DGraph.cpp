#include "DGraph.h"
#include <algorithm>
#include <queue>

DGraph::DGraph() : adjacency(0) { }

DGraph::DGraph(std::size_t vertices) : adjacency(vertices) { }

std::size_t inline DGraph::size() const {
    return adjacency.size();
}

std::size_t inline DGraph::inDegree(std::size_t a) const {
    return parents[a].size();
}
std::size_t inline DGraph::outDegree(std::size_t a) const {
    return adjacency[a].size();
}

void DGraph::connect(std::size_t a, std::size_t b) {
#ifdef DEBUG
    if (std::find(adjacency[a].begin(), adjacency[a].end(), b) != adjacency[a].end()) {
        throw std::runtime_error("Nodes already connected");
    }
#endif
    adjacency[a].push_back(b);
    parents[b].push_back(a);
}

const std::list<std::size_t> inline &DGraph::neighbors(std::size_t a) const {
    return adjacency[a];
}

const std::list<std::size_t> inline &DGraph::parents(std::size_t a) const {
    return parents[a];
}

void DGraph::transpose() {
	for (int x = 0; x < adjacency.size(); ++x) {
		adjacency[x].swap(parents[x]);
	}
}