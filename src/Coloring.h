#ifndef ALGO3_TP3_COLORING_H
#define ALGO3_TP3_COLORING_H

#include <vector>
#include <ostream>
#include <stdexcept>
#include <sstream>
#include <limits>
#include "Graph.h"
#include "ColorStorage.h"

/*! Guarda un coloreo parcial o total para un grafo.
 */
class Coloring {
    friend std::ostream &operator<<(std::ostream &, const Coloring &);
public:
    /*! Constructor
     *
     * @param g grafo de referencia
     */
    Coloring(const Graph &g) :
            graph(g),
            colors(g.size(), uncolored()),
            collisions(g.size(), 0),
            left(g.size()),
            total_collisions(0),
            updated(true) { }

    /*! Constructor por copia
     *
     * @param c coloreo a copiar
     */
    Coloring(const Coloring &c) :
            graph(c.graph),
            colors(c.colors),
            collisions(c.colors),
            left(c.left),
            total_collisions(c.total_collisions),
            updated(c.updated) { }

    /*! Operador de asignación
     *
     * @return referencia a la clase actual
     */
    Coloring &operator=(const Coloring &r) {
        if (this != &r) {
            if (&graph != &r.graph) {
                throw std::runtime_error("Los coloreos deben pertenecer a un mismo grafo para ser asignados");
            }

            this->colors = r.colors;
            this->collisions = r.collisions;
            this->left = r.left;
            this->total_collisions = r.total_collisions;
            this->updated = r.updated;
        }

        return *this;
    }

    /*! Cantidad de nodos en el coloreo
     *
     * @return nodos en el coloreo
     */
    inline std::size_t size() const {
        return graph.size();
    }

    /*!
     * @return true si todos los nodos tienen un color
     */

    inline bool complete() const {
        return (left == 0);
    }

    /*!
     *
     * @param index número de nodo
     * @return true si el nodo index está coloreado
     */
    inline bool isset(std::size_t index) const {
        return (get(index) != uncolored());
    }

    /*! Devuelve el color de un nodo
     *
     * @param index número de nodo
     * @return color del nodo index, uncolored() si no tiene color
     */
    inline std::size_t get(std::size_t index) const {
    #ifdef DEBUG
        if (index >= size()) {
            throw std::out_of_range("Indice fuera de rango");
        }
    #endif

        return colors[index];
    }

    /*! Cambia el color de un nodo
     *
     * @param index número de nodo
     * @param color nuevo color a asignar
     * @return antiguo color del nodo index, uncolored() si no tenía color
     */
    inline std::size_t set(std::size_t index, std::size_t color) {
    #ifdef DEBUG
        if (index >= size()) {
            throw std::out_of_range("Indice fuera de rango");
        }

        // TODO: verificar que el color esté en rango para el índice
    #endif

        if (colors[index] == uncolored() && color != uncolored()) {
            --left;
        } else if (colors[index] != uncolored() && color == uncolored()) {
            ++left;
        }

        updated = false;
        return (colors[index] = color);
    }

    /*! Descolorea un nodo
     *
     * @param index número de nodo
     * @return antiguo color del nodo index, uncolored() si no tenía color
     */
    inline std::size_t unset(std::size_t index) {
        return set(index, uncolored());
    }

    /*! Devuelve la cantidad de conflictos para todos los nodos en total, contados por única vez.
     *
     * @return cantidad de conflictos en total
     */
    std::size_t conflicts() {
        update_collisions();
        return total_collisions;
    }

    /*! Devuelve la cantidad de conflictos de un nodo
     *
     * @param index número de nodo
     * @return cantidad de conflictos con sus vecinos coloreados
     */
    std::size_t conflicts(std::size_t index) {
#ifdef DEBUG
        if (index >= size()) {
            throw std::out_of_range("Indice fuera de rango");
        }

        if (!isset(index)) {
            throw std::runtime_error("No podemos computar conflictos para un nodo sin colorear");
        }
#endif
        update_collisions();
        return collisions[index];
    }

    /*! Devuelve la cantidad de conflictos para cada vertice. Si el vertice no está coloreado, la cantidad de conflictos
     * es 0.
     *
     * @return arreglo con la cantidad de conflictos de cada vertice
     */
    const std::vector<std::size_t> &perVertexConflicts() {
        update_collisions();
        return collisions;
    }

    /*!
     * @return valor para representar que un nodo no está coloreado
     */
    inline std::size_t static uncolored() {
        return std::numeric_limits<std::size_t>::max();
    }

    /*! Destructor
     */
    virtual ~Coloring() { }
private:
    /*! Actualiza la cantidad de colisiones por vertice y demás indicadores */
    void update_collisions() {
        if (updated) {
            return;
        }

        total_collisions = 0;

        for (std::size_t i = 0; i < size(); ++i) {
            collisions[i] = 0;

            if (isset(i)) {
                for (std::size_t neighbour : graph.neighbours(i)) {
                    if (isset(neighbour) && get(neighbour) == get(i)) {
                        ++collisions[i];
                        ++total_collisions;
                    }
                }
            }
        }

        total_collisions /= 2;
        updated = true;
    }

    const Graph &graph;
    std::vector<std::size_t> colors;
    std::vector<std::size_t> collisions;
    std::size_t left;
    std::size_t total_collisions;
    bool updated;
};

inline std::ostream &operator<<(std::ostream &stream, const Coloring &coloring) {
    std::stringstream output;

    if (coloring.complete()) {
        for (std::size_t i = 0; i < coloring.graph.size() - 1; ++i) {
            output << coloring.get(i) << ' ';
        }

        output << coloring.get(coloring.graph.size() - 1) << std::endl;
    } else {
        output << "X" << std::endl;
    }

    stream << output.str();
    return stream;
}

#endif //ALGO3_TP3_COLORING_H
