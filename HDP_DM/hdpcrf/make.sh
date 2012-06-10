#/bin/bash
gcc -o test -O3 -funroll-loops -fno-unit-at-a-time -funswitch-loops -ftree-loop-linear -ftree-loop-im -ftree-vectorize -fexpensive-optimizations hdp_c_decompclass.c -lm

