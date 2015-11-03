
#include "Problem.h"
#include "DGraph.h"
#include <iterator> 

std::list<std::size_t> Problem::solve1() {
	auto result = std::list<std::size_t>();

	return result;
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
}

korasaju(Graph implicationGraph) {
	std::stack S;
	int now = 0;
	std::vector<bool> checked(implicationGraph.size(), false);
	S.push_back(0);
	while(!S.empty()) {
		
	}
}


std::list<std::size_t> Problem::solve2() {
	auto result = std::list<std::size_t>();

	return result;
}

std::list<std::size_t> Problem::solve3() {
	auto result = std::list<std::size_t>();
	auto ascending = colors.ascendingByColor();

	return result;
}


std::list<std::size_t> Problem::solve4() {
	auto result = std::list<std::size_t>();

	return result;
}
