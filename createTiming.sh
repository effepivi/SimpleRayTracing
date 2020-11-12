#!/usr/bin/env bash

echo "CPU,Parallelisation,Number of threads per node,Number of nodes,Compiler,Image size,Runtime in sec" > timing.csv

cat timing-serial.csv >> timing.csv
cat timing-pthread-*.csv >> timing.csv
cat timing-omp-*.csv >> timing.csv
