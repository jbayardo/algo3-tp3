#include <algorithm>
#include "DGraph.h"

DGraph::DGraph() : _adjacency(0) { }

DGraph::DGraph(std::size_t vertices) : _adjacency(vertices), _parents(vertices) { }

void DGraph::connect(std::size_t a, std::size_t b) {
#ifdef DEBUG
    if (std::find(_adjacency[a].begin(), _adjacency[a].end(), b) != _adjacency[a].end()) {
        // throw std::runtime_error("Nodes already connected");
        return;
    }
#endif

    _adjacency[a].push_back(b);
    _parents[b].push_back(a);
}

void DGraph::transpose() {
	for (std::size_t i = 0; i < _adjacency.size(); ++i) {
		_adjacency[i].swap(_parents[i]);
	}
}