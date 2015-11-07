#include "Problem.h"

Problem::Problem(std::string input) {
    std::ifstream handle;
    handle.open(input, std::ifstream::in);

    if (!handle.is_open()) {
        throw std::runtime_error("Fallo al abrir el archivo de tests");
    }

    handle >> vertices >> edges >> nColors;

    if (nColors <= 0) {
        throw std::runtime_error("Error reading file: number of colors must be higher than 0");
    }

    colors = ColorStorage(vertices);

    for (std::size_t vertex = 0; vertex < vertices; ++vertex) {
        std::size_t readColors;
        handle >> readColors;

        if (readColors <= 0) {
            throw std::runtime_error("Error reading file: number of current colors must be higher than 0");
        }

        std::list<std::size_t> current;

        for (std::size_t c = 0; c < readColors; ++c) {
            std::size_t color;
            handle >> color;

            if (color >= nColors) {
                throw std::runtime_error("Invalid color number");
            }

            current.push_back(color);
        }

        colors.add(vertex, current);
    }

    graph = Graph(vertices);

    for (std::size_t edge = 0; edge < edges; ++edge) {
        std::size_t from, to;
        handle >> from >> to;

        if (from >= vertices || to >= vertices) {
            throw std::runtime_error("Invalid edge");
        }

        graph.connect(from, to);
    }

    handle.close();
}

Coloring Problem::solve(int exercise, int runs) const {
    if (runs < 1) {
        throw std::out_of_range("La cantidad de corridas debe ser mayor a 0");
    }

    switch (exercise) {
        case 1:
            for (auto i = 0; i < runs - 1; ++i) {
                // solve1();
            }

            // return solve1();
            return Coloring(graph);
        case 2:
            for (auto i = 0; i < runs - 1; ++i) {
                // solve2();
            }

            // return solve2();
            return Coloring(graph);
        case 3:
            for (auto i = 0; i < runs - 1; ++i) {
                solve3();
            }

            return solve3();
        case 4:
            for (auto i = 0; i < runs - 1; ++i) {
                solve4();
            }

            return solve4();
        default:
            throw std::out_of_range("Los ejercicios estan numerados del 1 al 4");
    }
}

Coloring Problem::solve1() const {
	struct state {
		std::size_t is;
		std::size_t isNot;
		std::size_t color;
	};

	std::vector<std::vector<state>> vertex_data(graph.size(), std::vector<state>(2));
	DGraph implication_graph(colors.total_number()*2);
	int v = 0;
	int end = graph.size();

	// Assign a vertex for every node's color and its negation, in the new graph
	for (int i = 0; i < end; ++i) {
		int li = 0;
		for (auto color : colors.get(i)) {
			vertex_data[i][li].color = color;
			vertex_data[i][li].is = v++;
			vertex_data[i][li++].isNot = v++;

		}
	}

	// Build the implications
	// For every vertex
	for (int i = 0; i < end; ++i) {
		std::list<std::size_t> myColors = colors.get(i);
		// go through its neighbours
		for (auto neighbour : graph.neighbours(i)) {
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

	std::list<std::list<std::size_t>> s_c_c = korasaju(implication_graph);

	Coloring c(graph);
	return c;
}

std::list<std::list<std::size_t>> korasaju(DGraph& implication_graph) {
	std::stack<std::size_t> nodes;
	std::size_t size = implication_graph.size();
	std::size_t now = 0;
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
					dfs.push(neighbour);
				}
			}
		}
	}

	return res;
}

Coloring Problem::solve2() const {
    Timer timer("Backtracking Timer");
    std::stack<Coloring> pending;
    // Generamos el coloreo vacio
    pending.push(Coloring(graph));

    while (!pending.empty()) {
        Coloring current = pending.top();
        pending.pop();
    }
    Coloring c(graph);
    return c;
}


Coloring greedy_order(std::vector<std::size_t> vertex_order,
                      const Graph& graph,
                      const ColorStorage& colors) {
    auto coloring = Coloring(graph);

    for (auto& v: vertex_order) {
        auto choice = colors.get(v).front();
        auto conflicts = coloring.conflicts(choice);

        for (auto& c: colors.get(v)) {
            auto current_conflicts = coloring.conflicts(c);

            if (current_conflicts < conflicts) {
                choice = c;
                conflicts = current_conflicts;

                if (current_conflicts == 0) {
                    break;
                }
            }
        }
        coloring.set(v, choice);
    }
#ifdef DEBUG
    if (!coloring.complete()) {
        throw std::runtime_error("La heuristica golosa devolvió un coloreo incompleto");
    }
#endif

    return coloring;
}


Coloring Problem::solve3() const {
    auto vertex_order = graph.descendingByDegree();
    auto result = greedy_order(vertex_order, graph, colors);
    if (!result.complete()) {
        vertex_order = colors.ascendingByColor();
        result = greedy_order(vertex_order, graph, colors);
    }

    return result;
}

/**
 * @param input coloreo de entrada
 * @return mejor coloreo vecino
 */
Coloring neighbour(Coloring next, const ColorStorage& colors) {
    // Calculamos la cantidad de vecinos que vamos a mirar
    std::size_t size = 5;

    if (next.size() < size) {
        size = next.size();
    }

    // Obtenemos las colisiones
    std::vector<std::size_t> conflicts = next.perVertexConflicts();
    std::vector<std::size_t> vertices(size, std::numeric_limits<std::size_t>::max());

    // Obtenemos el mejor vecino
    for (std::size_t n = 0; n < size; ++n) {
        // Tomamos el n-esimo vertice con más colisiones
        // TODO: hacer menos cancro
        vertices[n] = n;

        for (std::size_t i = 0; i < conflicts.size(); ++i) {
            // Si el elemento actual tiene mas colisiones que el que habiamos seleccionado
            if (conflicts[i] > conflicts[vertices[n]]) {
                // Si el elemento actual no habia sido seleccionado previamente, lo seteamos
                bool skip = false;

                for (std::size_t j = 0; j < n; ++j) {
                    if (vertices[j] == i) {
                        skip = true;
                    }
                }

                if (!skip) {
                    vertices[n] = i;
                }
            }
        }

        // Obtengo el mejor color para el vertice que no sea el actual
        Coloring current(next);

        /* TODO: hay que integrar esta porqueria en el colorstorage */
        for (auto &color : colors.get(vertices[n])) {
            Coloring temporal(next);

            if (color != temporal.get(vertices[n])) {
                temporal.set(vertices[n], color);

                if (temporal.conflicts(vertices[n]) < current.conflicts(vertices[n])) {
                    current = temporal;
                }
            }
        }

        // Si mejora el coloreo actual, lo reemplazo!
        if (current.collisions() < next.collisions()) {
            next = current;
        }
    }

    return next;
}

Coloring Problem::solve4() const {
    Coloring current = solve3();

    // TODO: esto es delicado, podriamos quedarnos iterando en ciclos si no limitamos las iteraciones
    for (std::size_t iterations = 0; iterations < 1000; ++iterations) {
        Coloring next = neighbour(current, colors);

        if (next.collisions() >= current.collisions()) {
            return current;
        } else {
            current = next;
        }
    }

    return current;
}
