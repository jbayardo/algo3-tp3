#ifndef ALGO3_TP3_CONFLICTCOLORING_H
#define ALGO3_TP3_CONFLICTCOLORING_H

#include "Coloring.h"

/*! Guarda un coloreo parcial o total para un grafo, con información sobre las colisiones entre los nodos
 */
class ConflictColoring : public Coloring {
public:
    /*! Constructor
     *
     * @param g grafo de referencia
     */
    ConflictColoring(const Graph &g) :
            Coloring(g),
            collisions(g.size(), 0),
            total_collisions(0),
            updated(true) { }

    /*! Constructor
     *
     * @param c coloreo sin datos de colisiones
     */
    ConflictColoring(const Coloring &c) :
            Coloring(c),
            collisions(graph.size(), 0),
            total_collisions(0),
            updated(false) { }

    /*! Constructor por copia
     *
     * @param c coloreo a copiar
     */
    ConflictColoring(const ConflictColoring &c) :
            Coloring(c),
            collisions(c.collisions),
            total_collisions(c.total_collisions),
            updated(c.updated) { }

    /*! Operador de asignación
     *
     * @return referencia a la clase actual
     */
    ConflictColoring &operator=(const ConflictColoring &r) {
        if (this != &r) {
            if (&graph != &r.graph) {
                throw std::runtime_error("Los coloreos deben pertenecer a un mismo grafo para ser asignados");
            }

            this->colors = r.colors;
            this->left = r.left;

            this->collisions = r.collisions;
            this->total_collisions = r.total_collisions;
            this->updated = r.updated;
        }

        return *this;
    }

    /*! Cambia el color de un nodo
     *
     * @param index número de nodo
     * @param color nuevo color a asignar
     * @return antiguo color del nodo index, uncolored() si no tenía color
     */
    inline std::size_t set(std::size_t index, std::size_t color) {
        std::size_t output = Coloring::set(index, color);
        updated = false;
        return output;
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

    /*! Destructor
     */
    virtual ~ConflictColoring() { }

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

protected:
    std::vector<std::size_t> collisions;
    std::size_t total_collisions;
    bool updated;
};

#endif //ALGO3_TP3_CONFLICTCOLORING_H
