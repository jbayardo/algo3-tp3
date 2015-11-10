#include <stack>
#include "Problem.h"
#include "DGraph.h"

std::list<std::list<std::size_t>> korasaju(DGraph& implication_graph, std::vector<std::size_t>& node_scc) {
    std::stack<std::size_t> nodes;
    int size = implication_graph.size();
    int now = 0;
    std::vector<bool> is_in_stack(implication_graph.size(), false);

    while (nodes.size() != size) {
        while (is_in_stack[now]) {
            ++now;
        }

        std::stack<std::size_t> dfs;
        std::vector<bool> discovered(size, false);
        dfs.push(now);
        // Perform a dfs from this vertex
        while (!dfs.empty()) {
            std::size_t v = dfs.top();
            dfs.pop();
            if (!discovered[v]) {
                discovered[v] = true;
                std::size_t expansion = 0;
                for (auto neighbour : implication_graph.neighbours(v)) {
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

    // Reverse edges
    implication_graph.transpose();

    int scc_number = 0;
    std::list<std::list<std::size_t>> res;
    while (!nodes.empty()) {
        // Ignore nodes already processed
        while (!is_in_stack[nodes.top()]) nodes.pop();
        if (nodes.empty()) break;

        now = nodes.top();
        nodes.pop();

        // Start new strongly connected component
        res.push_back(std::list<std::size_t>());
        res.back().push_back(now);
        is_in_stack[now] = false;
        node_scc[now] = scc_number;

        // Complete the SCC with nodes found while doing a DFS
        std::stack<std::size_t> dfs;
        dfs.push(now);
        while (!dfs.empty()) {
            std::size_t v = dfs.top();
            dfs.pop();
            for (auto neighbour : implication_graph.neighbours(v)) {
                if (is_in_stack[neighbour]) {
                    res.back().push_back(neighbour);
                    is_in_stack[neighbour] = false;
                    node_scc[neighbour] = scc_number;
                    dfs.push(neighbour);
                }
            }
        }
        ++scc_number;
    }

    return res;
}

Coloring Problem::solve1() const {
    struct state {
        std::size_t is;
        std::size_t isNot;
        std::size_t color;
    };

    std::vector<std::vector<state>> vertex_data(graph.size(), std::vector<state>(2));
    std::vector<std::size_t> state_to_vertex(colors.total_number()*2);
    DGraph implication_graph(colors.total_number()*2);

    int v = 0;
    int end = graph.size();

    // Assign a vertex for every node's color and its negation, in the new graph
    for (int i = 0; i < end; ++i) {
        int li = 0;
        for (auto color : colors.get(i)) {
            vertex_data[i][li].color = color;

            vertex_data[i][li].is = v;
            state_to_vertex[v] = i;

            ++v;
            vertex_data[i][li++].isNot = v;
            state_to_vertex[v] = i;

            ++v;
        }
    }

    // Build the implications
    // For every vertex
    for (int i = 0; i < end; ++i) {
        std::list<std::size_t> myColors = colors.get(i);
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

    std::vector<std::size_t> node_scc(implication_graph.size());
    std::list<std::list<std::size_t>> s_c_c = korasaju(implication_graph, node_scc);

    Coloring c(graph);
    // Check if variable and negation are in the same strongly connected component
    for (auto node : vertex_data) {
        for (auto state : node) {
            if (node_scc[state.is] == node_scc[state.isNot]) return c;
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

    std::vector<bool> s_c_c_states(s_c_c.size());
    // TODO

    return c;
}