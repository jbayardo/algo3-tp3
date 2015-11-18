#include <list>
#include <vector>
#include <stack>
#include <iostream>
#include "Problem.h"
#include "Statistics.h"
#include "DGraph.h"

#define TO_IMPLICATION_INDEX(vertex, color, neg) (4*vertex + 2*color + ((neg == true)? 0:1))
#define GET_VERTEX(vertex) (vertex/4)
#define GET_COLOR(vertex) ((vertex % 4)/2)
#define GET_NEG(vertex) (((vertex % 4) % 2) == 0)

class Problem1 {
    enum ComponentState {
        True,
        False,
        Unset
    };
public:
    Problem1(const Graph &graph_, const ColorStorage &colors_) : graph(graph_), colors(colors_) { }

    Coloring solve() const {
        Timer timer("Exercise 1 Timer");

        // Armamos el grafo de implicaciones
        DGraph implications = buildImplicationGraph();
        // Corremos Kosaraju
        std::pair<std::list<std::list<std::size_t>>, std::vector<std::size_t>> kosaraju = implications.kosaraju();

        // Obtenemos la información que devuelve Kosaraju
        std::list<std::list<std::size_t>> &components = kosaraju.first;
        std::vector<std::size_t> &belongs = kosaraju.second;

        // Creamos la salida de la función
        Coloring output(graph);

        // Verificamos que no haya contradicciones
        for (std::size_t i = 0; i < implications.size(); ++i) {
            std::size_t complement = TO_IMPLICATION_INDEX(GET_VERTEX(i), GET_COLOR(i), !GET_NEG(i));

            if (belongs[i] == belongs[complement]) {
                // Tenemos un nodo y su negación en la misma componente conexa. Salir.
                return output;
            }
        }

        // Armamos el grafo de las componentes conexas
        DGraph induced(components.size());

        for (std::size_t i = 0; i < implications.size(); ++i) {
            for (auto &neighbour : implications.neighbours(i)) {
                if (belongs[i] != belongs[neighbour]) {
                    induced.connect(belongs[i], belongs[neighbour]);
                }
            }
        }

        // Coloreamos!
        std::vector<ComponentState> induced_states(components.size(), ComponentState::Unset);

        std::size_t current = components.size() - 1;

        for (auto it = components.rbegin(); it != components.rend(); ++it) {
            if (induced_states[current] == ComponentState::Unset) {
                induced_states[current] = ComponentState::True;
            }

            if (induced_states[current] == ComponentState::True) {
                // Estamos en una componente verdadera
                for (auto &vertex : *it) {
                    std::size_t complement = TO_IMPLICATION_INDEX(GET_VERTEX(vertex), GET_COLOR(vertex), !GET_NEG(vertex));

                    switch (induced_states[belongs[complement]]) {
                        case ComponentState::Unset:
                            // Como la negación no tiene un valor de verdad, queda claro que debe ser falso.
                            induced_states[belongs[complement]] = ComponentState::False;
                            break;
                        case ComponentState::True:
                            // Encontramos una variable verdadera que tiene a su negación como verdadera.
                            // Es una contradicción
                            return output;
                        default:
                            break;
                    }

                    if (GET_NEG(vertex)) {
                        output.set(GET_VERTEX(vertex), getColorFromIndex(GET_VERTEX(complement), GET_COLOR(complement)));
                    } else {
                        output.set(GET_VERTEX(vertex), getColorFromIndex(GET_VERTEX(vertex), GET_COLOR(vertex)));
                    }
                }

                for (auto &neighbour : induced.neighbours(current)) {
                    if (induced_states[neighbour] == ComponentState::False) {
                        // Esta componente conexa está como verdadera, pero implica un falso. Esto es una contradicción
                        // Le saco un color, esto es por el caso borde en el que estamos en la topológicamente menor
                        output.unset(0);
                        return output;
                    }
                }
            } else {
                // Estamos en una componente falsa
                for (auto &vertex : *it) {
                    std::size_t complement = TO_IMPLICATION_INDEX(GET_VERTEX(vertex), GET_COLOR(vertex), !GET_NEG(vertex));

                    switch (induced_states[belongs[complement]]) {
                        case ComponentState::Unset:
                            // Como la negación no tiene un valor de verdad, queda claro que debe ser true.
                            induced_states[belongs[complement]] = ComponentState::True;
                            break;
                        case ComponentState::False:
                            // Encontramos una variable verdadera que tiene a su negación como falsa.
                            // Es una contradicción
                            return output;
                        default:
                            break;
                    }

                    if (GET_NEG(vertex)) {
                        output.set(GET_VERTEX(vertex), getColorFromIndex(GET_VERTEX(vertex), GET_COLOR(vertex)));
                    } else {
                        output.set(GET_VERTEX(vertex), getColorFromIndex(GET_VERTEX(complement), GET_COLOR(complement)));
                    }
                }

                for (auto &parent : induced.parents(current)) {
                    if (induced_states[parent] == ComponentState::True) {
                        // Esta componente conexa está como falsa, pero es implicada por un verdadero. Es contradicción
                        // Le saco un color, esto es por el caso borde en el que estamos en la topológicamente menor
                        output.unset(0);
                        return output;
                    }
                }
            }

            --current;
        }

        return output;
    }
private:
    DGraph buildImplicationGraph() const {
        // Vamos a utilizar nodos fantasma
        DGraph implications(4*graph.size());

        for (std::size_t vertex = 0; vertex < graph.size(); ++vertex) {
            // Primero conectamos a los colores del vertice con sí mismo
            if (colors.get(vertex).size() == 1) {
                // Tenemos exactamente 1 color
                implications.connect(TO_IMPLICATION_INDEX(vertex, 0, false), TO_IMPLICATION_INDEX(vertex, 0, true));
            } else {
                // Tenemos exactamente 2 colores
                implications.connect(
                        TO_IMPLICATION_INDEX(vertex, 0, true),
                        TO_IMPLICATION_INDEX(vertex, 1, false));

                implications.connect(
                        TO_IMPLICATION_INDEX(vertex, 1, false),
                        TO_IMPLICATION_INDEX(vertex, 0, true));

                implications.connect(
                        TO_IMPLICATION_INDEX(vertex, 0, false),
                        TO_IMPLICATION_INDEX(vertex, 1, true));

                implications.connect(
                        TO_IMPLICATION_INDEX(vertex, 1, true),
                        TO_IMPLICATION_INDEX(vertex, 0, false));
            }

            // Luego conectamos al vertice con los vecinos
            for (auto &neighbour : graph.neighbours(vertex)) {
                // Nos salteamos a los que ya hayamos insertado en el grafo de implicaciones
                if (neighbour < vertex) {
                    continue;
                }

                std::set<std::size_t> intersection;

                // Calculamos la intersección con el vecino
                std::set_intersection(
                        colors.get(vertex).begin(), colors.get(vertex).end(),
                        colors.get(neighbour).begin(), colors.get(neighbour).end(),
                        std::inserter(intersection, intersection.begin()));

                if (intersection.size() == 1) {
                    // Tenemos 1 solo color en común
                    std::size_t color = *(intersection.begin());
                    std::size_t indexVertex = getColorIndex(vertex, color);
                    std::size_t indexNeighbour = getColorIndex(neighbour, color);

                    implications.connect(
                            TO_IMPLICATION_INDEX(vertex, indexVertex, true),
                            TO_IMPLICATION_INDEX(neighbour, indexNeighbour, false));

                    implications.connect(
                            TO_IMPLICATION_INDEX(neighbour, indexNeighbour, true),
                            TO_IMPLICATION_INDEX(vertex, indexVertex, false));
                } else if (intersection.size() == 2) {
                    std::size_t color0 = *(intersection.begin());
                    std::size_t indexVertex0 = getColorIndex(vertex, color0);
                    std::size_t indexNeighbour0 = getColorIndex(neighbour, color0);

                    std::size_t color1 = *(++intersection.begin());
                    std::size_t indexVertex1 = getColorIndex(vertex, color1);
                    std::size_t indexNeighbour1 = getColorIndex(neighbour, color1);

                    implications.connect(
                            TO_IMPLICATION_INDEX(vertex, indexVertex0, true),
                            TO_IMPLICATION_INDEX(neighbour, indexNeighbour0, false));

                    implications.connect(
                            TO_IMPLICATION_INDEX(neighbour, indexNeighbour0, true),
                            TO_IMPLICATION_INDEX(vertex, indexVertex0, false));

                    implications.connect(
                            TO_IMPLICATION_INDEX(vertex, indexVertex1, true),
                            TO_IMPLICATION_INDEX(neighbour, indexNeighbour1, false));

                    implications.connect(
                            TO_IMPLICATION_INDEX(neighbour, indexNeighbour1, true),
                            TO_IMPLICATION_INDEX(vertex, indexVertex1, false));
                }
            }
        }

        return implications;
    }

    std::size_t getColorIndex(std::size_t vertex, std::size_t colour) const {
#ifdef DEBUG
        if (colors.get(vertex).find(colour) == colors.get(vertex).end()) {
            throw std::out_of_range("Color not found");
        }
#endif

        std::size_t index = 0;

        if (*(colors.get(vertex).begin()) != colour) {
            ++index;
        }

        return index;
    }

    std::size_t getColorFromIndex(std::size_t vertex, std::size_t index) const {
#ifdef DEBUG
        if (index >= 2) {
            throw std::out_of_range("Color index out of range");
        }
#endif

        auto it = colors.get(vertex).begin();

        while (index > 0) {
            ++it;
            --index;
        }

        return *it;
    }

    const Graph &graph;
    const ColorStorage &colors;
};

Coloring Problem::solve1() const {
    Problem1 instance(graph, colors);
    return instance.solve();
}
