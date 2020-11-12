#!/usr/bin/env bash

echo "CPU,Parallelisation,Number of threads per node,Number of nodes,Compiler,Image size,Runtime in sec" > timing.csv

cat timing-serial.csv >> timing.csv 2>/dev/null
cat timing-pthread-*.csv >> timing.csv 2>/dev/null
cat timing-omp-*.csv >> timing.csv 2>/dev/null
