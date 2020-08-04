#!/bin/bash
make clean
make libcryptopp.a libcryptopp.so cryptest.exe -j 7
make install PREFIX=/home/gavahi/cryptopp/install -j 7
