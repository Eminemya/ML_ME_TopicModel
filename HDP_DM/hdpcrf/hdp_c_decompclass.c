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
    /*gamln_l=malloc(sizeof(double)*(N+1));*/
    gamln_wl=malloc(sizeof(double)*(N+1));
    Readgamln(gamln_0,gamln_a,gamln_g,gamln_l,gamln_wl,N+1);
    int init=(int)atoi(argv[1]);
    int itttt=(int)atoi(argv[2]);
    hdp = Readtxt(init);
    OLink *classqq;
    int numcl,lastcl,iter;
    double *chooser,avg;

    int cc,*order=malloc(sizeof(int)*1000);
    //2. Decompose Dish:
    for(iter=0; iter<itttt; iter++) {
      
        //2.1 Refine Dish:      
        lastcl=hdp->base->lastcl;
        randperm(lastcl+1,order);
        for(cc=0; cc<=lastcl; cc++) {
            class=order[cc];
            classqq=hdp->base->classqq;
            if(classqq[class]!=NULL&&classqq[class]->val>0) {
                haha=hdp_c_decompclass(hdp->base, hdp->dp,tt,class,0,0);
                printf("RF dish %d,%f,%d\n",class,haha,hdp->base->numclass);
                //break;
                if(classqq[class]!=NULL&&classqq[class]->val>0) {
                    haha=hdp_c_mergeclass(hdp, tt,class);
                    printf("mm:%d,%f\n",class+1,haha);
                    }
                }
            }
        hdp_c_relabelclass(hdp->base,hdp->dp);
        
        //haha=   hdp_c_searchlambda(hdp->base); 
        //printf("UPDAE lambda1 %d,%f\n",iter,haha);

      /*
        */

        /*2.2 Remove Dish:
          */
        lastcl=hdp->base->lastcl;
        chooser=malloc(sizeof(double)*(lastcl+1));
        numcl=hdp->base->numclass;
        avg=0;
        for(class=0; class<=lastcl; class++) {
            classqq=hdp->base->classqq;
            if(classqq[class]!=NULL&&classqq[class]->val>0) {
                chooser[class]=hdp->base->cclik[class]/classqq[class]->val;
                avg+=chooser[class];
                }
            }
        avg/=numcl;
        printf("avg:%f\n",avg);
        randperm(lastcl+1,order);
        for(cc=0; cc<=lastcl; cc++) {
            class=order[cc];
            classqq=hdp->base->classqq;
            if(classqq[class]!=NULL&&classqq[class]->val>0&&chooser[class]<avg) {
                haha=hdp_c_decompclass(hdp->base, hdp->dp, tt,class,1,init);
                printf("RM dish %d,%f,%d\n",class,haha,hdp->base->numclass);
                hdp_c_relabelclass(hdp->base,hdp->dp);
                }
            }
        //haha=   hdp_c_searchlambda(hdp->base); 
        //printf("UPDAE lambda2 %d,%f\n",iter,haha);
        free(chooser);
        }
    free(order);
    free(gamln_0);
    free(gamln_a);
    free(gamln_g);
    /*free(gamln_l);*/
    free(gamln_wl);

    Writetxt(hdp,init);
    }

/*haha=hdp_c_decompclass(hdp->base, hdp->dp,pow(((double)(iter)/(double)(5)),p),class,0);*/
/*
    int *ress=malloc(sizeof(int)*2);
    ress[0]=1;
    OLink *ct;
    for(iter=1; iter<2; iter++) {
    lastcl=hdp->base->lastcl;
    lastcl=hdp->numdp-1;
    for(class=1; class<=lastcl; class++) {
    ress[1]=class;
         dp=hdp->dp+class;
         ct=hdp->base->ctindex;
         haha             = hdp_c_lmres(hdp->base, hdp->dp, dp, 0.3, class,-1,1);
          if(haha < HDP_EPSILON) {
                hdp_c_oldval(hdp->base, hdp->dp,ress);
                }
            else {
                hdp_c_newval(hdp->base, hdp->dp,ress);
                }
        printf("clean: %d,%f,%d\n",class,haha,hdp->base->numclass);
        }
}
free(ress);
*/
/*  int cltindex[2]={1,4};
    haha                = hdp_c_decompres(hdp->base, hdp->dp, 1,0, cltindex, 0);
*/
