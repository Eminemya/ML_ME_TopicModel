#ifndef _BASE_CRF
#define _BASE_CRF

#include "util_crf.c"
#include "sparse.c"
typedef struct {
    HH *hh;
    int numclass, maxclass,lastcl,numdp,maxta,numword;    
    double *cclik,noiselevel;
    OLink *classqq;
    OLink *wordqq;
    OLink *ctindex;
    /*backup*/
    int o_numclass, o_lastcl,o_maxta;
    double *o_cclik,avg_h;
    } BASE_C;

void CopyBase_C(BASE_C *new_base,BASE_C *old_base) {
    int ii,maxclass,numclass,numword=old_base->numword;
    /*  BASE_C *new_base;*/

    new_base->numclass =  numclass  = old_base->numclass;
    new_base->maxclass = maxclass  = old_base->maxclass;

    new_base->hh       =  malloc(sizeof(HH)*maxclass);
    for (ii=0; ii<maxclass; ii++) {
        new_base->hh[ii].eta=malloc(sizeof(double)*(numword+1));
        memcpy(new_base->hh[ii].eta, old_base->hh[ii].eta,sizeof(double)*(numword+1));
        }

    new_base->numdp    = old_base->numdp;
    new_base->numword  = numword;
    new_base->avg_h    = old_base->avg_h;
    new_base->noiselevel    = old_base->noiselevel;
    new_base->lastcl   = old_base->lastcl;
    new_base->cclik    = malloc(sizeof(double)*maxclass);
    new_base->o_numclass = old_base->o_numclass;
    new_base->o_lastcl   = old_base->o_lastcl;
    new_base->o_cclik    = malloc(sizeof(double)*maxclass);
    new_base->maxta     = old_base->maxta;
    new_base->o_maxta     = old_base->o_maxta;
    new_base->classqq = malloc(sizeof(OLNode)*maxclass);
    new_base->ctindex = malloc(sizeof(OLNode)*maxclass);
    CopyOLink(new_base->classqq,old_base->classqq,maxclass);
    CopyOLink(new_base->ctindex,old_base->ctindex,maxclass);
    new_base->wordqq=RightConnect(new_base->classqq,numword,old_base->lastcl+1);
    memcpy(new_base->cclik, old_base->cclik,sizeof(double)*maxclass);
    memcpy(new_base->o_cclik, old_base->o_cclik,sizeof(double)*maxclass);
    }

void DeleteBase_C(BASE_C *new_base,int option) {
    int ii;
    for (ii=0; ii<new_base->maxclass; ii++) {
        free(new_base->hh[ii].eta);
        }
    free(new_base->hh);


    free(new_base->cclik);
    free(new_base->o_cclik);
    if(option==0) {
        /*not for write output*/
        DelCrossList(new_base->classqq,new_base->wordqq,new_base->numword,new_base->maxclass,2);
        DelCrossList(new_base->ctindex,new_base->ctindex,new_base->numdp-1,new_base->maxclass,0);
        }
    }

#endif
