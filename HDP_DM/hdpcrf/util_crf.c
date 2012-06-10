#ifndef MXUTILS_CRF
#define MXUTILS_CRF
#include <math.h>
#include "psi.c"
#include <string.h>


typedef struct {
    int numdim;
    double *eta;
    } HH;
typedef int SS;
typedef int* QQ;
int samevector(int* v1,int* v2,int len) {
    int i,ss=1;
    for(i=0; i<len; i++) {
        if(v1[i]!=v2[i]) {
            ss=0;
            //printf("not equal ....%d,%d",v1[i],v2[i]);
            break;
            }
        }
    return ss;
    }
void printv1(int length, int* a) {
    int i;
    for(i=0; i<length; i++) {
        printf("%d  ",a[i]);
        }
    printf("\n");
    }
void printvector(int length, double* a) {
    int i;
    for(i=0; i<length; i++) {
        printf("%f  ",a[i]);
        }
    printf("\n");
    }
void prodvector(int length, double* a, double* b,double* c) {
    int i;
    for(i=0; i<length; i++) {
        c[i]  = a[i]*b[i];
        }
    }


int randmult(double *pi, int veclength, int skip) {
    double *pi2, *piend;
    double sum = 0.0, mass;
    int cc = 0;

    piend = pi + veclength*skip;
    for ( pi2 = pi ; pi2 < piend ; pi2 += skip )
        sum += *pi2;
    mass = drand48() * sum;
    while (1) {
        mass -= *pi;
        if ( mass <= 0.0 ) break;
        pi += skip;
        cc ++;
        }
    return cc;
    }
#define M_lnSqrt2PI 0.91893853320467274178
static double gamma_series[] = {
    76.18009172947146,
    -86.50532032941677,
    24.01409824083091,
    -1.231739572450155,
    0.1208650973866179e-2,
    -0.5395239384953e-5
    };
double *gamln_0,*gamln_a,*gamln_g,*gamln_l,*gamln_wl;

void randperm(int n,int *perm) {
    int i, j, t;
    for(i=0; i<n; i++) {
        perm[i] = i;
        }
    for(i=0; i<n; i++) {
        j = rand()%(n-i)+i;
        t = perm[j];
        perm[j] = perm[i];
        perm[i] = t;
        }
    }

/*matlab: sort(rand(1,n))
void randperm(int *p,int len) {
    int i,j;
    for ( i = 0; i < len; i++) {
        j = floor(drand48() * (i + 1));
        p[i] = p[j];
        p[j] = i;
        }
    }
*/
void freeQQs(QQ *qq,int mm) {
    int jj;
    for ( jj = 0 ; jj < mm ; jj++ ) {
        free(qq[jj]);
        }
    free(qq);
    }

double gammaln(double x) {
    int i;
    double denom, x1, series;
    denom = x+1;
    x1 = x + 5.5;
    series = 1.000000000190015;
    for(i = 0; i < 6; i++) {
        series += gamma_series[i] / denom;
        denom += 1.0;
        }
    return( M_lnSqrt2PI + (x+0.5)*log(x1) - x1 + log(series/x) );
    }
double gamln(int pre,double x,int type) {
    if(pre<=10000) {
        if(pre<0) {
            printf("DAMN...................... %d\n",pre);
            }
        else {
            /*read from global variables*/
            switch(type) {
                case 1:
                    return gamln_0[pre];
                case 2:
                    return gamln_a[pre];
                case 3:
                    return gamln_g[pre];
                case 4:
                    return gammaln(x);
                    /*return gamln_l[pre];*/
                case 5:
                    return gamln_wl[pre];
                }
            }
        }
    else {
        /*4th order approximation
        return( M_lnSqrt2PI + (x-0.5)*log(x)-x);*/
        return gammaln(x);
        }
    }




/*
double delta_t(int t1_Nc,int t2_Nc) {
    double y;

    y=gamln(t1_Nc)+gamln(t2_Nc)-gamln(t1_Nc+t2_Nc);

    return y;
    }
*/

void add_t(double *t1,double *t2,int n1,int n2,int sign,double *y) {
    int i,j,count=0,*index,judge,len;
    switch(sign) {
        case 1:
            for(i=0; i<n1; i++) {
                y[i]=t1[i];
                }
            for(i=0; i<n2; i++) {
                y[n1+i]=t2[i];
                }
            break;
        case -1:
            index=(int *) calloc(n2, sizeof(int));
            for(j=0; j<n2; j++) {
                for(i=0; i<n1; i++) {
                    if(t1[i]==t2[j]) {
                        index[count]=i;
                        count+=1;
                        break;
                        }
                    }
                }
            len=0;
            for(i=0; i<n1; i++) {
                judge=0;
                for(j=0; j<count; j++) {
                    if(i==index[j]) {
                        judge=-1;
                        break;
                        }
                    }
                if(judge==0) {
                    y[len]=t1[i];
                    len+=1;
                    }
                }
            free(index);
            break;
        }
    }

void test_psi() {
    int i;
    for(i=1; i<1000; i++) {
        printf("%f, ",psi((double)i));
        }

    }

#define swap(arr,x,y,type) { \
      type *t1,*t2,tt; \
      t1 = arr+x; \
      t2 = arr+y; \
      tt = *t1; \
      *t1 = *t2; \
      *t2 = tt; \
}
/*ascending order*/
void quicksort(double *list,int *ind,int m,int n) {
    int i,j,k;
    double key;
    if( m < n) {
        k = (int)(m+n)/2;
        swap(list,m,k,double);
        swap(ind,m,k,int);
        key = list[m];
        i = m+1;
        j = n;
        while(i <= j) {
            while((i <= n) && (list[i] <= key))
                i++;
            while((j >= m) && (list[j] > key))
                j--;
            if( i < j) {
                swap(list,i,j,double);
                swap(ind,i,j,int);
                }
            }
        // swap two elements
        swap(list,m,j,double);
        swap(ind,m,j,int);
        // recursively sort the lesser list
        quicksort(list,ind,m,j-1);
        quicksort(list,ind,j+1,n);
        }
    }

//#define S_STEP 0.0000001
#define S_STEP 0.0001
double SearchLambda(int *nn,double *eta,int len) {
    int i,j,k,ind[2];
    int *preindex=malloc(sizeof(int)*len),*index=malloc(sizeof(int)*len);
    double step,*val=malloc(sizeof(double)*len),pre1,pre2,*val_c=malloc(sizeof(double)*len),del=0;
    double *preval=malloc(sizeof(double)*(1+len));
    memcpy(preval,eta,sizeof(double)*(len+1));
    for(i=0; i<len; i++) {
        val[i]=psi(nn[i]+eta[i+1])-psi(eta[i+1]);
        val_c[i]=val[i];
        index[i]=i;
        del-=val[i];
        }

    quicksort(val_c,index,0,len-1);
    //coarse to fine
    for(k=0;k<8;k++){
    step=S_STEP*(int)pow(10,7-k);
    //for(k=0;k<7;k++){
    //step=S_STEP*(int)pow(10,6-k);
    memset(preindex,0,len*sizeof(int));
    while(samevector(preindex,index,len)==0) {
        memcpy(preindex,index,sizeof(int)*len);
        for(i=0; i<(int)len/2; i++) {
            ind[0]=index[i];
            ind[1]=index[len-1-i];
            index[i]=i;
            index[len-1-i]=len-1-i;
            /*for all pairs */
                //printf("aaa %d,%d,%f,%f,%f,%f\n ",ind[0],ind[1],eta[1+ind[0]],eta[1+ind[1]],val[ind[0]],val[ind[1]]);
                //
            //if((eta[1+ind[0]]<0 ||  eta[1+ind[1]]<0)){
            //printf("input err: %d,%f,%f,%f\n", k,eta[1+ind[0]], eta[1+ind[1]],step);
            //}
            if(val[ind[0]]>val[ind[1]]){
            printf("sort err: %d,%d,%f,%f,%f,%f,%f\n", k,i,val_c[i],val_c[len-i-1],val[ind[0]], val[ind[1]],step);
                        printv1(len,index);
                        //printv1(len,nn);
                        printvector(len,val_c);
                        printvector(len,val);
            }
            while(val[ind[0]]<val[ind[1]] && eta[1+ind[0]]-step>0) {
                pre1=val[ind[0]];
                pre2=val[ind[1]];
                eta[1+ind[0]]-= step;
                eta[1+ind[1]]+= step;
                val[ind[0]]=psi(eta[1+ind[0]]+nn[ind[0]])-psi(eta[1+ind[0]]);
                val[ind[1]]=psi(eta[1+ind[1]]+nn[ind[1]])-psi(eta[1+ind[1]]);
                //if(eta[1+ind[0]]>0){
                //printf("gg %d,%d,%f,%f,%f,%f\n ",ind[0],ind[1],eta[1+ind[0]],eta[1+ind[1]],val[ind[0]],val[ind[1]]);
                //}
                 //   if( eta[1+ind[0]]<0 ||  eta[1+ind[1]]<0){
                 //   printf("iteration err: %d,%f,%f,%f,%f,%f\n", k,val[ind[0]],val[ind[1]],eta[1+ind[0]], eta[1+ind[1]],step);
                //  }
                
                }
            //be careful about the equal case...
            if(val[ind[0]]>val[ind[1]]) {
                /*one step back*/
                eta[1+ind[0]]+= step;
                eta[1+ind[1]]-= step;
                //if( eta[1+ind[0]]<0 ||  eta[1+ind[1]]<0){
                //printf("add back err: %d,%f,%f,%f,%f,%f,%f,%f\n", k,val[ind[0]],val[ind[1]],pre1,pre2,eta[1+ind[0]], eta[1+ind[1]],step);
                //}
                val[ind[0]]=pre1;
                val[ind[1]]=pre2;
                //printf("fff %d,%d,%f,%f,%f,%f\n ",ind[0],ind[1],eta[1+ind[0]],eta[1+ind[1]],val[ind[0]],val[ind[1]]);
                //if(val[ind[0]]>val[ind[1]]) {
                //    printf("pre_wrong...%d,%f,%f\n",k,val[ind[0]],val[ind[1]]);
                //}
                }
            }      
           if (len%2==1){
           index[(len-1)/2]=(len-1)/2;
           }  
            memcpy(val_c,val,sizeof(double)*len);
            quicksort(val_c,index,0,len-1);
            //printv1(len,index);
            //printv1(len,nn);
            //printvector(len+1,eta);
        }
    }
    //printvector(len,val);
    //printvector(len+1,eta);
    for(i=0; i<len; i++) {
        del+=val[i];
        }    
    free(preindex);
    free(index);
    free(val);
    free(val_c);

    return del;
    }
#endif

