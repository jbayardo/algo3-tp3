#include "Problem.h"
#include "ConflictColoring.h"
#include "Statistics.h"

ConflictColoring greedy_order(std::vector<std::size_t> &vertex_order,
                      const Graph &graph,
                      const ColorLists &colors) {
    auto coloring = ConflictColoring(graph);

    for (auto &v: vertex_order) {
        auto choice = 0;
        auto conflicts = std::numeric_limits<std::size_t>::max();

        for (auto &c: colors[v]) {
            coloring.setu(v, c);
            auto current_conflicts = coloring.conflicts(v);

            if (current_conflicts < conflicts) {
                choice = c;
                conflicts = current_conflicts;

                if (current_conflicts == 0) {
                    break;
                }
            }
        }

        coloring.setu(v, choice);
    }
#ifdef DEBUG
    if (!coloring.complete()) {
        throw std::runtime_error("La heuristica golosa devolvió un coloreo incompleto");
    }
#endif

    return coloring;
}


Coloring Problem::solve3() const {
    Timer timer("Exercise 3 Timer");
    auto colors_by_frequency = colors.sortByFrequency();
    auto vertex_order = graph.descendingByDegree();
    auto result = greedy_order(vertex_order, graph, colors_by_frequency);

    return result;
}