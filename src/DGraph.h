#ifndef ALGO3_TP3_DGRAPH_H
#define ALGO3_TP3_DGRAPH_H

#include <stack>
#include <vector>
#include <list>
#include <tuple>
#include <algorithm>
#include <sstream>

class DGraph {
    friend std::ostream &operator<<(std::ostream &, const DGraph &);
public:
    DGraph() : adjacency(0) { }

    /*! Constructor
     *
     * @param vertices cantidad de vertices en el grafo
     * @complexity O(n)
     */
    DGraph(std::size_t vertices) :
        adjacency(vertices),
        _parents(vertices) { }

    /*! Constructor por copia
     *
     * @param g objeto a copiar
     * @complexity O(n + m)
     */
    DGraph(const DGraph &g) :
        adjacency(g.adjacency),
        _parents(g._parents) { }

    /*! Constructor por movimiento
     *
     * @param g objeto a mover
     * O(1)
     */
    DGraph(DGraph &&g) :
        adjacency(std::move(g.adjacency)),
        _parents(std::move(g._parents)) { }

    /*! Operador de asignación
     *
     * @return referencia a la clase actual
     * @complexity O(n)
     */
    DGraph &operator=(const DGraph &r) {
        if (this != &r) {
            adjacency = r.adjacency;
            _parents = r._parents;
        }

        return *this;
    }

    void connect(std::size_t a, std::size_t b) {
    #ifdef DEBUG
        if (std::find(adjacency[a].begin(), adjacency[a].end(), b) != adjacency[a].end()) {
            throw std::runtime_error("Nodos ya conectados");
        }
    #endif

        adjacency[a].push_back(b);
        _parents[b].push_back(a);
    }

    inline std::size_t size() const {
        return adjacency.size();
    }

    inline std::size_t inDegree(std::size_t a) const {
        return _parents[a].size();
    }

    inline std::size_t outDegree(std::size_t a) const {
        return adjacency[a].size();
    }

    inline const std::list<std::size_t> &neighbours(std::size_t a) const {
        return adjacency[a];
    }

    inline const std::list<std::size_t> &parents(std::size_t a) const {
        return _parents[a];
    }

    void transpose() {
        for (std::size_t i = 0; i < adjacency.size(); ++i) {
            adjacency[i].swap(_parents[i]);
        }
    }

    std::pair<std::list<std::list<std::size_t>>, std::vector<std::size_t>> kosaraju() {
        std::vector<bool> is_in_stack(size(), false);
        std::stack<std::size_t> nodes;

        std::size_t current = 0;

        while (nodes.size() < size()) {
            // Obtenemos el proximo nodo que no este en el stack
            while (is_in_stack[current]) {
                ++current;
            }

            // Current es el nodo por el que debo hacer el dfs.
            std::stack<std::size_t> pending;
            std::vector<bool> visited(size(), false);
            pending.push(current);
            visited[current] = true;

            while (!pending.empty()) {
                std::size_t expand = pending.top();
                pending.pop();

                bool modified = false;

                for (auto &x : neighbours(expand)) {
                    if (!visited[x] && !is_in_stack[x]) {
                        visited[x] = true;
                        pending.push(x);
                        modified = true;
                    }
                }

                if (!modified && !is_in_stack[expand]) {
                    nodes.push(expand);
                    is_in_stack[expand] = true;
                }
            }
        }

        // Damos vuelta las flechas del grafo
        transpose();

        int current_scc = 0;
        std::vector<std::size_t> scc(size(), 0);
        std::list<std::list<std::size_t>> output;

        while (!nodes.empty()) {
            // Ignore nodes already processed

            while (!nodes.empty() && !is_in_stack[nodes.top()]) {
                nodes.pop();
            }

            if (nodes.empty()) {
                break;
            }

            std::size_t now = nodes.top();
            nodes.pop();

            // Start new strongly connected component
            output.push_back(std::list<std::size_t>());
            output.back().push_back(now);
            is_in_stack[now] = false;
            scc[now] = current_scc;

            // Complete the SCC with nodes found while doing a DFS
            std::stack<std::size_t> dfs;
            dfs.push(now);

            while (!dfs.empty()) {
                std::size_t v = dfs.top();
                dfs.pop();
                for (auto &neighbour : neighbours(v)) {
                    if (is_in_stack[neighbour]) {
                        output.back().push_back(neighbour);
                        is_in_stack[neighbour] = false;
                        scc[neighbour] = current_scc;
                        dfs.push(neighbour);
                    }
                }
            }

            ++current_scc;
        }

        // Volvemos los ejes a la normalidad
        transpose();

        return std::make_pair(output, scc);
    }
private:
    std::vector<std::list<std::size_t>> adjacency;
    std::vector<std::list<std::size_t>> _parents;
};

inline std::ostream &operator<<(std::ostream &stream, const DGraph &graph) {
    std::stringstream output;

    output << "digraph {" << std::endl;

    for (std::size_t i = 0; i < graph.size(); ++i) {
        output << i << ";" << std::endl;
    }

    for (std::size_t i = 0; i < graph.size(); ++i) {
        for (auto &neighbour : graph.neighbours(i)) {
            output << i << " -> " << neighbour << ";" << std::endl;
        }
    }

    output << "}" << std::endl;
    stream << output.str();

    return stream;
}

#endif //ALGO3_TP3_DGRAPH_H
