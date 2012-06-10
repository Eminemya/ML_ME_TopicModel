#include "../distributions/multinomial/multinomial.c"
#include "hdp_crf.c"

#define HDPIN prhs[0]
#define CL prhs[1]
#define T prhs[2]
#define HDPOUT plhs[0]
#define DEL plhs[1]

void mexFunction( int nlhs, mxArray *plhs[],
                  int nrhs, const mxArray*prhs[] ) {
    int class;
    mxArray *tmparray, *tmpcell;
    double *haha,tt;
    HDP_C *hdp;
    if (nrhs!=3) mexErrMsgTxt("Three input arguments required.");
    if (!mxIsStruct(HDPIN)) mexErrMsgTxt("HDP structure expected.");
    if (mxGetNumberOfElements(HDPIN)!=1) mexErrMsgTxt("One structure expected.");
    hdp = mxReadHDP_C(HDPIN);
    class  = (int)mxGetScalar(CL);
    tt  =  mxGetScalar(T);
    DEL = mxCreateDoubleMatrix(1, 1,mxREAL);
    haha=mxGetPr(DEL);
    haha[0]=hdp_c_mergeclass(hdp, tt,class-1);
    hdp_c_relabelclass(hdp->base,hdp->dp);
    HDPOUT = mxDuplicateArray(HDPIN);
    mxWriteHDP_C(HDPOUT,hdp);
    }
