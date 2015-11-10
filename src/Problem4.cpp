#include "Problem.h"
#include "Statistics.h"

/**
 * @param input coloreo de entrada
 * @return mejor coloreo vecino
 */
Coloring neighbour(Coloring next, const ColorStorage &colors) {
    // Calculamos la cantidad de vecinos que vamos a mirar
    std::size_t size = 5;

    if (next.size() < size) {
        size = next.size();
    }

    // Obtenemos las colisiones
    const std::vector<std::size_t> &conflicts = next.perVertexConflicts();
    std::vector<std::size_t> vertices(size, std::numeric_limits<std::size_t>::max());

    // Obtenemos el mejor vecino
    for (std::size_t n = 0; n < size; ++n) {
        // Tomamos el n-esimo vertice con más colisiones
        vertices[n] = n;

        for (std::size_t i = 0; i < conflicts.size(); ++i) {
            // Si el elemento actual tiene mas colisiones que el que habiamos seleccionado
            if (conflicts[i] > conflicts[vertices[n]]) {
                // Si el elemento actual no habia sido seleccionado previamente, lo seteamos
                bool skip = false;

                for (std::size_t j = 0; j < n; ++j) {
                    if (vertices[j] == i) {
                        skip = true;
                    }
                }

                if (!skip) {
                    vertices[n] = i;
                }
            }
        }

        // Obtengo el mejor color para el vertice que no sea el actual
        Coloring current(next);

        for (auto &color : colors.get(vertices[n])) {
            Coloring temporal(next);

            if (color != temporal.get(vertices[n])) {
                temporal.set(vertices[n], color);

                if (temporal.conflicts(vertices[n]) < current.conflicts(vertices[n])) {
                    current = temporal;
                }
            }
        }

        // Si mejora el coloreo actual, lo reemplazo!
        if (current.conflicts() < next.conflicts()) {
            next = current;
        }
    }

    return next;
}

Coloring Problem::solve4() const {
    Timer timer("Exercise 4 Timer");
    Coloring current = solve3();

    for (std::size_t iterations = 0; iterations < 1000; ++iterations) {
        Coloring next = neighbour(current, colors);

        if (next.conflicts() >= current.conflicts()) {
            return current;
        } else {
            current = next;
        }
    }

    return current;
}

/**
 * @param input coloreo de entrada
 * @return mejor coloreo vecino
 */
Coloring neighbour2(Coloring next, const Graph &graph, const ColorStorage &colors) {
    std::size_t best = 0;
    double current = 0.0;

    // Obtenemos el nodo a modificar
    for (std::size_t i = 0; i < graph.size(); ++i) {
        double ratio = ((double)next.conflicts(i))/((double)graph.degree(i));

        if (ratio > current) {
            current = ratio;
            best = i;
        }
    }

    std::size_t initial = next.get(best);
    std::size_t conflicts = next.conflicts(best);

    for (auto &color : colors.get(best)) {
        if (color != initial) {
            std::size_t previous = next.get(best);
            next.set(best, color);

            if (next.conflicts(best) < conflicts) {
                conflicts = next.conflicts(best);
            } else {
                next.set(best, previous);
            }
        }
    }

    return next;
}

Coloring Problem::solve5() const {
    Timer timer("Exercise 5 Timer");
    Coloring current = solve3();

    for (std::size_t iterations = 0; iterations < 1000; ++iterations) {
        Coloring next = neighbour2(current, graph, colors);

        if (next.conflicts() >= current.conflicts()) {
            return current;
        } else {
            current = next;
        }
    }

    return current;
}