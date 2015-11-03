#ifndef ALGO3_TP3_GRAPH_H
#define ALGO3_TP3_GRAPH_H

#include <vector>
#include <list>

class Graph {
public:
    Graph();
    Graph(std::size_t vertices);
    std::size_t inline size() const;
    std::size_t inline degree(std::size_t a) const;
    void connect(std::size_t a, std::size_t b);
    const std::list<std::size_t> inline &neighbors(std::size_t a) const;
private:
    std::vector<std::list<std::size_t>> adjacency;
};

#endif //ALGO3_TP3_GRAPH_H
