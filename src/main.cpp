#include <iostream>
#include "Statistics.h"
#include "Problem.h"

/*
 * ./tp <ejercicio> <entrada> <salida> <corridas>
 */
int main(int argc, char *argv[]) {
    if (argc < 4) {
        std::cerr << "Formato de entrada: " << argv[0] << " <ejercicio> <entrada> <salida> <corridas>" << std::endl;
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

    std::ofstream handle;
    handle.open(output, std::ofstream::out);

    if (!handle.is_open()) {
        throw std::runtime_error("Fallo al abrir el archivo de salida");
    }

    handle << result;
    handle.close();

    std::string path = std::string(output);
    std::string basename = path.substr(0, path.find_last_of('.'));
    Statistics::getInstance().dump(basename + ".sts");

    return 0;
}