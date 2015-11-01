#ifndef ALGO3_TP3_COLORING_H
#define ALGO3_TP3_COLORING_H

#include <vector>
#include <ostream>

class Coloring {
    friend std::ostream &operator<<(std::ostream &stream, const Coloring &bracelet);
public:
    Coloring(std::size_t vertices);
    Coloring(const Coloring &c);
    Coloring & operator=(const Coloring &r);
    std::size_t inline size() const;
    bool inline complete() const;
    bool inline isset(std::size_t index) const;
    std::size_t inline get(std::size_t index) const;
    std::size_t inline set(std::size_t index, std::size_t color);
    std::size_t inline unset(std::size_t index);
    virtual ~Coloring();
private:
    std::size_t static inline uncolored() {
        return std::numeric_limits<std::size_t>::max();
    }

    std::vector<std::size_t> colors;
    std::size_t left;
};

#endif //ALGO3_TP3_COLORING_H
