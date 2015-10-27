#ifndef ALGO3_TP3_COLORSTORAGE_H
#define ALGO3_TP3_COLORSTORAGE_H

class ColorStorage {
public:
    ColorStorage(std::size_t vertices) : colors(vertices) { };

    void add(std::size_t vertex, std::list<std::size_t> &colors) {
        colors[vertex] += colors;
    }

    std::list<std::size_t> get(std::size_t vertex) const {
        return colors[vertex];
    }
private:
    std::vector<std::list<std::size_t>> colors;
};

#endif //ALGO3_TP3_COLORSTORAGE_H
