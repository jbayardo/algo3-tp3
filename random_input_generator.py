#!/usr/bin/python
from random import randint, shuffle
from itertools import combinations


def print_graph(head, edges, colors):
    color_out = []

    color_out = [" ".join(["%d" % len(vals)] + ["%d" % x for x in vals]) + "\n"
                 for vals in colors]

    return head + "".join(color_out) + edges


def header(n, m, c):
    return "%d %d %d\n" % (n, m, c)


def get_colors(n, c, prefix=[], top=None):
    if top is None:
        return [set(prefix + [randint(0, c-1)
                for _ in xrange(randint(1, c-1))])
                for _ in xrange(n)]
    else:
        return [set((prefix + [randint(0, c-1)
                for _ in xrange(randint(1, c-1))])[:top])
                for _ in xrange(n)]


def random_input(n=None, m=None, c=None, top=None):
    if n is None:
        n = randint(10, 100)

    if m is None:
        m = randint(1, ((n-1)*n)/2)
    else:
        m = min(m, ((n-1)*n)/2)

    if c is None:
        c = n

    colors = get_colors(n, c, [], top)

    all_edges = list(combinations(xrange(n), 2))

    shuffle(all_edges)

    edges = "\n".join(["%d %d" % e for e in all_edges[:m]])

    return print_graph(header(n, m, c), edges, colors)


def complete_graph(n, m=None, c=None, top=None):
    colors = [range(n) for _ in xrange(n)]

    all_edges = list(combinations(xrange(n), 2))

    edges = ["%d %d" % (u, v) for (u, v) in all_edges]
    m = len(edges)
    edges = "\n".join(edges)

    return print_graph(header(n, m, n), edges, colors)


def star_graph(n, m=None, c=None, top=None):
    if c is None:
        c = n

    colors = get_colors(n, c, [1, 2], top)

    edges = ["%d %d" % (x, n-1) for x in xrange(n-1)]
    if m is None:
        m = len(edges)
    else:
        edges = edges[:m]

    edges = "\n".join(edges)

    return print_graph(header(n, m, n), edges, colors)


def complete_bipartite(n, m=None, c=None, top=None):
    if c is None:
        c = n

    colors = get_colors(n, c, [1, 2], top)

    A = [x for x in xrange(n) if x & 1]
    B = [x for x in xrange(n) if not(x & 1)]

    edges = ["%d %d" % (x, y) for x in A for y in B]
    if m is None:
        m = len(edges)
    else:
        edges = edges[:m]
    edges = "\n".join(edges)

    return print_graph(header(n, m, n), edges, colors)


def cycle_graph(n, m=None, c=None, top=None):
    if c is None:
        c = n
    colors = get_colors(n, c, [1, 2, 3], top)

    edges = ["%d %d" % (x, x+1) for x in xrange(n-1)] + ["%d %d" % (n-1, 0)]
    if m is None:
        m = len(edges)
    else:
        edges = edges[:m]

    edges = "\n".join(edges)

    return print_graph(header(n, m, n), edges, colors)


def wheel_graph(n, m=None, c=None, top=None):
    n = max(n, 4)
    if c is None:
        c = n

    colors = get_colors(n, c, [1, 2, 3, 4], top)

    edges = ["%d %d" % (x, x+1) for x in xrange(n-2)] + \
            ["%d %d" % (n-2, 0)] + ["%d %d" % (n-1, x) for x in xrange(n-1)]
    if m is None:
        m = len(edges)
    else:
        edges = edges[:m]

    return print_graph(header(n, m, n), "\n".join(edges), colors)


def binary_balanced_tree(n, m=None, c=None, top=None):
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

    if c is None:
        c = n

    colors = get_colors(n, c, [1, 2], top)

    edges = ["%d %d" % (min(e), max(e)) for e in _tree_edges(n)]

    if m is None:
        m = len(edges)
    else:
        edges = edges[:m]

    edges = "\n".join(edges)

    return print_graph(header(n, m, n), edges, colors)


def no_edges_graph(n):
    colors = get_colors(n, [])

    edges = ''

    m = 0

    return print_graph(header(n, m, n), edges, colors)


if __name__ == '__main__':
    print random_input(150)
