#ifndef ALGO3_TP3_GRAPH_H
#define ALGO3_TP3_GRAPH_H

#include <vector>
#include <list>

class Graph {
public:
    Graph();
    Graph(std::size_t vertices);
    void connect(std::size_t a, std::size_t b);
    std::vector<std::size_t> descendingByDegree() const;

    const std::list<std::size_t> inline &neighbours(std::size_t a) const {
#ifdef DEBUG
        if (a >= size()) {
            throw std::out_of_range("Indice fuera de rango");
        }
#endif

        return adjacency[a];
    }

    std::size_t inline size() const {
        return adjacency.size();
    }

    std::size_t inline degree(std::size_t a) const {
#ifdef DEBUG
        if (a >= size()) {
            throw std::out_of_range("Indice fuera de rango");
        }
#endif
        return adjacency[a].size();
    }
    virtual ~Graph();
private:
    std::vector<std::list<std::size_t>> adjacency;
};

#endif //ALGO3_TP3_GRAPH_H
