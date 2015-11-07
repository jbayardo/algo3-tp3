#ifndef ALGO3_TP3_PROBLEM_H
#define ALGO3_TP3_PROBLEM_H


#include <vector>
#include <list>
#include <stack>
#include <stdexcept>
#include <fstream>
#include "DGraph.h"
#include "Statistics.h"
#include "Graph.h"
#include "ColorStorage.h"
#include "Coloring.h"

class Problem {
public:
    Problem(std::string input);
    Coloring solve(int exercise, int runs) const;
private:
    Coloring solve1() const;
    Coloring solve2() const;
    Coloring solve3() const;
    Coloring solve4() const;

    std::size_t vertices;
    std::size_t edges;
    std::size_t nColors;

    Graph graph;
    ColorStorage colors;
};

std::list<std::list<std::size_t>> korasaju(DGraph& i_g, std::vector<std::size_t>& node_scc);

#endif //ALGO3_TP3_PROBLEM_H
