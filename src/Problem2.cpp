#include <set>
#include "Problem.h"
#include "Problem1.h"
#include "Statistics.h"

#include <iostream>

bool is2ListColoring (const Graph &graph, const ColorStorage &colors, const Coloring &current) {
    for (std::size_t i = 0; i < graph.size(); ++i) {
        if (!current.isset(i) && colors.get(i).size() > 2) {
            return false;
        }
    }

    return true;
}

ColorStorage transform(const Graph &graph, const ColorStorage &colors, const Coloring &current) {
    ColorStorage output(graph.size());

    for (std::size_t vertex = 0; vertex < graph.size(); ++vertex) {
        if (colors.get(vertex).size() <= 2) {
            output.add(vertex, colors.get(vertex));
        } else {
            output.add(vertex, current.get(vertex));
        }
    }

    return output;
}

bool isAdmissible(const Graph &graph, const Coloring &current, std::size_t node, std::size_t colour) {
    for (auto &neighbour : graph.neighbours(node)) {
        if (current.isset(neighbour) && current.get(neighbour) == colour) {
            return false;
        }
    }

    return true;
}

Coloring coloringExists(const Graph &graph, const ColorStorage &colors, Coloring current, std::size_t node) {
    if (current.complete()) {
        return current;
    } else {
        // Chequear si es 2 list coloring
        #ifdef PODAS
        if (is2ListColoring(graph, colors, current)) {
            ColorStorage storage = transform(graph, colors, current);
            Problem1 instance(graph, storage);
            return instance.solve();
        }

        // Probamos con todos los colores
        for (auto &colour : colors.get(node)) {
            if (isAdmissible(graph, current, node, colour)) {
                current.set(node, colour);

                try {
                    return coloringExists(graph, colors, current, node + 1);
                } catch (...) {
                    continue;
                }
            }
        }

        throw std::runtime_error("Se fue todo a la chota");
        #else
        for (auto &colour : colors.get(node)) {
            try {
                return coloringExists(graph, colors, current, node + 1);
            } catch (...) {
                    continue;
            }
        }
        #endif

    }
}

Coloring Problem::solve2() const {
    Timer timer("Exercise 2 Timer");
    Coloring current(graph);

    try {
        return coloringExists(graph, colors, current, 0);
    } catch (...) {
        return current;
    }
}