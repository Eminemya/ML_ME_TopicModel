#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "hdp_crf.c"



int main(int argc, char* argv[]) {
    int class=0,all=0,word,*fullrow;
    double tt=1,haha[1];
    HDP_C *hdp;
    BASE_C *base=hdp->base;
    HH hh=base->hh;

    hdp = Readtxt();
    srand48(1);

    HDPOUT = mxDuplicateArray(HDPIN);
    mxWriteHDP_C(HDPOUT,hdp);
    free(fullrow);
    }
