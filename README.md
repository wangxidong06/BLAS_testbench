# BLAS-testbench
A testbench of Basic Linear Algebra Subprograms.

## Construction
- HPL(The High Performance Linpack)
  - HPL.dat: the config file of HPL
  - Make.test: the makefile config to compile HPL  
- single_operator_test
  - Level-1.c: the level-1 testbench of BLAS
  - Level-2.c: the level-2 testbench of BLAS
  - Level-3.c: the level-3 testbench of BLAS

## How to use
- HPL
  1. Download and compile: Openmpi, gcc, gfortran
  
  2. Download and compile HPL
  
       - move make.test to HPL files
  
       - specify the path of make.test  ((your optimized OpenBLAS / OpenMPI / HPL path) in make.test
  
       - bash: 
  
         ```bash
         make arch=test
         ```
  
       - cd HPL/test/bin: config the HPL.dat and run 
  
         ```bash
         mpirun -allow-run-as-root  -np 4 ./xhpl > result.txt 
         ```
  
- Single_operator_test
  1. Specify the dynamic link path of cblas.h (your optimized OpenBLAS) in every C code.
  
     ```C++
     #include "/root/openblas/pre_openblas/include/cblas.h"
     ```
  
  2. run the code
