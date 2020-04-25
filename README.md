
# An Empirical Study of Cryptographic Libraries for MPI Communications
In this work, we consider incorporating encryption to support
privacy and integrity in the Message Passing Interface (MPI)
library, which is widely used in HPC applications. We empirically
study contemporary cryptographic libraries using micro-benchmarks
and NAS parallel benchmarks to evaluate their overheads for en-
crypting MPI messages on two different networking technologies,
10Gbps Ethernet and 40Gbps InfiniBand.

We developed two MPI libraries whose communication is
encrypted via AES-GCM (for both 128-bit and 256-bit keys);
one library is based on MPICH-3.2.1 for Ethernet and the other
on MVAPICH2-2.3 for InfiniBand. Specifically, encryption is
added to the following MPI routines:
• Point-to-point: MPI_Send, MPI_Recv, MPI_ISend,
MPI_IRecv, MPI_Wait, and MPI_Waitall.
• Collective:
MPI_Allgather,
MPI_Alltoall,
MPI_Alltoallv, and MPI_Bcast.
The underlying cryptographic library is user-selectable among
OpenSSL, BoringSSL, Libsodium, and CryptoPP. With en-
cryption incorporated at the MPI layer, our prototypes can
run on top of any underlying network. As our main focus of
this work is to benchmark the performance of encrypted MPI
libraries

## Related Paper
[IEEE Cluster 2019, Albuquerque, USA](https://ieeexplore.ieee.org/abstract/document/8891033)

## Installation
To install cryptMPI for the Infiniband and Ethernet network please follow following steps:
#### Package requirement
 autoconf version... >= 2.67
 automake version... >= 1.15
 libtool version... >= 2.4.4

To install the above package you could use get-lib.sh

After installing, set the path for the above packages.

```bash
export PATH=/HOME_DIR/automake/bin:$PATH
export LD_LIBRARY_PATH=/HOME_DIR/automake/lib:$LD_LIBRARY_PATH
```

#### CryptMPI-MVAPICH installation (Infiniband)
Steps:
```bash
tar -xvzf cryptMPI-mvapich2-2.3.2.tar.gz
cd mvapich2-2.3.2
./autogen.sh
./configure --prefix=/MVAPICH_INSTALL_DIR/install  --with-boringssl-include="/YOUR_PATH_TO_MVAPICH/mvapich2-2.3.2/boringssl-master/include/ -fopenmp"
```
In the *Makefile* add -L/YOUR_PATH_TO_MVAPICH/mvapich2-2.3.2/boringssl-master/build/crypto -lcrypto in *LIBS*

(e.g. LIBS =-L/YOUR_PATH_TO_MVAPICH/mvapich2-2.3.2/boringssl-master/build/crypto -lcrypto -libmad -lrdmacm -libumad -libverbs -ldl -lrt -lm -lpthread)

```bash
export LD_LIBRARY_PATH=/YOUR_PATH_TO_MVAPICH/mvapich2-2.3.2/boringssl-master/build/crypto
make clean
make -j
make install
```

#### CryptMPI-MPICH installation (Ethernet)
Steps: 
```bash
tar -xvzf cryptMPI-mpich-3.2.1.tar.gz
cd mpich-3.2.1
./autogen.sh
./configure --prefix=/MPICH_INSTALL_DIR/install  --with-boringssl-include="/YOUR_PATH_TO_MPICH/mpich-3.2.1/boringssl-master/include/ -fopenmp"
```
In the *Makefile* add -L/YOUR_PATH_TO_MPICH/mpich-3.2.1/boringssl-master/build/crypto -lcrypto in *LIBS*

(e.g. LIBS = -L/YOUR_PATH_TO_MPICH/mpich-3.2.1/boringssl-master/build/crypto -lcrypto -lpthread )

And also add *-fopenmp* in *LDFLAGS* (e.g. LDFLAGS = -fopenmp)
 
```bash
export LD_LIBRARY_PATH=/YOUR_PATH_TO_MPICH/mpich-3.2.1/boringssl-master/build/crypto
make clean
make -j
make install
```


## Usage
To run MPI applications using CryptMPI please follow following steps:
#### CryptMPI-MVAPICH (Infiniband)
```bash
export LD_LIBRARY_PATH=/MVAPICH_INSTALL_DIR/install/lib:/YOUR_PATH_TO_MVAPICH/mvapich2-2.3.2/boringssl-master/build/crypto
export MV2_ENABLE_AFFINITY=1
export MV2_CPU_BINDING_POLICY=hybrid
export MV2_HYBRID_BINDING_POLICY=spread 
/MVAPICH_INSTALL_DIR/install/mpiexec -n 2 -f host ./pingpong
/MVAPICH_INSTALL_DIR/install/mpiexec -n 64 -f host ./stencil 8 8 128 128 2 1000 0
```

#### CryptMPI-MPICH (Ethernet)
```bash
export LD_LIBRARY_PATH=/MPICH_INSTALL_DIR/install/lib:/YOUR_PATH_TO_MPICH/mpich-3.2.1/boringssl-master/build/crypto
/MPICH_INSTALL_DIR/install/mpiexec -n 2 -f host ./pingpong
/MPICH_INSTALL_DIR/install/mpiexec -n 64 -f host ./stencil 8 8 128 128 2 1000 0
```


## Performance measurement
The performance was measured on 100Gb/s Infiniband and 10Gb/s Ethernet network. Benchmark program used:
- Ping-Pong program
- OSU micro-benchmark 5.6.2
- NAS parallel benchmarks 3.3.1 
- 2D-Stencil







