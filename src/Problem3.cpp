#include "Problem.h"

Coloring greedy_order(std::vector<std::size_t> vertex_order,
                      const Graph& graph,
                      const ColorStorage& colors) {
    auto coloring = Coloring(graph);

    for (auto& v: vertex_order) {
        auto choice = colors.get(v).front();
        auto conflicts = coloring.conflicts(choice);

        for (auto& c: colors.get(v)) {
            auto current_conflicts = coloring.conflicts(c);

            if (current_conflicts < conflicts) {
                choice = c;
                conflicts = current_conflicts;

                if (current_conflicts == 0) {
                    break;
                }
            }
        }
        coloring.set(v, choice);
    }
#ifdef DEBUG
    if (!coloring.complete()) {
        throw std::runtime_error("La heuristica golosa devolvió un coloreo incompleto");
    }
#endif

    return coloring;
}


Coloring Problem::solve3() const {
    auto vertex_order = graph.descendingByDegree();
    auto result = greedy_order(vertex_order, graph, colors);
    if (!result.complete()) {
        vertex_order = colors.ascendingByColor();
        result = greedy_order(vertex_order, graph, colors);
    }

    return result;
}