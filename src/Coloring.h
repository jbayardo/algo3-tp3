#ifndef ALGO3_TP3_COLORING_H
#define ALGO3_TP3_COLORING_H

#include <vector>
#include <ostream>
#include "Graph.h"
#include "ColorStorage.h"

/*! Guarda un coloreo parcial o total para un grafo.
 */
class Coloring {
    friend std::ostream &operator<<(std::ostream &stream, const Coloring &bracelet);
public:
    /*! Constructor
     * @param g grafo de referencia
     */
    Coloring(const Graph &g);

    /*! Constructor por copia
     * @param c coloreo a copiar
     */
    Coloring(const Coloring &c);

    /*! Operador de asignación
     *
     * @return referencia a la clase actual
     */
    Coloring & operator=(const Coloring &r);

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
     * @param index número de nodo
     * @return true si el nodo index está coloreado
     */
    inline bool isset(std::size_t index) const {
    #ifdef DEBUG
        if (index >= size()) {
            throw std::out_of_range("Indice fuera de rango");
        }
    #endif

        return (colors[index] != uncolored());
    }

    /*! Devuelve el color de un nodo
     *
     * @param index número de nodo
     * @return color del nodo index, uncolored() si no tiene color
     */
    inline std::size_t  get(std::size_t index) const {
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
    inline std::size_t  set(std::size_t index, std::size_t color) {
    #ifdef DEBUG
        if (index >= size()) {
            throw std::out_of_range("Indice fuera de rango");
        }

        // TODO: verificar que el color esté en rango para el índice
    #endif

        if (colors[index] == uncolored()) {
            --left;
        }

        return (colors[index] = color);
    }

    /*! Descolorea un nodo
     *
     * @param index número de nodo
     * @return antiguo color del nodo index, uncolored() si no tenía color
     */
    inline std::size_t  unset(std::size_t index) {
    #ifdef DEBUG
        if (index >= size()) {
            throw std::out_of_range("Indice fuera de rango");
        }
    #endif

        if (colors[index] != uncolored()) {
            ++left;
        }

        return (colors[index] = uncolored());
    }

    /*! Cuenta conflictos de coloreo para un nodo
     *
     * @param index número de nodo
     * @return cantidad de conflictos con sus vecinos coloreados
     */
    std::size_t conflicts(std::size_t index) const;

    std::vector<std::size_t> perVertexConflicts() const {
        std::vector<std::size_t> vertex_conflicts(this->size(), 0);

        for (std::size_t i = 0; i < size(); ++i) {
            if (isset(i)) {
                for (auto &neighbour : graph.neighbours(i)) {
                    if (this->isset(neighbour) && get(neighbour) != get(i)) {
                        ++vertex_conflicts[i];
                    }
                }
            }
        }

        return vertex_conflicts;
    }

    /*! Destructor
     */
    virtual ~Coloring();

    /*!
     * @return valor para representar que un nodo no está coloreado
     */
    inline std::size_t static  uncolored() {
        return std::numeric_limits<std::size_t>::max();
    }

    inline std::size_t collisions() const {
        auto current_collisions = 0;

        for (auto &c: perVertexConflicts()){
            current_collisions += c;
        }

        return current_collisions;
    }
private:
    const Graph &graph;
    std::vector<std::size_t> colors;
    std::size_t left;
};

#endif //ALGO3_TP3_COLORING_H
