#include <iostream>
#include "Statistics.h"
#include "Problem.h"
#include "ConflictColoring.h"

/*
 * ./tp <ejercicio> <entrada> <salida> [corridas=1]
 */
int main(int argc, char *argv[]) {
    if (argc < 4) {
        std::cerr << "Formato de entrada: " << argv[0] << " <ejercicio> <entrada> <salida> <corridas>" << std::endl;
#ifdef DEBUG
        std::cerr << "BUILD DE DEBUG" << std::endl;
#endif

#ifdef EXPS
        std::cerr << "BUILD DE EXPERIMENTACION" << std::endl;
#endif
        return 1;
    }

    int exercise = std::atoi(argv[1]);
    std::string input(argv[2]);
    std::string output(argv[3]);
    int runs;

    if (argc == 4) {
        runs = 1;
    } else {
        runs = std::atoi(argv[4]);
    }

    Problem solver(input);
    Coloring result(solver.solve(exercise, runs));

#if defined(DEBUG) || defined(EXPS)
    ConflictColoring conflicts(result);

    std::cout << conflicts;
#endif

    std::ofstream handle;
    handle.open(output, std::ofstream::out);

    if (!handle.is_open()) {
        throw std::runtime_error("Fallo al abrir el archivo de salida");
    }

#if defined(DEBUG) || defined(EXPS)
    handle << conflicts;
#else
    handle << result;
#endif

    handle.close();

    std::string path = std::string(output);
    std::string basename = path.substr(0, path.find_last_of('.'));
    Statistics::getInstance().dump(basename + std::string(".sts"));

    return 0;
}