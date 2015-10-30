
#include "Problem.h"

std::list<std::size_t> Problem::solve1 () {

}

twoSat() {
    int vertexN = 0;
    for(int x = 0; x < graph.size; ++x) {
        vertexN += graph.neighbors(x).size() == 1? 1 : 4;
    }
    std::vector<int> vertexCourse(vertexN, -1);
    Graph implicationGraph(vertexN);



}

korasaju(Graph implicationGraph) {
    std::stack S;
    int now = 0;
    std::vector<bool> checked(implicationGraph.size(), false);
    S.push_back(0);
    while(!S.empty()) {
        
    }
}


std::list<std::size_t> Problem::solve2 () {

}

std::list<std::size_t> Problem::solve3 () {

}

std::list<std::size_t> Problem::solve4 () {

}
