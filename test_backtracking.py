#!/usr/bin/pypy
from random_input_generator import *
from test_tools import BacktrackingTest


def test_complete():
    return BacktrackingTest(complete_graph,
                      lambda x: x,
                      "complete")


def test_star():
    return BacktrackingTest(star_graph,
                      lambda x: 2,
                      "star")


def test_bipartite():
    return BacktrackingTest(complete_bipartite,
                      lambda x: 2,
                      "bipartite")


def test_cycle():
    return BacktrackingTest(cycle_graph,
                      lambda x: 2 + (x & 1),
                      "cycle")


def test_wheel():
    return BacktrackingTest(wheel_graph,
                      lambda x: 4 - (x & 1),
                      "wheel")


def test_tree():
    return BacktrackingTest(binary_balanced_tree,
                      lambda x: 2 if x > 1 else 1,
                      "bbtree")


def test_random():
    return BacktrackingTest(random_input,
                      lambda x: x,
                      "random")

all_tests = [test_bipartite,
             test_cycle,
             test_wheel,
             test_tree,
             test_star]

if __name__ == '__main__':
    map(lambda t: t().execute(), all_tests)
