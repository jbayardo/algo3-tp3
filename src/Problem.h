#ifndef ALGO3_TP3_PROBLEM_H
#define ALGO3_TP3_PROBLEM_H

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


#endif //ALGO3_TP3_PROBLEM_H
