#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "hdp_crf.c"

int main(int argc, char* argv[]) {
    int exclu,i,*res,all;
    double tt,haha,*ress;
    HDP_C *hdp;

    hdp = Readtxt();
    srand48(1);
    int num=200;
    res   =malloc(sizeof(int)*(num+1));
    res[0]=num;
    for(i=1; i<num+1; i++) {
        res[i]=i-1;
        }
    exclu=0;
    all=0;
    tt=0.2;
    haha=hdp_c_decompres(hdp->base,&hdp->dp[0],tt,exclu-1,res,all);/**/
    hdp_c_relabelclass(hdp->base,hdp->dp);
    free(res);
    Writetxt(hdp);

    }










