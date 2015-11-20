#!/home/julian/Software/anaconda/bin/python
import os
import re
import pandas as pd
# Este script larga output.csv, con el formato que buscamos para que lo tome
# el software para graficar, Tableau.

directories = ['backtracking_podas', 'backtracking_sin_podas', 'test_heuristics', 'two_list_tests']

# Obtenemos archivos a mirar
files = []

for directory in directories:
    files += map(lambda x: directory+'/'+x, os.listdir(directory))

# Pasamos por todos los archivos y armamos el dataset
dataset = []

for fname in files:
    if fname[-3:] != 'sts':
        continue

    matches = re.match(r"^(.*)\/test_([1-5]+)_(.*)_([0-9]+)_([0-9]+)_([0-9]+)_([0-9]+)?\.sts$", fname)

    batch = matches.group(1).strip()
    method = int(matches.group(2).strip())
    family = matches.group(3).strip()
    n = int(matches.group(4).strip())
    m = int(matches.group(5).strip())
    c = int(matches.group(6).strip())
    expected = int(matches.group(7).strip())

    # Read output file for the test, this has information about conflicts
    with open(fname[:-3]+'out', 'r') as handle:
        output = handle.read()

    output = map(str.split, map(str.strip, output.strip().split('\n')))

    # Data coming from output
    try:
        colors = map(int, output[0])
    except:
        print "Error in file", fname
        continue

    unique_colors = set(colors)
    conflicts = int(output[1][0])
    specific = map(int, output[2])

    # Read statistics for the test
    with open(fname, 'r') as handle:
        statistics = handle.read()

    statistics = statistics.strip().split('\n')

    for line in statistics:
        if line.strip() == '':
            continue

        line = line.strip().split('\t\t\t')
        line[1] = map(int, line[1].strip().split(','))
        line[1] = sorted(line[1])

        # Poda de 10%
        line[1] = line[1][5:-5]

        for run, measure in enumerate(line[1]):
            output = {
                'batch': batch,
                'family': family,
                'method': method,
                'n': n,
                'm': m,
                'c': c,
                'expected': expected,
                'run': run + 1,
                'timer': line[0],
                'value': int(measure),
                'conflicts': conflicts,
                'unique_colors': len(unique_colors)
            }

            dataset.append(output)

df = pd.DataFrame(dataset)
df.to_csv('output.csv', index=False)

