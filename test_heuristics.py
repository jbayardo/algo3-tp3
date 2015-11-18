#!/usr/bin/pypy

from random_input_generator import *
import subprocess as s
from multiprocessing import Process
from collections import defaultdict
import random
import os.path


def test_complete():
    test_template(complete_graph,
                  lambda x: x,
                  "complete")


def test_star():
    test_template(star_graph,
                  lambda x: 2,
                  "star")


def test_bipartite():
    test_template(complete_bipartite,
                  lambda x: 2,
                  "bipartite")


def test_cycle():
    test_template(cycle_graph,
                  lambda x: 2 + (x & 1),
                  "cycle")


def test_wheel():
    test_template(wheel_graph,
                  lambda x: 4 - (x & 1),
                  "wheel")


def test_tree():
    test_template(binary_balanced_tree,
                  lambda x: 2 if x > 1 else 1,
                  "bbtree")


def test_random():
    test_template(random_input,
                  lambda x: x,
                  "random")


exercises = [3, 4, 5]
runs = 25


def test_template(input, expected, family):
    results = defaultdict(list)

    for n in xrange(5, 206):
        output = run_test(family, n, input(n), expected(n))

        for key in output:
            results[key].append(output[key])

    for exercise in exercises:
        print "------ Statistics for exercise {exercise}, {family}:".format(exercise=exercise, family=family)
        print "Valid Colorings: %d" % len(filter(lambda x: x['conflicts'] == 0, results[exercise]))
        print "Invalid Colorings: %d" % len(filter(lambda x: x['conflicts'] != 0, results[exercise]))
        print "Maximum Distance from Expected Number of Colors: %d\n" % max(map(lambda x: x['unique_colors'] - x['expected'], results[exercise]))


def run_test(family, size, input, expected):
    dic = {}

    input_filename = "tests/test_{family}_{size}_{expected}.in".format(
        family=family,
        size=size,
        expected=expected)

    if not os.path.isfile(input_filename):
        with open(input_filename, "w") as t:
            t.write(input)

    for exercise in exercises:
        output_filename = "tests/test_{exercise}_{family}_{size}_{expected}.out".format(
            exercise=exercise,
            family=family,
            size=size,
            expected=expected)

        command = "./algo3_tp3 {exercise} {input_filename} {output_filename} {runs}".format(
            exercise=exercise,
            input_filename=input_filename,
            output_filename=output_filename,
            runs=runs)

        output = map(str.strip, s.check_output(command.split()).strip().split('\n'))
        # output[0] son los colores
        # output[1] son los conflictos totales
        # output[2] son los conflictos en casos particulares

        dic[exercise] = {
            # Tamano de la instancia
            'size': size,
            # X(G) para el grafo
            'expected': expected,
            # Colores utilizados
            'colors': map(int, output[0].split()),
            # Cantidad de conflictos
            'conflicts': int(output[1]),
            # Cantidad de conflictos por nodo
            'specific': map(int, output[2].split())
        }

        # Cantidad de colores unicos utilizados
        dic[exercise]['unique_colors'] = len(set(dic[exercise]['colors']))

    return dic

all_tests = [test_tree,
             test_star,
             test_bipartite,
             test_cycle,
             test_wheel,
             test_random,
             test_complete]

if __name__ == '__main__':
    map(lambda t: t(), all_tests)
