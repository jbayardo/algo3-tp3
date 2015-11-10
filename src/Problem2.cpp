#include <stack>
#include "Problem.h"
#include "Statistics.h"

Coloring Problem::solve2() const {
    Timer timer("Exercise 2 Timer");
    std::stack<Coloring> pending;
    // Generamos el coloreo vacio
    pending.push(Coloring(graph));

    while (!pending.empty()) {
        Coloring current = pending.top();
        pending.pop();
    }
    Coloring c(graph);
    return c;
}