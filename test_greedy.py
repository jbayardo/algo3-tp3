#!/usr/bin/python

from random_input_generator import *
import subprocess as s


def test_complete():
    test_template(complete_graph,
                  lambda x: x,
                  "Testing complete")


def test_star():
    test_template(star_graph,
                  lambda x: 2,
                  "Testing star")


def test_bipartite():
    test_template(complete_bipartite,
                  lambda x: 2,
                  "Testing bipartite")


def test_cycle():
    test_template(cycle_graph,
                  lambda x: 2 + x & 1,
                  "Testing cycle")


def test_wheel():
    test_template(wheel_graph,
                  lambda x: 4 - x & 1,
                  "Testing wheel")


def test_tree():
    test_template(binary_balanced_tree,
                  lambda x: 2 if x > 1 else 1,
                  "Testing tree")


def test_template(input, expected, msg):
    print msg
    results = []
    for n in xrange(1, 1001):
        if n % 250 == 0:
            print "%d" % (n/10) + "%"
        e = expected(n)
        results.append(run_test(input(n), e))
    print "Optimal cases: %d" % (filter(lambda x: x == 0, results))
    print "Not optimal: %d" % (filter(lambda x: x != 0, results))
    print "Max distance from optimum: %d" % max(results)


def run_test(input, expected):
    command = "algo3_tp3 3 test_greedy.in test_greedy.out 1"
    with open("test_greedy.in", "w") as t:
        t.write(input)
    output = s.check_output(command.split())
    colors = len(set(map(int, output.split())))
    return colors - expected


all_tests = [test_complete,
             test_star,
             test_bipartite,
             test_cycle,
             test_wheel,
             test_tree]

if __name__ == '__main__':
    for t in all_tests:
        t()
