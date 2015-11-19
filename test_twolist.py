#!/usr/bin/pypy
from random_input_generator import *
from test_tools import TwoListTest


def test_complete():
    return TwoListTest(complete_graph,
                      lambda x: x,
                      "complete")


def test_star():
    return TwoListTest(star_graph,
                      lambda x: 2,
                      "star")


def test_bipartite():
    return TwoListTest(complete_bipartite,
                      lambda x: 2,
                      "bipartite")


def test_cycle():
    return TwoListTest(cycle_graph,
                      lambda x: 2 + (x & 1),
                      "cycle")


def test_wheel():
    return TwoListTest(wheel_graph,
                      lambda x: 4 - (x & 1),
                      "wheel")


def test_tree():
    return TwoListTest(binary_balanced_tree,
                      lambda x: 2 if x > 1 else 1,
                      "bbtree")


def test_random():
    return TwoListTest(random_input,
                      lambda x: x,
                      "random")

all_tests = [test_random,
             test_complete,
             test_bipartite,
             test_cycle,
             test_wheel,
             test_tree,
             test_star]

if __name__ == '__main__':
    map(lambda t: t().execute(), all_tests)
