#!/bin/bash
#SBATCH -p normal
#SBATCH -t 2:00:00
#SBATCH -N 4
#SBATCH --ntasks-per-node 64

cd /home1/05137/gborcean/project;
FILES=$(pwd)/infiles;
for e in 1 2 4 8 16 32 64;  do
        for f in $FILES/*;  do



        echo $e 'NUMBER OF THREADS' $f 'FILENAME' $'\n'
        wc -c $f

        time_start=`date +%s%3N`
        #   OMP_NUM_THREADS=64 /usr/bin/time ./final $f
        OMP_NUM_THREADS=$e ./final $f
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
done

