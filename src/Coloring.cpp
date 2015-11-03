#include <sstream>
#include <limits>
#include <stdexcept>
#include "Coloring.h"

Coloring::Coloring(const Graph &g) :
        graph(g),
        colors(g.size(), uncolored()),
        left(g.size()) { }

Coloring::Coloring(const Coloring &c) :
        graph(c.graph),
        colors(c.colors),
        left(c.left) { }

Coloring &Coloring::operator=(const Coloring &r) {
    if (this != &r) {
        if (&graph != &r.graph) {
            throw std::runtime_error("Los coloreos deben pertenecer a un mismo grafo para ser asignados");
        }

        this->colors = r.colors;
        this->left = r.left;
    }

    return *this;
}

bool inline Coloring::complete() const {
    return (left == 0);
}

bool inline Coloring::isset(std::size_t index) const {
    return (colors[index] != uncolored());
}

std::size_t inline Coloring::get(std::size_t index) const {
    return colors[index];
}

std::size_t inline Coloring::set(std::size_t index, std::size_t color) {
    if (colors[index] == uncolored()) {
        --left;
    }

    return (colors[index] = color);
}

std::size_t inline Coloring::unset(std::size_t index) {
    if (colors[index] != uncolored()) {
        ++left;
    }

    return (colors[index] = uncolored());
}

Coloring::~Coloring() { }

std::ostream & operator<<(std::ostream &stream, const Coloring &coloring) {
    std::stringstream output;

    if (coloring.complete()) {
        for (std::size_t i = 0; i < coloring.graph.size() - 1; ++i) {
            output << coloring.get(i) << ' ';
        }

        output << coloring.get(coloring.graph.size() - 1) << std::endl;
    } else {
        output << "X" << std::endl;
    }

    stream << output;
    return stream;
}