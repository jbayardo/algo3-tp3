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
    std::size_t inline size() const;

    /*!
     * @return true si todos los nodos tienen un color
     */
    bool inline complete() const;

    /*!
     * @param index número de nodo
     * @return true si el nodo index está coloreado
     */
    bool inline isset(std::size_t index) const;

    /*! Devuelve el color de un nodo
     *
     * @param index número de nodo
     * @return color del nodo index, uncolored() si no tiene color
     */
    std::size_t inline get(std::size_t index) const;

    /*! Cambia el color de un nodo
     *
     * @param index número de nodo
     * @param color nuevo color a asignar
     * @return antiguo color del nodo index, uncolored() si no tenía color
     */
    std::size_t inline set(std::size_t index, std::size_t color);

    /*! Descolorea un nodo
     *
     * @param index número de nodo
     * @return antiguo color del nodo index, uncolored() si no tenía color
     */
    std::size_t inline unset(std::size_t index);

    /*! Verifica si un coloreo es admisible, es decir, si los colores pertenecen a las listas de los nodos y ningún
     * nodo tiene el mismo color en su vecindad.
     *
     * @return true si el coloreo es admisible
     */
    bool admissible(const ColorStorage &storage) const;

    /*! Destructor
     */
    virtual ~Coloring();

    /*!
     * @return valor para representar que un nodo no está coloreado
     */
    std::size_t static inline uncolored() {
        return std::numeric_limits<std::size_t>::max();
    }
private:
    std::vector<std::size_t> colors;
    std::size_t left;
    const Graph &graph;
};

#endif //ALGO3_TP3_COLORING_H