#include <list>
#include <vector>
#include <stack>
#include <iostream>
#include "Problem.h"
#include "DGraph.h"

#define _TRUE 1
#define _FALSE 0
#define _NOTSET 2

Coloring Problem::solve1() const {
    struct state {
        std::size_t is;
        std::size_t isNot;
        std::size_t color;
    };
    DGraph implication_graph(colors.total_number()*2);
    // Aca para cada estado posible de cada variable guardo el nodo que representa su afirmacion y negacion
    std::vector<std::vector<state>> vertex_data(graph.size(), std::vector<state>(2));
    // Aca guardo la vuelta, dado un nodo del grafo de implicacion me da el estado al que pertenece
    std::vector<std::pair<std::size_t,std::size_t> > state_to_vertex(colors.total_number()*2);

    int v = 0;

    // Assign a vertex for every node's color and its negation, in the new graph
    for (int i = 0; i < graph.size(); ++i) {
        int li = 0;
        for (auto color : colors.get(i)) {
            vertex_data[i][li].color = color;

            vertex_data[i][li].is = v;
            state_to_vertex[v] = std::make_pair(i,li);

            ++v;
            vertex_data[i][li++].isNot = v;
            state_to_vertex[v] = std::make_pair(i,li);

            ++v;
        }
    }

    // Build the implications
    // For every vertex
    for (int i = 0; i < graph.size(); ++i) {
        const std::list<std::size_t> &myColors = colors.get(i);

        // go through its neighbours
        for (auto &neighbour : graph.neighbours(i)) {
            int ic = 0;

            // Check if there is an intersection in its colors
            for (auto myColor : myColors) {
                int icn = 0;

                // Go through every neighbour possible color
                for (auto neighbourColor : colors.get(neighbour)) {
                    if (myColor == neighbourColor) {
                        // if its the same color I can color just one node at the same time
                        implication_graph.connect(vertex_data[i][ic].is, vertex_data[neighbour][icn].isNot);
                        implication_graph.connect(vertex_data[i][ic].isNot, vertex_data[neighbour][icn].is);
                    } else {
                        // if its a different color, I can color both nodes in freely
                        // TODO: Check
                        implication_graph.connect(vertex_data[i][ic].is, vertex_data[neighbour][icn].is);
                        implication_graph.connect(vertex_data[i][ic].is, vertex_data[neighbour][icn].isNot);
                        implication_graph.connect(vertex_data[i][ic].isNot, vertex_data[neighbour][icn].is);
                        implication_graph.connect(vertex_data[i][ic].isNot, vertex_data[neighbour][icn].isNot);
                    }

                    icn++;
                }

                ic++;
            }
        }

        if (myColors.size() == 1) {
            // if a vertex has only one color I have to build a truth statement somehow
            implication_graph.connect(vertex_data[i][0].isNot, vertex_data[i][0].is);
        } else {
            int c = 0;
            for (auto color : myColors) {
                int oc = 0;
                for (auto otherColor : myColors) {
                    if (color != otherColor) {
                        implication_graph.connect(vertex_data[i][c].is, vertex_data[i][oc].isNot);
                        implication_graph.connect(vertex_data[i][c].isNot, vertex_data[i][oc].is);
                    }
                    oc++;
                }
                c++;
            }
        }
    }

    // Hacemos Kosaraju para el grafo de implicaciones
    std::pair<std::list<std::list<std::size_t>>, std::vector<std::size_t>> kosaraju = implication_graph.kosaraju();

    std::list<std::list<std::size_t>> &s_c_c = kosaraju.first;
    std::vector<std::size_t> &node_scc = kosaraju.second;

    Coloring c(graph);
    // Check if variable and negation are in the same strongly connected component

    for (auto node : vertex_data) {
        for (auto state : node) {
            if (node_scc[state.is] == node_scc[state.isNot]) {
                return c;
            }
        }
    }

    DGraph condensed(s_c_c.size());

    // Build the condesed graph
    for (int i = 0; i < node_scc.size(); ++i) {
        for (auto &neighbour : implication_graph.neighbours(i)) {
            // TODO: Ver de no conectar dos veces el mismo nodo
            // TODO: tener cuidado con los judios, estan siempre observando
            if (node_scc[i] != node_scc[neighbour]) {
                condensed.connect(node_scc[i], node_scc[neighbour]);
            }
        }
    }

    std::vector<char> s_c_c_states(s_c_c.size(), _NOTSET);

    std::size_t actual_scc = s_c_c.size() - 1;
    for (auto it = s_c_c.rbegin(); it != s_c_c.rend(); it++) {
        if (s_c_c_states[actual_scc] == _NOTSET) {
            s_c_c_states[actual_scc] = _TRUE;
        }
        if (s_c_c_states[actual_scc] == _TRUE) {
            // Itero por cada nodo de la componente fuertemente conexa
            for (auto node : *it) {
                std::size_t orig_node = state_to_vertex[node].first;
                std::size_t state_number = state_to_vertex[node].second;
                state node_state = vertex_data[orig_node][state_number];
                if (node_state.is == node) {
                    // El nodo representa una variable no negada en el grafo de implicaciones
                    // Por lo tanto el estado vale, entonces coloreamos el nodo del color de este estado
                    c.set(orig_node, node_state.color);
                    // La negacion de esta variable ahora es falsa porque su no negacion es verdadera
                    if (s_c_c_states[node_scc[node_state.isNot]] != _FALSE && s_c_c_states[node_scc[node_state.isNot]] != _NOTSET) {
                        // Colision!! 
                        return c;
                    } else {
                        s_c_c_states[node_scc[node_state.isNot]] = _FALSE;
                    }
                } else {
                    // El nodo representa una variable negada en el grafo de implicaciones
                    // La variable no negada es falsa porque su negacion es verdadera
                    if (s_c_c_states[node_scc[node_state.is]] != _FALSE && s_c_c_states[node_scc[node_state.is]] != _NOTSET) {
                        // Colision!!
                        return c;
                    } else {
                        s_c_c_states[node_scc[node_state.is]] = _FALSE;
                    }
                }
            }
            // Ahora me dijo si yo no implico ningun falso
            for (auto neighbour : condensed.neighbours(actual_scc)) {
                if (s_c_c_states[neighbour] == _FALSE) {
                    // Si es asi, hay un absurdo, asi que ya no sirve
                    return c;
                }
            }
        } else {
            // Itero por cada nodo de la componente fuertemente conexa
            for (auto node : *it) {
                std::size_t orig_node = state_to_vertex[node].first;
                std::size_t state_number = state_to_vertex[node].second;
                state node_state = vertex_data[orig_node][state_number];
                if (node_state.isNot == node) {
                    // El nodo representa una variable negada en el grafo de implicaciones
                    // Como la negacion es falsa, entonces la afirmacion es verdadera
                    // Por lo tanto coloreamos el nodo con el color correspondiente
                    c.set(orig_node, node_state.color);
                    // La negacion de esta variable ahora es falsa porque su no negacion es verdadera
                    if (s_c_c_states[node_scc[node_state.is]] != _TRUE && s_c_c_states[node_scc[node_state.is]] != _NOTSET) {
                        // Colision!! 
                        return c;
                    } else {
                        s_c_c_states[node_scc[node_state.is]] = _TRUE;
                    }
                } else {
                    // El nodo representa una variable no negada en el grafo de implicaciones
                    // La variable no negada es verdadera porque su negacion es falsa
                    if (s_c_c_states[node_scc[node_state.isNot]] != _TRUE && s_c_c_states[node_scc[node_state.isNot]] != _NOTSET) {
                        // Colision!!
                        return c;
                    } else {
                        s_c_c_states[node_scc[node_state.isNot]] = _TRUE;
                    }
                }
            }
            // Ahora me dijo si yo no me implica ningun verdadero
            for (auto neighbour : condensed.parents(actual_scc)) {
                if (s_c_c_states[neighbour] == _TRUE) {
                    // Si es asi, hay un absurdo, asi que ya no sirve
                    return c;
                }
            }
        }
        actual_scc--;
    }
    // TODO checkear que no haya absurdos en el grafo denso!!
    // Si no hubo colisiones entonces esta todo bien, y esta todo coloreado

    return c;
}
