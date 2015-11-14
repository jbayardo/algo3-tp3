#ifndef ALGO3_TP3_COLORSTORAGE_H
#define ALGO3_TP3_COLORSTORAGE_H

#include <vector>
#include <list>
#include <algorithm>
#include <map>

typedef std::vector<std::list<std::size_t>> ColorLists;


class ColorStorage {
public:
    ColorStorage() : colors(0) { };
    ColorStorage(std::size_t vertices) : colors(vertices), _total_number(0) { };

    /**
     * TODO: Si le ponemos el const a iColors, podemos hacer que Problem2::transform sea mucho más rápido.
     */
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

    ColorLists sortByFrequency() const {
        std::map<std::size_t, std::size_t> frequencies;
        ColorLists colors_by_frequency(colors);

        for (auto& l: colors_by_frequency) {
            for (auto& c: l) {
                if (frequencies.find(c) == frequencies.end()) {
                    frequencies[c] = 1;
                }
                else {
                    frequencies[c] += 1;
                }
            }
        }

        for (auto& l: colors_by_frequency) {
            l.sort( [&frequencies] (std::size_t i, std::size_t j) {
                        return frequencies[i] > frequencies[j];
                    }
                );
        }

        return colors_by_frequency;
    }


private:
    ColorLists colors;
    std::size_t _total_number;
};

#endif //ALGO3_TP3_COLORSTORAGE_H
