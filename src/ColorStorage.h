#ifndef ALGO3_TP3_COLORSTORAGE_H
#define ALGO3_TP3_COLORSTORAGE_H

#include <vector>
#include <set>
#include <algorithm>
#include <map>

typedef std::vector<std::set<std::size_t>> ColorSets;
typedef std::vector<std::list<std::size_t>> ColorLists;


class ColorStorage {
public:
    ColorStorage() : colors(0) { };
    ColorStorage(std::size_t vertices) : colors(vertices), _total_number(0) { };

    void add(std::size_t index, std::size_t color) {
#ifdef DEBUG
        if (index >= size()) {
            throw std::out_of_range("Indice fuera de rango");
        }

        if (std::find(colors[index].begin(), colors[index].end(), color) != colors[index].end()) {
            throw std::runtime_error("El color ya está en el vértice");
        }
#endif
        _total_number += 1;
        colors[index].insert(color);
    }

    void add(std::size_t index, const std::set<std::size_t> &iColors) {
#ifdef DEBUG
        if (index >= size()) {
            throw std::out_of_range("Indice fuera de rango");
        }

        for (auto &color : iColors) {
            if (std::find(colors[index].begin(), colors[index].end(), color) != colors[index].end()) {
                throw std::runtime_error("Algún color ya está en el vértice");
            }
        }
#endif
        _total_number += iColors.size();
        colors[index].insert(iColors.begin(), iColors.end());
    }

    const std::set<std::size_t> inline &get(std::size_t index) const {
#ifdef DEBUG
        if (index >= size()) {
            throw std::out_of_range("Indice fuera de rango");
        }
#endif

        return colors[index];
    }
    std::size_t total_number() const {
    	return _total_number;
    }

    std::size_t inline size() const {
        return colors.size();
    }

    ColorLists sortByFrequency() const {
        std::map<std::size_t, std::size_t> frequencies;
        ColorLists colors_by_frequency(colors.size());

        for(std::size_t i = 0; i < colors.size(); i++) {
            colors_by_frequency[i] = std::list<std::size_t>(colors[i].begin(),
                                                            colors[i].end());
            auto& l = colors_by_frequency[i];
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
                        return frequencies[i] >= frequencies[j];
                    }
                );
        }

        return colors_by_frequency;
    }


private:
    ColorSets colors;
    std::size_t _total_number;
};

#endif //ALGO3_TP3_COLORSTORAGE_H
