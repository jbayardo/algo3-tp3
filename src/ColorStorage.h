#ifndef ALGO3_TP3_COLORSTORAGE_H
#define ALGO3_TP3_COLORSTORAGE_H

#include <vector>
#include <list>
#include <algorithm>

class ColorStorage {
public:
    ColorStorage() : colors(0) { };
    ColorStorage(std::size_t vertices) : colors(vertices), _total_number(0) { };

    void add(std::size_t vertex, std::list<std::size_t> &iColors) {
#ifdef DEBUG
        if (std::find(colors[vertex].begin(), colors[vertex].end(), colors) != colors[vertex].end()) {
        	throw std::runtime_error("Color already added for vertex");
        	return;
        }
#endif
        colors[vertex].splice(colors[vertex].begin(), iColors); //Agrego colores nuevos al inicio
        _total_number += iColors.size();
    }                                                           //No hay orden

    const std::list<std::size_t> inline &get(std::size_t vertex) const {
        return colors[vertex];
    }
    std::size_t total_number() const {
    	return _total_number;
    }

    std::size_t inline size() const {
        return colors.size();
    }

    std::vector<std::size_t> ascendingByColor() const{
        std::vector<std::size_t> vertex_order;

        for (std::size_t i = 0; i < colors.size(); i++) {
            vertex_order.push_back(i);
        }

        auto comp = [this](std::size_t i, std::size_t j) {
            return this->colors[i].size() < this->colors[j].size();
        };

        std::sort(vertex_order.begin(), vertex_order.end(), comp);

        return vertex_order;
    }
private:
    std::vector<std::list<std::size_t>> colors;
    std::size_t _total_number;
};

#endif //ALGO3_TP3_COLORSTORAGE_H
