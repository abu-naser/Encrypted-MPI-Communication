#!/bin/bash
MPICC="/home/gavahi/boringssl-mvapich/install-mvapich/bin/mpicc"
MPIEXEC="/home/gavahi/boringssl-mvapich/install-mvapich/bin/mpiexec" 
export LD_LIBRARY_PATH=/home/gavahi/boringssl-mvapich/install-mvapich/lib:/home/gavahi/boringssl-master/build/crypto
RED='\033[0;32m'
NC='\033[0m' # No Color
printf "\n${RED}#######################################################  New Test  ##############################################################################${NC}\n"
echo "Testing alltoallv...."
printf "\n"

cd examples/alltoallv-test-files
rm i-neg f-neg
$MPICC -o i-neg alltoallv-int-negative.c
$MPICC  -o f-neg  alltoallv-float-negative.c  
ls -lah

$MPIEXEC -n 4 ./i-neg 
$MPIEXEC -n 4 ./f-neg 

echo "Testing alltoallv done........"
echo "******************************************"
printf "\n"
echo "Testing alltoall...."
printf "\n"
cd ../all-to-all-test-files
rm i i-neg f-neg
$MPICC  -o i     all-to-all-int.c
$MPICC  -o i-neg all-to-all-int-negative.c
$MPICC  -o f-neg all-to-all-float-negative.c   
ls -lah
$MPIEXEC -n 4 ./i
$MPIEXEC -n 4 ./i-neg 
$MPIEXEC -n 4 ./f-neg 

echo "Testing alltoall done........"
echo "******************************************"
printf "\n"
echo "Testing allgather...."
printf "\n"
cd ../all-gather-test-files
rm i i-neg f-neg
$MPICC  -o i     all-gather-int.c
$MPICC  -o i-neg all-gather-int-negative.c
$MPICC  -o f-neg all-gather-float-negative.c   
ls -lah

$MPIEXEC -n 4 ./i
$MPIEXEC -n 4 ./i-neg 
$MPIEXEC -n 4 ./f-neg 

echo "\n\n"
echo "Testing allgather done........"
echo "******************************************"
printf "\n"
echo "Testing bcast...."
printf "\n"
cd ../bcast
rm  i-neg f-neg

$MPICC -o i-neg  bcast-int-negative.c
$MPICC -o f-neg bcast-float-negative.c 
ls -lah

$MPIEXEC -n 4 ./i-neg 
$MPIEXEC -n 4 ./f-neg 

echo "Testing bcast done........"