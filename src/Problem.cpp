
#include <iterator> 
#include <fstream>
#include <stdexcept>
#include "Problem.h"
#include "Statistics.h"

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
                solve1();
            }

            return solve1();
        case 2:
            for (auto i = 0; i < runs - 1; ++i) {
                solve2();
            }

            return solve2();
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

}

twoSat() {
	struct state {
		int is;
		int isNot;
	};

	std::vector<std::vector<state>> vertexData(graph.size(), std::vector<state>(2));
	DGraph implicationGraph(colors.totalNumber()*2);
	int v = 0;
	int end = graph.size();

	// Assign a vertex for every node's color and its negation, in the new graph
	for (int i = 0; i < end; ++i) {
		int li = 0;
		for (auto color : colors.get(i)) {
			vertexData[i][li].is = v++;
			vertexData[i][li++].isNot = v++;
		}
	}

	// Build the implications
	// For every vertex
	for (int i = 0; i < end; ++i) {
		std::list<std::size_t>& myColors = colors.get(i)
		// go through its neighbors
		for (auto neighbor : graph.neighbors(i)) {
			int ic = 0;
			// Check if there is an intersection in its colors
			for (auto myColor : myColors) {
				int icn = 0;
				// Go through every neighbor possible color
				for (auto neighborColor, colors.get(neighbor)) {
					if (myColor == neighborColor) {
						// if its the same color I can color just one node at the same time
						implicationGraph.connect(vertexData[i][ic].is, vertexData[neighbor][icn].isNot);
						implicationGraph.connect(vertexData[i][ic].isNot, vertexData[neighbor][icn].is);
					} else {
						// if its a different color, I can color both nodes in freely
						implicationGraph.connect(vertexData[i][ic].is, vertexData[neighbor][icn].is);
						implicationGraph.connect(vertexData[i][ic].is, vertexData[neighbor][icn].isNot);
						implicationGraph.connect(vertexData[i][ic].isNot, vertexData[neighbor][icn].is);
						implicationGraph.connect(vertexData[i][ic].isNot, vertexData[neighbor][icn].isNot);
					}
					icn++;
				}
				ic++;
			}
		}

		if (myColors.size() == 1) {
			// if a vertex has only one color I have to build a truth statement somehow
			implicationGraph.connect(vertexData[i][0].isNot, vertexData[neighbor][0].is);
		} else {
			int c = 0;
			for (auto color : myColors) {
				int oc = 0;
				for (auto otherColor : myColors) {
					if (color != otherColor) {
						implicationGraph.connect(vertexData[i][c].is, vertexData[neighbor][oc].isNot);
						implicationGraph.connect(vertexData[i][c].isNot, vertexData[neighbor][oc].is);
					}
					oc++;
				}
				c++;
			}
		}	
	}

	int size = implicationGraph.size()
	std::vector<bool> isInStack(size, false);
	std::stack<int> nodes;
	int now = 0;
	while (nodes.size() != size) {
		while (isInStack[now]) ++now;
		
		std::stack<int> dfs;
		std::vector<bool> isInDfsStack(size, false);
		while (dfs.)
	}
}

korasaju(Graph implicationGraph) {
	std::stack S;
	int now = 0;
	std::vector<bool> checked(implicationGraph.size(), false);
	S.push_back(0);
	while(!S.empty()) {
		
	}
}

Coloring Problem::solve2() const {
    Timer timer("Backtracking Timer");
    std::stack<Coloring> pending;
    // Generamos el coloreo vacio
    pending.push(Coloring(graph));

    while (!pending.empty()) {
        Coloring current = pending.top();
        pending.pop();

        // Chequeo si redujimos a 2 list coloring
        if (2 list coloring) {
            return ...;
        } else {
            // Genero todas las alternativas
            for () {
                Coloring generated(current);

                if (generated.admissible(colors)) {
                    pending.push(generated);
                }
            }
        }
    }
}

Coloring Problem::solve3() const {
    auto vertex_order = graph.descendingByDegree();
    auto coloring = Coloring(graph);

    for (auto& v: vertex_order) {
        auto conflicts = std::numeric_limits<std::size_t>::max();
        auto choice = 0;

        for (auto& c: colors.get(v)) {
            auto current_conflicts = 0;

            for (auto& n: graph.neighbors(v)) {
                if (coloring.get(n) == c) {
                    current_conflicts++;
                }
            }

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

}

Coloring Problem::solve4() const {
}
