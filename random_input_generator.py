#!/usr/bin/python
import os
from random import randint, shuffle, randrange
from itertools import combinations


def random_input():
    n = randint(1, 100)
    m = randint(1, ((n-1)*n)/2)
    c = n

    colors = {k: set([randint(1, c) for _ in xrange(randint(1, c))]) for k in xrange(n)}

    all_edges = list(combinations(xrange(n), 2))

    shuffle(all_edges)

    edges = "\n".join(["%d %d"%(u, v) for (u, v) in all_edges[:m]])

    header = "%d %d %d\n" % (n, m, c)
    color_out = []

    for c, vals in colors.iteritems():
        s_len = "%d " % len(vals)
        s_vals = " ".join(["%d" % x for x in vals])
        color_out.append(s_len + s_vals)

    print header + "\n".join(color_out) + edges

if __name__ == '__main__':
    random_input()