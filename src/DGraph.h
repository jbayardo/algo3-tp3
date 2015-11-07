#ifndef ALGO3_TP3_DGRAPH_H
#define ALGO3_TP3_DGRAPH_H

#include <vector>
#include <list>

class DGraph {
public:
    DGraph();
    DGraph(std::size_t vertices);
    void connect(std::size_t a, std::size_t b);

    inline std::size_t size() const {
        return _adjacency.size();
    }

    inline std::size_t inDegree(std::size_t a) const {
        return _parents[a].size();
    }

    inline std::size_t outDegree(std::size_t a) const {
        return _adjacency[a].size();
    }

    inline const std::list<std::size_t> &neighbours(std::size_t a) const {
        return _adjacency[a];
    }

    inline const std::list<std::size_t> &parents(std::size_t a) const {
        return _parents[a];
    }

    void transpose();
private:
    std::vector<std::list<std::size_t>> _adjacency;
    std::vector<std::list<std::size_t>> _parents;
};

#endif //ALGO3_TP3_DGRAPH_H
