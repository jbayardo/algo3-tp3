#include <sstream>
#include <limits>
#include "Coloring.h"

Coloring::Coloring(std::size_t vertices) : colors(vertices, uncolored()), left(vertices) { }

Coloring::Coloring(const Coloring &c) : colors(c.colors), left(c.left) { }

Coloring &Coloring::operator=(const Coloring &r) {
    if (this != &r) {
        this->colors = r.colors;
        this->left = r.left;
    }

    return *this;
}

std::size_t inline Coloring::size() const {
    return colors.size();
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
        for (std::size_t i = 0; i < coloring.size() - 1; ++i) {
            output << coloring.get(i) << ' ';
        }

        output << coloring.get(coloring.size() - 1) << std::endl;
    } else {
        output << "X" << std::endl;
    }

    stream << output;
    return stream;
}