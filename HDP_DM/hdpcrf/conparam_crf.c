#ifndef _CONPARAM_CRF
#define _CONPARAM_CRF

typedef struct {
    double alpha, alphaa, alphab;
    int numdp, *totalnd, *totalnt;
    } CONPARAM;


void CopyConparamVector(CONPARAM *result,CONPARAM *mstruct,int nn) {
    CONPARAM *cp;
    int ii;
    for ( ii = 0 ; ii < nn ; ii++ ) {
        cp  = result + ii;
        cp->alpha = mstruct->alpha;
        cp->alphaa = mstruct->alphaa;
        cp->alphab = mstruct->alphab;
        cp->numdp  = mstruct->numdp;
        cp->totalnd = malloc(sizeof(int)*cp->numdp);
        memcpy(cp->totalnd,mstruct->totalnd,sizeof(int)*cp->numdp);
        cp->totalnt = malloc(sizeof(int)*cp->numdp);
        memcpy(cp->totalnt,mstruct->totalnt,sizeof(int)*cp->numdp);
        }

    }

void DeleteConparamVector(CONPARAM *cparray,int nn) {
    CONPARAM *cp;
    int ii;
    for ( ii = 0 ; ii < nn ; ii++ ) {
        cp = cparray + ii;
        free(cp->totalnd);
        free(cp->totalnt);
        }
    free(cparray);
    }

#endif
