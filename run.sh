#!/bin/bash

FILES=$(pwd)/infiles

for f in  $FILES/*
do  
    wc -c $f
    ./final $f
#    echo $(basename $f)  
    wc -c $(pwd)/otest.bz2
    bzip2 $f
    wc -c $f.bz2    
    bzip2 -d $f.bz2
done
