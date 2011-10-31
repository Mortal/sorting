#!/bin/sh
DIR=`dirname "$0"`
N=$((16*1024*1024*1024))
SEED=580763289
echo $DIR
echo STXXL
date
time $DIR/bench_external_sort-stxxl $N $SEED
echo filestream
date
time $DIR/bench_external_sort-filestream $N $SEED
echo memory
date
time $DIR/bench_external_sort-memory $N $SEED
echo END
date
