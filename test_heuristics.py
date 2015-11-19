#!/usr/bin/pypy
from random_input_generator import *
from test_tools import GreedyTest
from multiprocessing import Process


def test_complete():
    return GreedyTest(complete_graph,
                      lambda x: x,
                      "complete")


def test_star():
    return GreedyTest(star_graph,
                      lambda x: 2,
                      "star")


def test_bipartite():
    return GreedyTest(complete_bipartite,
                      lambda x: 2,
                      "bipartite")


def test_cycle():
    return GreedyTest(cycle_graph,
                      lambda x: 2 + (x & 1),
                      "cycle")


def test_wheel():
    return GreedyTest(wheel_graph,
                      lambda x: 4 - (x & 1),
                      "wheel")


def test_tree():
    return GreedyTest(binary_balanced_tree,
                      lambda x: 2 if x > 1 else 1,
                      "bbtree")


def test_random():
    return GreedyTest(random_input,
                      lambda x: x,
                      "random")

all_tests = [
            test_bipartite,
            test_cycle,
            test_tree,
            test_star,
            # test_wheel,
            # test_random,
            # test_complete,
            ]

if __name__ == '__main__':
    procs = [Process(target=t().execute) for t in all_tests]
    map(lambda p: p.start(), procs)
    map(lambda p: p.join(), procs)
