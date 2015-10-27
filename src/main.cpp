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
    std::string input = argv[2];
    std::string output = argv[3];
    int runs;

    if (argc == 4) {
        runs = 1;
    } else {
        runs = std::atoi(argv[4]);
    }

    if (runs <= 0) {
        std::cerr << "Parametro de corridas inválido, debe ser mayor a 0." << std::endl;
        return 1;
    }

    Problem solver(input);

    switch (exercise) {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        default:
            std::cerr << "Parámetro de ejercicio inválido. Debe estar entre 1 y 4." << std::endl;
            return 1;
            break;
    }

    std::string path = std::string(output);
    std::string basename = path.substr(0, path.find_last_of('.'));
    Statistics::getInstance().dump(basename + ".sts");

    return 0;
}