#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "hdp_crf.c"


int main(int argc, char* argv[]) {
    int exclu,i,*res,all;
    double tt,haha,p=(double)1/(double)2;
    HDP_C *hdp;
    BASE_C *base;
    DP_C *dp;
    srand48(2);
    int class=2;
    all=0;
    tt=1;
    /*1. read in files*/
    int N=10000;
    gamln_0=malloc(sizeof(double)*(N+1));
    gamln_a=malloc(sizeof(double)*(N+1));
    gamln_g=malloc(sizeof(double)*(N+1));
    gamln_wl=malloc(sizeof(double)*(N+1));
    Readgamln(gamln_0,gamln_a,gamln_g,gamln_l,gamln_wl,N+1);
    hdp = Readtxt(1);

    /*haha= hdp_c_deleteres(hdp->base, hdp->dp, hdp->dp+68, 67, 1);*/
    /*haha=hdp_c_decompword(hdp->base, hdp->dp, 1, 0, 0);*/
    haha=hdp_c_decompclass(hdp->base, hdp->dp,10,0,0,1);/**/
    printf("wa: %f\n",haha);

    haha=    hdp_c_searchlambda(hdp->base);

    printf("wo: %f\n",haha);
    hdp_c_relabelclass(hdp->base,hdp->dp);/**/

    Writetxt(hdp,1);

    /*
        Writetxt(hdp,init);

    */
    free(gamln_0);
    free(gamln_a);
    free(gamln_g);
    free(gamln_wl);


    }

