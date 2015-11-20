#!/usr/bin/pypy
import sys

def copy_filtered_headers(filename):
    with open(filename) as source:
        with open("copy_"+filename, "w") as destiny:
            header = source.readline()
            destiny.write(header)
            for line_s in source:
                if line_s == header:
                    continue
                else:
                    destiny.write(line_s)
    print "copy_"+filename


if __name__ == '__main__':
    if len(sys.argv) < 2:
        print "filter_header.py archivo.csv"
    copy_filtered_headers(sys.argv[1])