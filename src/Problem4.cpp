#include <queue>
#include "Problem.h"
#include "ConflictColoring.h"
#include "Statistics.h"

/**
 * @param input coloreo de entrada
 * @return mejor coloreo vecino
 */
ConflictColoring neighbour(ConflictColoring original, const ColorStorage &colors) {
    Timer timer("Local Search Neighbourhood 1 Timer");
    // Calculamos la cantidad de vecinos que vamos a mirar
    std::size_t size = std::min(original.size(), 5UL);

    // Obtenemos las colisiones, y creamos un heap para facilitar el algoritmo
    const std::vector<std::size_t> &conflicts = original.perVertexConflicts();
    std::priority_queue<std::pair<std::size_t, std::size_t>, std::vector<std::pair<std::size_t, std::size_t> >, std::greater<std::pair<std::size_t, std::size_t> > > queue;

    // Obtenemos los size nodos con mayor cantidad de conflictos
    for (std::size_t n = 0; n < size; ++n) {
        queue.push(std::make_pair(conflicts[n], n));
    }

    for (std::size_t n = size; n < conflicts.size(); ++n) {
        std::pair<std::size_t, std::size_t> current = queue.top();

        if (current.first < conflicts[n]) {
            queue.pop();
            queue.push(std::make_pair(conflicts[n], n));
        }
    }

    // Obtengo el mejor vecino
    ConflictColoring best(original);

    for (std::size_t n = 0; n < size; ++n) {
        std::size_t vertex = queue.top().second;
        queue.pop();

        // Probamos con todos los colores
        for (auto &color : colors.get(vertex)) {
            if (color != original.get(vertex)) {
                ConflictColoring next(original);

                next.setu(vertex, color);

                if (next.conflicts() < best.conflicts()) {
                    best = next;
                }
            }
        }
    }

    return best;
}

Coloring Problem::solve4() const {
    Timer timer("Exercise 4 Timer");
    ConflictColoring current = solve3();

    while (1) {
        ConflictColoring next = neighbour(current, colors);

        if (next.conflicts() >= current.conflicts()) {
            return current;
        } else {
            current = next;
        }
    }
}

/**
 * @param input coloreo de entrada
 * @return mejor coloreo vecino
 */
ConflictColoring neighbour2(ConflictColoring current, const Graph &graph, const ColorStorage &colors) {
    Timer timer("Local Search Neighbourhood 2 Timer");
    std::size_t best = 0;
    double ratio = 0.0;

    // Obtenemos el nodo a modificar
    for (std::size_t i = 0; i < graph.size(); ++i) {
        double r = ((double)current.conflicts(i)) / ((double)graph.degree(i));

        if (r > ratio) {
            ratio = r;
            best = i;
        }
    }

    std::size_t initial = current.get(best);
    std::size_t conflicts = current.conflicts(best);

    for (auto &color : colors.get(best)) {
        if (color != initial) {
            std::size_t previous = current.get(best);
            current.setu(best, color);

            if (current.conflicts(best) < conflicts) {
                conflicts = current.conflicts(best);
            } else {
                current.setu(best, previous);
            }
        }
    }

    return current;
}

Coloring Problem::solve5() const {
    Timer timer("Exercise 5 Timer");
    ConflictColoring current(solve3());

    while (1) {
        ConflictColoring next = neighbour2(current, graph, colors);

        if (next.conflicts() >= current.conflicts()) {
            return current;
        } else {
            current = next;
        }
    }
}