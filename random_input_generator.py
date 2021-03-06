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
    colors = [list(set(prefix + [randint(0, c-1)
              for _ in xrange(randint(1, c-1))]))
              for _ in xrange(n)]

    for c in colors:
        shuffle(c)

    if top is not None:
        return map(lambda x: x[:top], colors)
    else:
        return colors


def random_input(n, m, c, top=None):
    if n is None:
        n = randint(10, 100)

    if m is None:
        m = randint(1, ((n-1)*n)/2)
    else:
        m = min(m, ((n-1)*n)/2)

    if c is None:
        raise ValueError("c no puede ser None")

    colors = get_colors(n, c, [], top)

    all_edges = list(combinations(xrange(n), 2))

    shuffle(all_edges)

    edges = "\n".join(["%d %d" % e for e in all_edges[:m]])

    return print_graph(header(n, m, c), edges, colors)


def complete_graph(n, m, c, top=None):
    if c < n:
        raise ValueError("minimo n colores diferentes")
    if c is None:
        raise ValueError("c no puede ser None")
    if m != (n*(n-1))/2:
        raise ValueError("m no compatible para grafo completo")

    colors = get_colors(n, c, range(n), top)

    all_edges = list(combinations(xrange(n), 2))

    edges = ["%d %d" % (u, v) for (u, v) in all_edges]
    edges = "\n".join(edges)

    return print_graph(header(n, m, c), edges, colors)


def star_graph(n, m, c, top=None):

    if c is None:
        raise ValueError("c no puede ser None")

    colors = get_colors(n, c, [0, 1], top)

    edges = ["%d %d" % (x, n-1) for x in xrange(n-1)]
    if m is None:
        m = len(edges)
    else:
        if m > len(edges):
            raise ValueError("m > maximo m posible")
        edges = edges[:m]

    edges = "\n".join(edges)

    return print_graph(header(n, m, c), edges, colors)


def complete_bipartite(n, m, c, top=None):

    if c is None:
        raise ValueError("c no puede ser None")

    colors = get_colors(n, c, [0, 1], top)

    A = [x for x in xrange(n) if x & 1]
    B = [x for x in xrange(n) if not(x & 1)]

    edges = ["%d %d" % (x, y) for x in A for y in B]
    if m is None:
        m = len(edges)
    else:
        if m > len(edges):
            raise ValueError("m > maximo m posible")
        edges = edges[:m]
    edges = "\n".join(edges)

    return print_graph(header(n, m, c), edges, colors)


def cycle_graph(n, m, c, top=None):
    lim = (2 + (n & 1))

    if c < lim:
        raise ValueError("no tiene solucion")
    colors = get_colors(n, c, [0, 1, 2][:lim], top)

    edges = ["%d %d" % (x, x+1) for x in xrange(n-1)] + ["%d %d" % (n-1, 0)]

    if m != len(edges):
        raise ValueError("m no existente para cycle correcto")

    edges = "\n".join(edges)

    return print_graph(header(n, m, c), edges, colors)


def wheel_graph(n, m, c, top=None):
    if n < 4:
        raise ValueError

    if c < 4:
        raise ValueError("c no coloreable")

    colors = get_colors(n, c, [0, 1, 2, 3], top)

    edges = ["%d %d" % (x, x+1) for x in xrange(n-2)] + \
            ["%d %d" % (n-2, 0)] + ["%d %d" % (n-1, x) for x in xrange(n-1)]

    if m != len(edges):
        raise ValueError("m no existente para wheel correcto")

    return print_graph(header(n, m, c), "\n".join(edges), colors)


def binary_balanced_tree(n, m, c, top=None):
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
        raise ValueError("c no puede ser None")

    colors = get_colors(n, c, [0, 1], top)

    edges = ["%d %d" % (min(e), max(e)) for e in _tree_edges(n)]

    if m is None:
        m = len(edges)
    else:
        if m > len(edges):
            raise ValueError("m > maximo m posible")
        edges = edges[:m]

    edges = "\n".join(edges)

    return print_graph(header(n, m, c), edges, colors)


def no_edges_graph(n):
    colors = get_colors(n, [])

    edges = ''

    m = 0

    return print_graph(header(n, m, n), edges, colors)
