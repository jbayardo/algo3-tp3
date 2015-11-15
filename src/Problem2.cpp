#include <stack>
#include <iostream>
#include <list>
#include "Problem.h"
#include "Statistics.h"

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

    for (std::size_t i = 0; i < graph.size(); ++i) {
        std::list<std::size_t> replacement;

        if (colors.get(i).size() <= 2) {
            replacement = colors.get(i);
            output.add(i, replacement);
        } else {
            if (current.isset(i)) {
                replacement.push_back(current.get(i));
                output.add(i, replacement);
            } else {
                replacement = colors.get(i);
                output.add(i, replacement);
            }
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
    // TODO: si descomentas lo de abajo, borra estas 2 lineas.
    return current;
/*    if (current.complete()) {
        return current;
    } else {
        // Chequear si es 2 list coloring
        if (is2ListColoring(graph, colors, current)) {
            return 2ListColoring(graph, transform(graph, colors, current));
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
    }*/
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