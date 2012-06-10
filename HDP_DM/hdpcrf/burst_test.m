%load burstbar
load bursty_10


% we tried mex but got out of memory issue. Thus, we wrote the main algo purely in c and matlab as convinient data conversion


%raw data-> matlab hdp structure
hdp=c_dat2crf(datass,50,4);

% matlab hdp-> text hdp as input for c code
mat2txt

% in the terminal
% gcc -o burst_0 -O3 -funroll-loops -fno-unit-at-a-time -funswitch-loops -ftree-loop-linear -ftree-loop-im -ftree-vectorize -fexpensive-optimizations hdp_c_decompclass.c -lm
% ./burst_0 1 5

