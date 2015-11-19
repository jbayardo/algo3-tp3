#!/usr/bin/python
from random_input_generator import random_input, no_edges_graph, complete_graph

####################################
############# Exercise 2 ############
####################################


def eval_nodes(n, m, c):
    for i in xrange(1, n+1):
        m = i/2
        print random_input(i, m, c)
        print ''


def eval_edges(n, m, c):
    for i in xrange(0, m):
        print random_input(n, i, c)
        print ''


def eval_colors(n, m, c):
    for i in xrange(1, c+1):
        print random_input(n, m, i)
        print ''


def best_case(n):
    for i in xrange(1, n+1):
        print no_edges_graph(i)


def worst_case(n):
    for i in xrange(1, n+1):
        print complete_graph(i)
        print ''

