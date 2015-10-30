#ifndef ALGO3_TP3_GRAPH_H
#define ALGO3_TP3_GRAPH_H

#include <vector>
#include <list>
#include <algorithm>
#include <queue>

class Graph {
public:
    Graph(std::size_t vertices) : adjacency(vertices) { };

    std::size_t size() const { return adjacency.size(); }
    std::size_t degree(std::size_t a) const { return adjacency[a].size(); }

    void connect(std::size_t a, std::size_t b) {
#ifdef DEBUG
        if (std::find(adjacency[a].begin(), adjacency[a].end(), b) != adjacency[a].end()) {
            throw std::runtime_error("Nodes already connected");
        }
#endif

        adjacency[a].push_back(b);
        adjacency[b].push_back(a);
    }

    const std::list<std::size_t>& neighbors(std::size_t a) const { return adjacency[a]; }
    // std::list<std::size_t> neighbors(std::size_t a) const { return adjacency[a]; }
private:
    std::vector<std::list<std::size_t>> adjacency;
};

/**
 * @param graph Grafo de entrada
 * @complexity \Omega(n + m)
 * @return Lista de componentes conexas del grafo, como grafos separados
 */
std::list<Graph> components(Graph &graph) {
    std::list<Graph> output;
    std::vector<bool> visited(graph.size(), false);

    for (std::size_t i = 0; i < visited.size(); ++i) {
        if (!visited[i]) {
            // Encontramos un nodo que todavia no esta en ninguna componente
            Graph component(graph.size()); // TODO: esto esta desperdiciando espacio al pedo, hay que arreglarlo

            // Comenzamos un BFS desde el nodo
            std::queue<std::size_t> next;
            next.push(i);

            while (!next.empty()) {
                std::size_t current = next.front();
                next.pop();

                // Recorremos los vecinos, agregando lo que haga falta
                for (auto &neighbor : graph.neighbors(current)) {
                    if (!visited[neighbor]) {
                        // Si el nodo todavia no fue visitado, lo encolamos
                        next.push(neighbor);

                        // Creamos sus conexiones en el grafo nuevo
                        component.connect(current, next);
                    }
                }

                visited[current] = true;
            }

            output.push_back(component);
        }
    }

    return output;
}


#endif //ALGO3_TP3_GRAPH_H
