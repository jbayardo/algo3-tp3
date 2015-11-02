#include <fstream>
#include <stdexcept>
#include "Problem.h"
#include "Statistics.h"

Problem::Problem(std::string input) {
    std::ifstream handle;
    handle.open(input, std::ifstream::in);

    if (!handle.is_open()) {
        throw std::runtime_error("Fallo al abrir el archivo de tests");
    }

    handle >> vertices >> edges >> nColors;

    if (nColors <= 0) {
        throw std::runtime_error("Error reading file: number of colors must be higher than 0");
    }

    colors = ColorStorage(vertices);

    for (std::size_t vertex = 0; vertex < vertices; ++vertex) {
        std::size_t readColors;
        handle >> readColors;

        if (readColors <= 0) {
            throw std::runtime_error("Error reading file: number of current colors must be higher than 0");
        }

        std::list<std::size_t> current;

        for (std::size_t c = 0; c < readColors; ++c) {
            std::size_t color;
            handle >> color;

            if (color >= nColors) {
                throw std::runtime_error("Invalid color number");
            }

            current.push_back(color);
        }

        colors.add(vertex, current);
    }

    graph = Graph(vertices);

    for (std::size_t edge = 0; edge < edges; ++edge) {
        std::size_t from, to;
        handle >> from >> to;

        if (from >= vertices || to >= vertices) {
            throw std::runtime_error("Invalid edge");
        }

        graph.connect(from, to);
    }

    handle.close();
}

Coloring Problem::solve(int exercise, int runs) const {
    if (runs < 1) {
        throw std::out_of_range("La cantidad de corridas debe ser mayor a 0");
    }

    switch (exercise) {
        case 1:
            for (auto i = 0; i < runs - 1; ++i) {
                solve1();
            }

            return solve1();
        case 2:
            for (auto i = 0; i < runs - 1; ++i) {
                solve2();
            }

            return solve2();
        case 3:
            for (auto i = 0; i < runs - 1; ++i) {
                solve3();
            }

            return solve3();
        case 4:
            for (auto i = 0; i < runs - 1; ++i) {
                solve4();
            }

            return solve4();
        default:
            throw std::out_of_range("Los ejercicios estan numerados del 1 al 4");
    }
}

Coloring Problem::solve1() const {
}

#include <stack>

Coloring Problem::solve2() const {
    Timer timer("Backtracking Timer");
    std::stack<Coloring> pending;

    // Generamos el coloreo vacio
    pending.push(Coloring(graph));

    while (!pending.empty()) {
        Coloring current = pending.top();
        pending.pop();

        // Chequeo si redujimos a 2 list coloring
        if (2 list coloring) {
            return ...;
        } else {
            // Genero todas las alternativas
            for () {
                Coloring generated(current);

                if (generated.admissible(colors)) {
                    pending.push(generated);
                }
            }
        }
    }
}

Coloring Problem::solve3() const {
}

Coloring Problem::solve4() const {
}

