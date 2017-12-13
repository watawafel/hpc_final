#!/bin/bash

FILES=$(pwd)/infiles

for f in  $FILES/*
do
    wc -c $f

    time_start=`date +%s%3N`
#   OMP_NUM_THREADS=64 /usr/bin/time ./final $f
    OMP_NUM_THREADS=32 ./final $f
    time_end=`date +%s%3N`
    
    echo 'milliseconds time:' $(expr $time_end - $time_start)
    wc -c $(pwd)/otest.bz2

    echo "bzip2 now..."
    time_start=`date +%s%3N`
#   /usr/bin/time bzip2 $f
    bzip2 $f
    time_end=`date +%s%3N`
    
    echo 'milliseconds time:' $(expr $time_end - $time_start)
    wc -c $f.bz2
    
    bzip2 -d $f.bz2
    echo $'\n'
done
