#ifndef ALGO3_TP3_PROBLEM1_H
#define ALGO3_TP3_PROBLEM1_H

#include "Graph.h"
#include "DGraph.h"
#include "Coloring.h"
#include "ColorStorage.h"

#define TO_IMPLICATION_INDEX(vertex, color, neg) (4*vertex + 2*color + ((neg == true)? 0:1))
#define GET_VERTEX(vertex) (vertex/4)
#define GET_COLOR(vertex) ((vertex % 4)/2)
#define GET_NEG(vertex) (((vertex % 4) % 2) == 0)

class Problem1 {
    enum TruthValue {
        False,
        True,
        Unset
    };
public:
    Problem1(const Graph &graph_, const ColorStorage &colors_);
    Coloring solve() const;
    virtual ~Problem1();
private:
    DGraph buildImplicationGraph() const;
    std::size_t getColorIndex(std::size_t vertex, std::size_t colour) const;
    std::size_t getColorFromIndex(std::size_t vertex, std::size_t index) const;

    const Graph &graph;
    const ColorStorage &colors;
};

#endif //ALGO3_TP3_PROBLEM1_H
