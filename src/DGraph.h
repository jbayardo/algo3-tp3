#ifndef ALGO3_TP3_DGRAPH_H
#define ALGO3_TP3_DGRAPH_H

#include <vector>
#include <list>
#include <tuple>
#include <algorithm>

class DGraph {
public:
    DGraph() : _adjacency(0) { }

    DGraph(std::size_t vertices) : _adjacency(vertices), _parents(vertices) { }

    void connect(std::size_t a, std::size_t b) {
    #ifdef DEBUG
        if (std::find(_adjacency[a].begin(), _adjacency[a].end(), b) != _adjacency[a].end()) {
            throw std::runtime_error("Nodes already connected");
        }
    #endif

        _adjacency[a].push_back(b);
        _parents[b].push_back(a);
    }

    inline std::size_t size() const {
        return _adjacency.size();
    }

    inline std::size_t inDegree(std::size_t a) const {
        return _parents[a].size();
    }

    inline std::size_t outDegree(std::size_t a) const {
        return _adjacency[a].size();
    }

    inline const std::list<std::size_t> &neighbours(std::size_t a) const {
        return _adjacency[a];
    }

    inline const std::list<std::size_t> &parents(std::size_t a) const {
        return _parents[a];
    }

    void transpose() {
        for (std::size_t i = 0; i < _adjacency.size(); ++i) {
            _adjacency[i].swap(_parents[i]);
        }
    }

    std::pair<std::list<std::list<std::size_t>>, std::vector<std::size_t>> kosaraju() {
        std::vector<std::size_t> node_scc(size(), 0);
        std::vector<bool> is_in_stack(size(), false);
        std::stack<std::size_t> nodes;
        int now = 0;

        while (nodes.size() != size()) {
            // Obtenemos el proximo nodo que no este en el stack
            while (is_in_stack[now]) {
                ++now;
            }

            // Hacemos un dfs desde el vertice actual
            std::stack<std::size_t> dfs;
            std::vector<bool> discovered(size(), false);
            dfs.push(now);

            while (!dfs.empty()) {
                std::size_t v = dfs.top();
                dfs.pop();

                if (!discovered[v]) {
                    discovered[v] = true;
                    std::size_t expansion = 0;

                    for (auto &neighbour : neighbours(v)) {
                        if (!discovered[neighbour]) {
                            expansion++;
                            dfs.push(neighbour);
                        }
                    }

                    // When we get to a vertex that cant keep expanding we push it into the original stack
                    if (expansion == 0 && !is_in_stack[v]) {
                        nodes.push(v);
                        is_in_stack[v] = true;
                    }
                }
            }
        }

        // Transponer los ejes
        transpose();

        int current_scc = 0;
        std::list<std::list<std::size_t>> output;

        while (!nodes.empty()) {
            // Ignore nodes already processed
            while (!is_in_stack[nodes.top()]) {
                nodes.pop();
            }

            if (nodes.empty()) {
                break;
            }

            now = nodes.top();
            nodes.pop();

            // Start new strongly connected component
            output.push_back(std::list<std::size_t>());
            output.back().push_back(now);
            is_in_stack[now] = false;
            node_scc[now] = current_scc;

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
                        node_scc[neighbour] = current_scc;
                        dfs.push(neighbour);
                    }
                }
            }

            ++current_scc;
        }

        // Volvemos los ejes a la normalidad
        transpose();

        return std::make_pair(output, node_scc);
    }
private:
    std::vector<std::list<std::size_t>> _adjacency;
    std::vector<std::list<std::size_t>> _parents;
};

#endif //ALGO3_TP3_DGRAPH_H
