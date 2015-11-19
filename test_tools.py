import os.path
from collections import defaultdict
import subprocess as s
from functools import partial


class TestRunner(object):
    """Base Model for tests"""
    def __init__(self, input, expected, family):
        super(TestRunner, self).__init__()
        self.input = input
        self.expected = expected
        self.family = family
        self.results = defaultdict(list)
        self.exercises = []
        self.runs = 25

    def execute(self):
        for n in xrange(5, 206):
            output = self.__run_instance(n)

            for key in output:
                self.results[key].append(output[key])
        return

    def __run_instance(self, size):
        expected = self.expected(size)
        input = self.input(size)
        family = self.family

        dic = {}

        input_filename = "tests/test_{family}_{size}_{expected}.in".format(
            family=family,
            size=size,
            expected=expected)

        if not os.path.exists("tests"):
            os.makedirs("tests")

        if not os.path.isfile(input_filename):
            with open(input_filename, "w") as t:
                t.write(input)

        for exercise in self.exercises:
            output_filename = "tests/test_{exercise}_{family}_{size}_{expected}.out".format(
                exercise=exercise,
                family=family,
                size=size,
                expected=expected)

            command = "./algo3_tp3 {exercise} {input_filename} {output_filename} {runs}".format(
                exercise=exercise,
                input_filename=input_filename,
                output_filename=output_filename,
                runs=self.runs)

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


class GreedyTest(TestRunner):
    """Test runner for greedy heuristics"""
    def __init__(self, input, expected, family):
        super(GreedyTest, self).__init__(input, expected, family)
        self.exercises = [3, 4, 5]
        self.runs = 25

    def __print_results(self):
        for exercise in self.exercises:
            print "------ Statistics for exercise {exercise}, {family}:".format(exercise=exercise, family=self.family)
            print "Valid Colorings: %d" % len(filter(lambda x: x['conflicts'] == 0, self.results[exercise]))
            print "Invalid Colorings: %d" % len(filter(lambda x: x['conflicts'] != 0, self.results[exercise]))
            print "Maximum Distance from Expected Number of Colors: %d\n" % max(map(lambda x: x['unique_colors'] - x['expected'], self.results[exercise]))

    def execute(self):
        super(GreedyTest, self).execute()
        self.__print_results()


class DecisionTest(object):
    """docstring for DecisionTest"""
    def __init__(self, input, expected, family):
        super(DecisionTest, self).__init__(input, expected, family)
        self.original_input = input

    def execute(self):
        for n in xrange(5, 206):
            for k in xrange(2, n):

                self.input = partial(self.original_input, top=k)
                output = self.__run_instance(n)

                for key in output:
                    self.results[key].append(output[key])
        return

    def __print_results(self):
        for exercise in self.exercises:
            print "------ Statistics for exercise {exercise}, {family}:".format(exercise=exercise, family=self.family)
            print "Valid Colorings: %d" % len(filter(lambda x: x['conflicts'] == 0, self.results[exercise]))
            print "Invalid Colorings: %d" % len(filter(lambda x: x['conflicts'] != 0, self.results[exercise]))
            print "Maximum Distance from Expected Number of Colors: %d\n" % max(map(lambda x: x['unique_colors'] - x['expected'], self.results[exercise]))

