import os.path
from collections import defaultdict
import subprocess as s
from functools import partial



class TestRunner(object):
    def __init__(self, input, expected, family, directory = "tests"):
        super(TestRunner, self).__init__()
        self.input = input
        self.expected = expected
        self.family = family
        self.results = defaultdict(list)
        self.exercises = []
        self.runs = 25
        self.directory = directory

    # def execute(self):
    #     raise "Instancias no configuradas. Chris es puto."
    #     return

    def run_instance(self, n, m, c, top = None):
        expected = self.expected(n)
        input = self.input(n, m, c, top)
        family = self.family

        dic = {}

        input_filename = "{directory}/test_{family}_{n}_{m}_{c}_{expected}.in".format(
            directory=self.directory,
            family=family,
            n=n,
            m=m,
            c=c,
            expected=expected)

        if not os.path.exists(self.directory):
            os.makedirs(self.directory)

        if not os.path.isfile(input_filename):
            with open(input_filename, "w") as t:
                t.write(input)

        for exercise in self.exercises:
            output_filename = "{directory}/test_{exercise}_{family}_{n}_{m}_{c}_{expected}.out".format(
                directory=self.directory,
                exercise=exercise,
                family=family,
                n=n,
                m=m,
                c=c,
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
                'n': n,
                # Aristas de la instancia
                'm': m,
                # Cantidad de colores total
                'c': c,
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

    def execute(self):
        for n in xrange(50, 1000, 50):
            a = (n-1)*(n-2)
            b = n*(n-1)
            for m in xrange(a/2 + 1, b/2):
                for c in xrange(2, n):
                    output = self.run_instance(n, m, c)

                    for key in output:
                        self.results[key].append(output[key])

        self.__print_results()

    def __print_results(self):
        for exercise in self.exercises:
            print "------ Statistics for exercise {exercise}, {family}:".format(exercise=exercise, family=self.family)
            print "Valid Colorings: %d" % len(filter(lambda x: x['conflicts'] == 0, self.results[exercise]))
            print "Invalid Colorings: %d" % len(filter(lambda x: x['conflicts'] != 0, self.results[exercise]))
            #print "Maximum Distance from Expected Number of Colors: %d\n" % max(map(lambda x: x['unique_colors'] - x['expected'], self.results[exercise]))


class TwoListTest(TestRunner):
    def __init__(self, input, expected, family):
        super(TwoListTest, self).__init__(input, expected, family, "two-list")
        self.exercises = [1]
        self.runs = 25

    def execute(self):
        for n in xrange(50, 1000, 50):
            for m in xrange((n-1)*(n-2)/2 + 1, n*(n-1)/2, 60):
                for c in xrange(n/2, n, 5):
                    output = super(TwoListTest, self).run_instance(n, m, c, 2)

                    for key in output:
                        self.results[key].append(output[key])

        self.__print_results()

    def __print_results(self):
        for exercise in self.exercises:
            for result in self.results[exercise]:
                if result['conflicts'] != 0:
                    print "Error occurred. Relevant information: ", result


class BacktrackingTest(TestRunner):
    def __init__(self, input, expected, family):
        super(BacktrackingTest, self).__init__(input, expected, family, "backtracking")
        self.exercises = [2]
        self.runs = 25

    def execute(self):
        for n in xrange(5, 12):
            for m in xrange((n-1)*(n-2)/2 + 1, n*(n-1)/2, 1):
                for c in xrange(n/2, n):
                    output = super(BacktrackingTest, self).run_instance(n, m, c)

                    for key in output:
                        self.results[key].append(output[key])

    def __print_results(self):
        for exercise in self.exercises:
            for result in self.results[exercise]:
                if result['conflicts'] != 0:
                    print "Error occurred. Relevant information: ", result

