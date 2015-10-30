#ifndef ALGO3_TP3_COLORSTORAGE_H
#define ALGO3_TP3_COLORSTORAGE_H

#include <vector>
#include <list>
#include <algorithm>

class ColorStorage {
public:
    ColorStorage(std::size_t vertices) : colors(vertices), totalNumber(0) { };

    void add(std::size_t vertex, std::list<std::size_t> &colors) {
#ifdef DEBUG
        if (std::find(colors[vertex].begin(), colors[vertex].end(), colors) != colors[vertex].end()) {
        	throw std::runtime_error("Color already added for vertex");
        	return;
        }
#endif
        colors[vertex] += colors;
        ++totalNumber;
    }

    std::list<std::size_t> get(std::size_t vertex) const {
        return colors[vertex];
    }

    int totalNumber() const {
    	return totalNumber;
    }
private:
    std::vector<std::list<std::size_t>> colors;
    int totalNumber;
};

#endif //ALGO3_TP3_COLORSTORAGE_H
