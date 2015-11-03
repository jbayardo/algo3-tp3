#ifndef ALGO3_TP3_DGRAPH_H
#define ALGO3_TP3_DGRAPH_H

#include <vector>
#include <list>

class DGraph {
public:
    DGraph();
    DGraph(std::size_t vertices);
    std::size_t size() const;
    std::size_t outDegree(std::size_t a) const;
    std::size_t inDegree(std::size_t a) const;
    void connect(std::size_t a, std::size_t b);
    const std::list<std::size_t> inline &neighbors(std::size_t a) const;
    void transpose();
private:
    std::vector<std::list<std::size_t>> adjacency;
    std::vector<std::list<std::size_t>> parents;
};

#endif //ALGO3_TP3_DGRAPH_H
