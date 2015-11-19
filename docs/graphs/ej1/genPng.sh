#!/bin/bash
for file in `ls *.dot`
do 
    dot -Tpng -o${file/.dot/}.png $file
done