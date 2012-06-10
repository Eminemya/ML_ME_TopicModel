#ifndef _DP_CRF
#define _DP_CRF
#include "util_crf.c"
#include "sparse.c"
#define ACTIVE 2
#define FROZEN 1
#define HELDOUT 0

typedef struct {
    /*statistics*/
    SS *datass;
    double alpha,ttlik;
    int numdata, numtable,lastta;
    OLink *tabless;
    int *datatt,*tablecc;
    OLink *wordss;
    /*backup*/
    double o_ttlik;
    int o_numtable,o_lastta;
    int *o_datatt,*o_tablecc;
    } DP_C;

void CopyDPVector_C(DP_C *new_dp,DP_C *old_dp,int numdp,int maxclass,int numword) {
    DP_C  *dp,*tmp_dp;
    int ii,numtable;
    for ( ii = 0 ; ii < numdp ; ii++ ) {
        tmp_dp        = old_dp+ii;
        dp            = new_dp+ii;
        dp->numdata   = tmp_dp->numdata;/**/
        dp->numtable= numtable=tmp_dp->numtable;
        dp->ttlik   = tmp_dp->ttlik;
        dp->o_ttlik   = tmp_dp->o_ttlik;
        dp->o_numtable= tmp_dp->o_numtable;
        dp->alpha=tmp_dp->alpha;

        if(tmp_dp->numdata!=0) {
            dp->lastta  = tmp_dp->lastta;
            dp->o_lastta  = tmp_dp->o_lastta;
            dp->datatt  = malloc(sizeof(int)*tmp_dp->numdata);
            dp->o_datatt  = malloc(sizeof(int)*tmp_dp->numdata);
            dp->tablecc = malloc(sizeof(int)*maxclass);
            dp->o_tablecc = malloc(sizeof(int)*maxclass);
            dp->datass = malloc(sizeof(int)*tmp_dp->numdata);
            dp->tabless = malloc(sizeof(OLink)*maxclass);
            memcpy(dp->datatt,tmp_dp->datatt,sizeof(int)*tmp_dp->numdata);
            memcpy(dp->datass,tmp_dp->datass,sizeof(int)*tmp_dp->numdata);
            memcpy(dp->tablecc,tmp_dp->tablecc,sizeof(int)*maxclass);
            memcpy(dp->o_datatt,tmp_dp->o_datatt,sizeof(int)*tmp_dp->numdata);
            memcpy(dp->o_tablecc,tmp_dp->o_tablecc,sizeof(int)*maxclass);
            CopyOLink(dp->tabless,tmp_dp->tabless,maxclass);
            dp->wordss=RightConnect(dp->tabless,numword,dp->lastta+1);
            }
        }
    }

void DeleteDPVector_C(DP_C *new_dp,int numdp,int maxclass,int numword) {
    DP_C  *dp;
    int ii;
    for ( ii = 0 ; ii < numdp ; ii++ ) {
        dp            = new_dp+ii;
        if(dp->numdata!=0) {
            free(dp->datatt);
            free(dp->tablecc);
            free(dp->o_datatt);
            free(dp->o_tablecc);
            free(dp->datass);
            DelCrossList(dp->tabless,dp->wordss,numword,maxclass,2);
            }
        }

    }
#endif
