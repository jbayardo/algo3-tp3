#ifndef ALGO3_TP3_GRAPH_H
#define ALGO3_TP3_GRAPH_H

#include <stdexcept>
#include <vector>
#include <algorithm>
#include <list>

class Graph {
public:
    Graph() : adjacency(0) { }

    /*! Constructor
     *
     * @param vertices cantidad de vertices en el grafo
     * @complexity O(n)
     */
    Graph(std::size_t vertices) :
        adjacency(vertices) { }

    /*! Constructor por copia
     *
     * @param g objeto a copiar
     * @complexity O(n + m)
     */
    Graph(const Graph &g) :
        adjacency(g.adjacency) { }

    /*! Constructor por movimiento
     *
     * @param g objeto a mover
     * O(1)
     */
    Graph(Graph &&g) :
        adjacency(std::move(g.adjacency)) { }

    /*! Operador de asignación
     *
     * @return referencia a la clase actual
     * @complexity O(n)
     */
    Graph &operator=(const Graph &r) {
        if (this != &r) {
            adjacency = r.adjacency;
        }

        return *this;
    }

    void inline connect(std::size_t a, std::size_t b) {
#ifdef DEBUG
        if (a >= size() || b >= size()) {
            throw std::out_of_range("Indice fuera de rango");
        }

        if (std::find(adjacency[a].begin(), adjacency[a].end(), b) != adjacency[a].end()) {
            throw std::runtime_error("Nodes already connected");
        }
#endif

        adjacency[a].push_back(b);
        adjacency[b].push_back(a);
    }

    const std::list<std::size_t> inline &neighbours(std::size_t a) const {
#ifdef DEBUG
        if (a >= size()) {
            throw std::out_of_range("Indice fuera de rango");
        }
#endif

        return adjacency[a];
    }

    std::size_t inline size() const {
        return adjacency.size();
    }

    std::size_t inline degree(std::size_t a) const {
#ifdef DEBUG
        if (a >= size()) {
            throw std::out_of_range("Indice fuera de rango");
        }
#endif

        return adjacency[a].size();
    }

    std::vector<std::size_t> descendingByDegree() const {
        std::vector<std::size_t> vertex_order;

        for (std::size_t i = 0; i < size(); i++) {
            vertex_order.push_back(i);
        }

        auto comp = [this](std::size_t i, std::size_t j) {
            return this->degree(i) >= this->degree(j);
        };

        std::stable_sort(vertex_order.begin(), vertex_order.end(), comp);

        return vertex_order;
    }

    virtual ~Graph() { }
private:
    std::vector<std::list<std::size_t>> adjacency;
};

#endif //ALGO3_TP3_GRAPH_H
