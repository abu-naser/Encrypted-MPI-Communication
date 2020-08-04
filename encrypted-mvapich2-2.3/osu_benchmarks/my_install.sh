#!/bin/bash
./configure --prefix=/home/naser/cluster-2019/boringssl-mvapich/osu_benchmarks/install CC=/home/naser/cluster-2019/boringssl-mvapich/install/bin/mpicc CXX=/home/naser/cluster-2019/boringssl-mvapich/install/bin/mpicxx
make clean && make && make install