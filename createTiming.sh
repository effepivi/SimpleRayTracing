#!/usr/bin/env bash

echo "CPU,Parallelisation,Number of threads/processes per node,Number of nodes,Compiler,Image size,Runtime in sec" > timing.csv

tail -n 1 timing-serial.csv >> timing.csv 2>/dev/null

for file in `ls timing-pthread-*.csv timing-omp-*.csv timing-mpi-*-*.csv 2>/dev/null`
do
    grep "Warning: can't honor --ntasks-per-node set to" $file >/dev/null 2>/dev/null
    if [ $? -eq 1 ]
    then
        grep "2.40GHz" $file >/dev/null 2>/dev/null
        if [ $? -eq 0 ]
        then        
            tail -n 1 $file >> timing.csv
        fi
    fi
done

