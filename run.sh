#!/bin/bash

FILES=$(pwd)/infiles

for f in  $FILES/*
do
    wc -c $f
    /usr/bin/time ./final $f
#    ./final $f
#   echo $(basename $f)
    wc -c $(pwd)/otest.bz2
    echo "bzip2"
    /usr/bin/time bzip2 $f
#    bzip2 $f
    wc -c $f.bz2
    bzip2 -d $f.bz2
    echo $'\n'
done
