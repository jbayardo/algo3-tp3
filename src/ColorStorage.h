#ifndef ALGO3_TP3_COLORSTORAGE_H
#define ALGO3_TP3_COLORSTORAGE_H

#include <vector>
#include <list>
#include <algorithm>

class ColorStorage {
public:
    ColorStorage() : colors(0) { };
    ColorStorage(std::size_t vertices) : colors(vertices), totalNumber(0) { };

    void add(std::size_t vertex, std::list<std::size_t> &iColors) {
#ifdef DEBUG
        if (std::find(colors[vertex].begin(), colors[vertex].end(), colors) != colors[vertex].end()) {
        	throw std::runtime_error("Color already added for vertex");
        	return;
        }
#endif
        colors[vertex].splice(colors[vertex].begin(), iColors); //Agrego colores nuevos al inicio
        totalNumber += iColors.size();
    }                                                           //No hay orden

    const std::list<std::size_t> inline &get(std::size_t vertex) const {
        return colors[vertex];
    }
    int totalNumber() const {
    	return totalNumber;
    }

    std::size_t inline size() const {
        return colors.size();
    }

    std::vector<std::size_t> ascendingByColor() {
        std::vector<std::size_t> vertex_order(colors.size());

        auto comp = [this](std::size_t i, std::size_t j) {
            return this->colors[i].size() < this->colors[j].size();
        };

        std::sort(vertex_order.begin(), vertex_order.end(), comp);

        return vertex_order;
    }
private:
    std::vector<std::list<std::size_t>> colors;
    int totalNumber;
};

#endif //ALGO3_TP3_COLORSTORAGE_H
