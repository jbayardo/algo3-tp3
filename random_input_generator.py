#!/usr/bin/python
from random import randint, shuffle, randrange
from itertools import combinations


def print_graph(head, edges, colors):
    color_out = []

    for _, vals in colors.iteritems():
        s_len = "%d " % len(vals)
        s_vals = " ".join(["%d" % x for x in vals])
        color_out.append(s_len + s_vals + "\n")

    return head + "".join(color_out) + edges


def header(n, m, c):
    return "%d %d %d\n" % (n, m, c)


def random_input(n=None):
    if n is None:
        n = randint(10, 100)
    m = randint(1, ((n-1)*n)/2)
    c = n

    colors = {k: set([randint(1, c-1) for _ in xrange(randint(1, c-1))]) for k in xrange(n)}

    all_edges = list(combinations(xrange(n), 2))

    shuffle(all_edges)

    edges = "\n".join(["%d %d"%(u, v) for (u, v) in all_edges[:m]])

    return print_graph(header(n, m, c), edges, colors)


def complete_graph(n):
    c = n

    colors = {k: range(n) for k in xrange(n)}

    all_edges = list(combinations(xrange(n), 2))

    edges = "\n".join(["%d %d"%(u, v) for (u, v) in all_edges])

    return print_graph(header(n, (n*(n-1)/2), c), edges, colors)


def star_graph(n):
    c = n
    colors = {k: set([1, 2] + [randint(1, c-1) for _ in xrange(randint(1, c-1))]) for k in xrange(n+1)}

    edges = "\n".join(["%d %d" % (x, n-1) for x in xrange(n-1)])

    return print_graph(header(n, n-1, c), edges, colors)


def complete_bipartite(n):
    c = n

    colors = {k: set([1, 2] + [randint(1, c-1) for _ in xrange(randint(1, c-1))]) for k in xrange(2*n)}

    A = [x for x in xrange(n) if x&1]
    B = [x for x in xrange(n) if not(x&1)]

    edges = "\n".join(["%d %d" % (x, y) for x in A for y in B])

    return print_graph(header(n, n*n, c), edges, colors)


def cycle_graph(n):
    c = n

    colors = {k: set([1, 2, 3] + [randint(1, c-1) for _ in xrange(randint(1, c-1))])
              for k in xrange(n)}

    edges = "\n".join(["%d %d" % (x, x+1) for x in xrange(n-1)] +
                      ["%d %d" % (n-1, 0)])

    return print_graph(header(n, n, c), edges, colors)


def wheel_graph(n):
    n = max(n, 4)
    c = n

    colors = {k: set([1, 2, 3] + [randint(1, c-1) for _ in xrange(randint(1, c-1))]) for k in xrange(n)}

    edges = "\n".join(["%d %d" % (x, x+1) for x in xrange(n-2)] +
                      ["%d %d" % (n-2, 0)] +
                      ["%d %d" % (n-1, x) for x in xrange(n-1)])

    return print_graph(header(n, 2*(n-1), c), edges, colors)


def binary_balanced_tree(n):
    def _tree_edges(n):
        # generador de arbol binario balanceado
        nodes = iter(range(n))
        parents = [next(nodes)]
        while parents:
            source = parents.pop(0)
            for i in range(2):
                try:
                    target = next(nodes)
                    parents.append(target)
                    yield source, target
                except StopIteration:
                    break

    c = n

    colors = {k: set([1, 2] + [randint(1, c-1) for _ in xrange(randint(1, c-1))]) for k in xrange(n)}

    edges = ["%d %d" % e for e in _tree_edges(n)]

    m = len(edges)

    edges = "\n".join(edges)

    return print_graph(header(n, m, c), edges, colors)

if __name__ == '__main__':
    print random_input()