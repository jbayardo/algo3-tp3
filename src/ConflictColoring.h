#ifndef ALGO3_TP3_CONFLICTCOLORING_H
#define ALGO3_TP3_CONFLICTCOLORING_H

#include "Coloring.h"

/*! Guarda un coloreo parcial o total para un grafo, con información sobre las colisiones entre los nodos
 */
class ConflictColoring : public Coloring {
    friend std::ostream &operator<<(std::ostream &, const ConflictColoring &);
public:
    /*! Constructor
     *
     * @param g grafo de referencia
     * @complexity O(n)
     */
    ConflictColoring(const Graph &g) :
            Coloring(g),
            collisions(g.size(), 0),
            total_collisions(0),
            updated(true) { }

    /*! Constructor
     *
     * @param c coloreo sin datos de colisiones
     * @complexity O(n)
     */
    ConflictColoring(const Coloring &c) :
            Coloring(c),
            collisions(graph.size(), 0),
            total_collisions(0),
            updated(false) { }

    /*! Constructor por copia
     *
     * @param c coloreo a copiar
     * @complexity O(n)
     */
    ConflictColoring(const ConflictColoring &c) :
            Coloring(c),
            collisions(c.collisions),
            total_collisions(c.total_collisions),
            updated(c.updated) { }

    /*! Constructor por movimiento
     *
     * @param c coloreo a mover
     * O(1)
     */
    ConflictColoring(ConflictColoring &&c) :
            Coloring(c),
            collisions(std::move(c.collisions)),
            total_collisions(c.total_collisions),
            updated(c.updated) { }

    /*! Operador de asignación
     *
     * @return referencia a la clase actual
     * @complexity O(n)
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
     * @complexity O(1)
     */
    inline std::size_t set(std::size_t index, std::size_t color) {
        std::size_t output = Coloring::set(index, color);
        updated = false;
        return output;
    }

    /*! Cambia el color de un nodo, actualizando la información de conflictos
     *
     * @param index número de nodo
     * @param color nuevo color a asignar
     * @return antiguo color del nodo index, uncolored() si no tenía color
     * @complexity O(N) worst case, O(1) best case
     */
    std::size_t setu(std::size_t index, std::size_t color) {
        std::size_t output = Coloring::set(index, color);

        if (updated) {
            total_collisions -= collisions[index];
            collisions[index] = 0;

            for (auto &neighbour : graph.neighbours(index)) {
                if (isset(neighbour)) {
                    if (get(neighbour) == output) {
                        --collisions[neighbour];
                        total_collisions -= 2;
                    }

                    if (get(neighbour) == color) {
                        ++collisions[neighbour];
                        ++collisions[index];
                        total_collisions += 2;
                    }
                }
            }
        }

        return output;
    }

    /*! Devuelve la cantidad de conflictos para todos los nodos en total, contados por única vez.
     *
     * @return cantidad de conflictos en total
     * @complexity O(1) best case, O(n + 1) worst case
     */
    std::size_t conflicts() {
        update_collisions();
        return total_collisions/2;
    }

    /*! Devuelve la cantidad de conflictos de un nodo
     *
     * @param index número de nodo
     * @return cantidad de conflictos con sus vecinos coloreados
     * @complexity O(1) best case, O(n + 1) worst case
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
     * @complexity O(1) best case, O(n + m) worst case
     */
    const std::vector<std::size_t> &perVertexConflicts() {
        update_collisions();
        return collisions;
    }

    /*! Destructor
     */
    virtual ~ConflictColoring() { }

private:
    /*! Actualiza la cantidad de colisiones por vertice y demás indicadores
     *
     * @complexity O(1) best case, O(n + m) worst case
     */
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

        updated = true;
    }

protected:
    std::vector<std::size_t> collisions;
    std::size_t total_collisions;
    bool updated;
};

/*! Imprime un coloreo
 *
 * @param stream stream en el que imprimir
 * @param coloring coloreo a imprimir
 * @return nuevo stream, con los cambios realizados
 * @complexity O(n)
 */
inline std::ostream &operator<<(std::ostream &stream, ConflictColoring &coloring) {
    std::stringstream output;

#if defined(DEBUG) || defined(EXPS)
    for (std::size_t i = 0; i < coloring.size(); ++i) {
        if (coloring.isset(i)) {
            output << coloring.get(i) << ' ';
        } else {
            output << "X ";
        }
    }

    output << std::endl;

    output << coloring.conflicts() << std::endl;

    for (auto &conflict : coloring.perVertexConflicts()) {
        output << conflict << ' ';
    }

    output << std::endl;
#else
    if (coloring.complete()) {
        for (std::size_t i = 0; i < coloring.size() - 1; ++i) {
            output << coloring.get(i) << ' ';
        }

        output << coloring.get(coloring.size() - 1) << std::endl;
    } else {
        output << "X" << std::endl;
    }
#endif

    stream << output.str();
    return stream;
}

#endif //ALGO3_TP3_CONFLICTCOLORING_H
