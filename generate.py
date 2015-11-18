#!/usr/bin/python
import os
from collections import defaultdict
from random import randint, shuffle, random, randrange
from itertools import combinations

EX_DIR = "experiments/"
BEST = "best"
WORST = "worst"
RANDOM = "random"
EX_FILE_TEMPLATE = "test_%d_complejidad_%s.in"

def best_cast_2(top):
	