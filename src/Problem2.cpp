#include <stack>
#include <iostream>
#include <list>
#include "Problem.h"
#include "Statistics.h"

Coloring Problem::solve2() const {
    Timer timer("Exercise 2 Timer");
    // std::stack<Coloring> pending;
    // // Generamos el coloreo vacio
    // pending.push(Coloring(graph));

    // while (!pending.empty()) {
    //     Coloring current = pending.top();
    //     pending.pop();

    //     if () {
    //         // Reducción a 2-sat
    //     } else {
    //         for () {
    //             pending.push();
    //         }
    //     }
    // }
    //
    //Coloring c(graph);
    //return c;
}

//checks if it's possible to assign currentColor to vertex v without conflict with neighbours
// bool isPossibleColor (const Graph& graph, int paintedNodes[],  int v, int currentColor) {

//     for (int i = 0; i < V; ++i) {

//         if (graph[v][i] && paintedNodes[i] != NULL && c == paintedNodes[i]) {

//             return false;

//         }

//     }
//     return true;

// }

//backtracking, returns True if there is a possible coloring and stores the coloring in paintedNodes
// bool coloringExists (const Graph& graph, const ColorLists& colors, int paintedNodes[V], int v) {
//     //base case, the algorithm called coloringExists without a valid vertex.
//     if (v == V) {

//         return true;

//     } else {
//         //backtrack for every possible color in current vertex
//         for (std::list<int>::iterator it = ColorsLists[v].begin(); it != colorsLists[v].end(); ++it) {

//             if (isPossibleColor(graph, paintedNodes, v, *it)) {
//                 //we paint vertex and backtrack to see possible outcomes with such configuration
//                 paintedNodes[v] = *it;

//                 if (coloringExists(graph, colors, paintedNodes, v+1)) {

//                     return true;

//                 } else {
//                     //such coloring didn't develop into a possible solution
//                     paintedNodes[v] = NULL;

//                 }
//             }

//         }
//         return false;
//     }
// }

// bool is2ListColoring (const &Graph graph, const ColorLists& colors, int v) {
//     // for every tuple of two colors, if every vertex has at least one of them, we run 2ListColoring.
//     // if coloring exists, we return it.
//     return false;

// }





