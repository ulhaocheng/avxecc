# AVXECC

AVXECC is a throughput-optimized Elliptic Curve Cryptography (ECC) library that
exploits the parallel processing capabilities of Intel's Advanced Vector
eXtensions (AVX2). It can execute four instances of scalar multiplication in
parallel, whereby each instance uses a 64-bit element of a 256-bit AVX2 vector.
AVXECC supports variable-base scalar multiplication on Curve25519 and fixed-base
scalar multiplication on the twisted Edwards curve that is
birationally-equivalent to Curve25519. Each of the four instances can use a
different scalar and, in the case of variable-base scalar multiplication, also a
different base point. The implementation is resistant against timing attacks
since it does not execute any secret-dependent branches or loads. Further
details can be found in the paper linked below.

Supported cryptosystems and platforms: 
- X25519 (key-pair generation and shared-secret computation) using AVX2
- planned: Ed25519 (signature generation and verification) using AVX2
- planned: X25519 and Ed25519 using AVX512 and AVX512-IFMA


### Paper

A paper describing the "limb-slicing" technique upon which the implementation of
AVXECC is based was presented at the 27th International Workshop on Selected
Areas in Cryptography ([SAC 2020](https://sacworkshop.org/SAC20/index.html)). A
preliminary version of the paper is available
[here](https://sacworkshop.org/SAC20/files/preproceedings/27-HighThroughput.pdf).


### Building and Testing/Benchmarking

*Clang/GCC*

The source code contains a simple `makefile` for Clang. This `makefile` can be
easily modified for other compilers (e.g. GCC), but the performance may be
affected since AVXECC was specifically  "tuned" for Clang. The library can be
compiled and tested with the following commands.

```bash
    $ make
    $ ./test_bench
```

*Microsoft Visual Studio 2017*

The subdirectory `vs2017` contains the project/solution file `AVXECC.sln` for
Visual Studio 2017. After loading the project it will most likely be necessary
to adjust the Windows SDK version in the project settings (currently Windows SDK
version 10.0.17763.0 is used). To modify the SDK version go to Project - AVXECC
Properties (Alt F7) - Configuration Properties - General - Windows SDK Version.


### Software Authors

[Hao Cheng](https://haoche.ng), Johann Groszschaedl, and Jiaqi Tian (SnT and
DCS, University of Luxembourg). Copyright © 2020-2024 University of Luxembourg.


### License

GNU General Public License (GPL) version 3 (see LICENSE file for details). Other
licenses may be available on request, please contact Johann Groszschaedl
(firstname(dot)lastname(at)uni(dot)lu).
