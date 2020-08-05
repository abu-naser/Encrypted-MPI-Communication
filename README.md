
# An Empirical Study of Cryptographic Libraries for MPI Communications
In this work, we consider incorporating encryption to support
privacy and integrity in the Message Passing Interface (MPI)
library, which is widely used in HPC applications. We empirically
study four contemporary cryptographic libraries, [OpenSSL](https://www.openssl.org/),
[BoringSSL](https://boringssl.googlesource.com/boringssl/), [Libsodium](https://libsodium.gitbook.io/doc/), and [CryptoPP](https://www.cryptopp.com/) using [micro-benchmarks](http://mvapich.cse.ohio-state.edu/benchmarks/)
and [NAS parallel benchmarks](https://www.nas.nasa.gov/publications/npb.html) to evaluate their overheads for encrypting
 MPI messages on two different networking technologies,
10Gbps Ethernet and 40Gbps InfiniBand. The results indicate
that (1) the performance differs drastically across cryptographic
libraries, and (2) effectively supporting privacy and integrity
in MPI communications on high speed data center networks is
challenging—even with the most efficient cryptographic library,
encryption can still introduce very significant overheads in some
scenarios such as a single MPI communication operation on
InfiniBand, but (3) the overall overhead may not be prohibitive
for practical uses since there can be multiple concurrent communications.

We developed two MPI libraries whose communication is
encrypted via AES-GCM (for both 128-bit and 256-bit keys);
one library is based on MPICH-3.2.1 for Ethernet and the other
on MVAPICH2-2.3 for InfiniBand. Specifically, encryption is
added to the following MPI routines:
* Point-to-point: MPI_Send, MPI_Recv, MPI_ISend,
MPI_IRecv, MPI_Wait, and MPI_Waitall.
* Collective:
MPI_Allgather,
MPI_Alltoall,
MPI_Alltoallv, and MPI_Bcast.


The underlying cryptographic library is user-selectable among
OpenSSL, BoringSSL, Libsodium, and CryptoPP. With encryption incorporated at the MPI layer, our prototypes can
run on top of any underlying network. Implemented
secure routines are as follows: 

|  Init encryption key     | Pont-to-point routines|  Collective routines   |
| -------------            |:---------------------:| ----------------------:|
| init_crypto              | MPI_SEC_Send          | MPI_SEC_Allgather      |
|                          | MPI_SEC_Recv          | MPI_SEC_Alltoall       |
|                          | MPI_SEC_Isend         | MPI_SEC_Alltoallv      |
|                          | MPI_SEC_Irecv         | MPI_SEC_Bcast          |
|                          | MPI_SEC_Wait          |                        |
|                          | MPI_SEC_Waitall       |                        |

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

#### Encrypted-MVAPICH installation (Infiniband)
Steps:
Configure and install with BoringSSL:
```bash
cd encrypted-mvapich2-2.3
./autogen.sh
./configure --prefix=/MVAPICH_INSTALL_DIR/install  --with-enc-lib=libboringssl
```
In the *Makefile* add -L/YOUR_PATH_TO_MVAPICH/encrypted-mvapich2-2.3/boringssl-master/build/crypto -lcrypto in *LIBS*

(e.g. LIBS =-L/YOUR_PATH_TO_MVAPICH/encrypted-mvapich2-2.3/boringssl-master/build/crypto -lcrypto -libmad -lrdmacm -libumad -libverbs -ldl -lrt -lm -lpthread)

And also add -I/YOUR_PATH_TO_MVAPICH/encrypted-mvapich2-2.3/boringssl-master/include in *CFLAGS*

```bash
export LD_LIBRARY_PATH=/YOUR_PATH_TO_MVAPICH/encrypted-mvapich2-2.3/boringssl-master/build/crypto
make clean
make -j
make install
```

Configure and install with OpenSSL:
```bash
cd encrypted-mvapich2-2.3
./autogen.sh
./configure --prefix=/MVAPICH_INSTALL_DIR/install  --with-enc-lib=libopenssl
```
In the *Makefile* add -L/YOUR_PATH_TO_MVAPICH/encrypted-mvapich2-2.3/openssl-1.1.1/openssl_install/lib -lcrypto in *LIBS*

(e.g. LIBS =-L/YOUR_PATH_TO_MVAPICH/encrypted-mvapich2-2.3/openssl-1.1.1/openssl_install/lib -lcrypto -libmad -lrdmacm -libumad -libverbs -ldl -lrt -lm -lpthread)

And also add -I/YOUR_PATH_TO_MVAPICH/encrypted-mvapich2-2.3/openssl-1.1.1/openssl_install/include in *CFLAGS*

```bash
export LD_LIBRARY_PATH=/YOUR_PATH_TO_MVAPICH/encrypted-mvapich2-2.3/openssl-1.1.1/openssl_install/lib
make clean
make -j
make install
```

Configure and install with Libsodium:
```bash
cd encrypted-mvapich2-2.3
./autogen.sh
./configure --prefix=/MVAPICH_INSTALL_DIR/install  --with-enc-lib=libsodium
```
In the *Makefile* add -L/YOUR_PATH_TO_MVAPICH/encrypted-mvapich2-2.3/libsodium-stable/libsodium_install/lib -lsodium in *LIBS*

(e.g. LIBS =-L/YOUR_PATH_TO_MVAPICH/encrypted-mvapich2-2.3/libsodium-stable/libsodium_install/lib -lsodium -libmad -lrdmacm -libumad -libverbs -ldl -lrt -lm -lpthread)

And also add -I/YOUR_PATH_TO_MVAPICH/encrypted-mvapich2-2.3/libsodium-stable/libsodium_install/include in *CFLAGS*

```bash
export LD_LIBRARY_PATH=/YOUR_PATH_TO_MVAPICH/encrypted-mvapich2-2.3/libsodium-stable/libsodium_install/lib
make clean
make -j
make install
```

Configure and install with CryptoPP:
```bash
cd encrypted-mvapich2-2.3
./autogen.sh
./configure --prefix=/MVAPICH_INSTALL_DIR/install  --with-enc-lib=libcryptopp
```
In the *Makefile* add -L/YOUR_PATH_TO_MVAPICH/encrypted-mvapich2-2.3/cryptopp/install/lib -lcryptopp in *LIBS*

(e.g. LIBS =-L/YOUR_PATH_TO_MVAPICH/encrypted-mvapich2-2.3/cryptopp/install/lib -lcryptopp -libmad -lrdmacm -libumad -libverbs -ldl -lrt -lm -lpthread)

```bash
export LD_LIBRARY_PATH=/YOUR_PATH_TO_MVAPICH/encrypted-mvapich2-2.3/cryptopp/install/lib
make clean
make -j
make install
```



#### Encrypted-MPICH installation (Ethernet)

Steps:
Configure and install with BoringSSL:
```bash
tar xf encrypted-mpich-3.2.1.tar.xz
cd encrypted-mpich-3.2.1
./autogen.sh
./configure --prefix=/MPICH_INSTALL_DIR/install  --with-enc-lib=libboringssl
```
In the *Makefile* add -L/YOUR_PATH_TO_MPICH/encrypted-mpich-3.2.1/boringssl-master/build/crypto -lcrypto in *LIBS*

(e.g. LIBS =-L/YOUR_PATH_TO_MPICH/encrypted-mpich-3.2.1/boringssl-master/build/crypto -lcrypto -libmad -lrdmacm -libumad -libverbs -ldl -lrt -lm -lpthread)

And also add -I/YOUR_PATH_TO_MPICH/encrypted-mpich-3.2.1/boringssl-master/include in *CFLAGS*

```bash
export LD_LIBRARY_PATH=/YOUR_PATH_TO_MPICH/encrypted-mpich-3.2.1/boringssl-master/build/crypto
make clean
make -j
make install
```

Configure and install with OpenSSL:
```bash
tar xf encrypted-mpich-3.2.1.tar.xz
cd encrypted-mpich-3.2.1
./autogen.sh
./configure --prefix=/MPICH_INSTALL_DIR/install  --with-enc-lib=libopenssl
```
In the *Makefile* add -L/YOUR_PATH_TO_MPICH/encrypted-mpich-3.2.1/openssl-1.1.1/openssl_install/lib -lcrypto in *LIBS*

(e.g. LIBS =-L/YOUR_PATH_TO_MPICH/encrypted-mpich-3.2.1/openssl-1.1.1/openssl_install/lib -lcrypto -libmad -lrdmacm -libumad -libverbs -ldl -lrt -lm -lpthread)

And also add -I/YOUR_PATH_TO_MPICH/encrypted-mpich-3.2.1/openssl-1.1.1/openssl_install/include in *CFLAGS*

```bash
export LD_LIBRARY_PATH=/YOUR_PATH_TO_MPICH/encrypted-mpich-3.2.1/openssl-1.1.1/openssl_install/lib
make clean
make -j
make install
```

Configure and install with Libsodium:
```bash
tar xf encrypted-mpich-3.2.1.tar.xz
cd encrypted-mpich-3.2.1
./autogen.sh
./configure --prefix=/MPICH_INSTALL_DIR/install  --with-enc-lib=libsodium
```
In the *Makefile* add -L/YOUR_PATH_TO_MPICH/encrypted-mpich-3.2.1/libsodium-stable/libsodium_install/lib -lsodium in *LIBS*

(e.g. LIBS =-L/YOUR_PATH_TO_MPICH/encrypted-mpich-3.2.1/libsodium-stable/libsodium_install/lib -lsodium -libmad -lrdmacm -libumad -libverbs -ldl -lrt -lm -lpthread)

And also add -I/YOUR_PATH_TO_MPICH/encrypted-mpich-3.2.1/libsodium-stable/libsodium_install/include in *CFLAGS*

```bash
export LD_LIBRARY_PATH=/YOUR_PATH_TO_MPICH/encrypted-mpich-3.2.1/libsodium-stable/libsodium_install/lib
make clean
make -j
make install
```

Configure and install with CryptoPP:
```bash
tar xf encrypted-mpich-3.2.1.tar.xz
cd encrypted-mpich-3.2.1
./autogen.sh
./configure --prefix=/MPICH_INSTALL_DIR/install  --with-enc-lib=libcryptopp
```
In the *Makefile* add -L/YOUR_PATH_TO_MPICH/encrypted-mpich-3.2.1/cryptopp/install/lib -lcryptopp in *LIBS*

(e.g. LIBS =-L/YOUR_PATH_TO_MPICH/encrypted-mpich-3.2.1/cryptopp/install/lib -lcryptopp -libmad -lrdmacm -libumad -libverbs -ldl -lrt -lm -lpthread)

```bash
export LD_LIBRARY_PATH=/YOUR_PATH_TO_MPICH/encrypted-mpich-3.2.1/cryptopp/install/lib
make clean
make -j
make install
```


## Usage
To run MPI applications using CryptMPI please follow following steps for BoringSSL:
#### Encrypted-MVAPICH (Infiniband)
```bash
export LD_LIBRARY_PATH=/MVAPICH_INSTALL_DIR/install/lib:/YOUR_PATH_TO_MVAPICH/encrypted-mvapich2-2.3/boringssl-master/build/crypto

/MVAPICH_INSTALL_DIR/install/mpiexec -n 2 -f host ./pingpong
```

#### Encrypted-MPICH (Ethernet)
```bash
export LD_LIBRARY_PATH=/MPICH_INSTALL_DIR/install/lib:/YOUR_PATH_TO_MPICH/encrypted-mpich-3.2.1/boringssl-master/build/crypto
/MPICH_INSTALL_DIR/install/mpiexec -n 2 -f host ./pingpong
```


## Performance measurement
The performance was measured on 40Gb/s Infiniband and 10Gb/s Ethernet network. Benchmark program used:
- Ping-Pong program
- OSU micro-benchmark 5.4.4
- NAS parallel benchmarks 3.3.1 








