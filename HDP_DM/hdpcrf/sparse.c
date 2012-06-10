#ifndef _SPARSE
#define _SPARSE
#include "util_crf.c"
/*
classqq:
row<->word
col<->class

since K<<W, we prefer to search the col instead of row
*/
typedef struct OLNode {
    int row,col;
    int val,o_val;
    double gl,o_gl;
    struct OLNode *down;
    struct OLNode *right;
    } OLNode,*OLink;
/*row index starts from 0,row index starts from 1*/
/*array of list for faster access*/

void PrintRow(OLink wordqq) {
    OLNode *p;
    if(wordqq!=NULL) {
        p=wordqq->right;
        while(p!=NULL) {
            printf("%d,%d,%d,%d\n",p->row,p->col,p->val,p->o_val);
            p=p->right;
            }
        }
    printf(".....................\n");
    }
void PrintCol(OLink classqq) {
    OLNode *p;
    if(classqq!=NULL) {
        p=classqq->down;
        while(p!=NULL) {
            printf("%d,%d,%d,%d\n",p->row,p->col,p->val,p->o_val);
            p=p->down;
            }
        }
    printf(".....................\n");
    }


/*0)Deletion*/
void DelNode(OLNode *node)  {
    if(node->down==NULL) {
        free(node);
        }
    else {
        DelNode(node->down);
        node->down=NULL;
        DelNode(node);
        }
    }
void DelCrossList(OLink *col_head,OLink *row_head,int numword,int maxclass,int option)  {
    int col,row;
    OLNode *p;
    for(col=0; col<maxclass; col++) {
        p=col_head[col];
        if(p!=NULL) {
            DelNode(p);
            }
        }
    free(col_head);
    if(option==2) {
        for(row=0; row<numword; row++) {
            if(row_head[row]!=NULL) {
                free(row_head[row]);
                }
            }
        free(row_head);
        }
    }


/*1) I/O*/
OLink *ReadSparse(QQ *pr, int mm,int nn,int maxnum,int shift,int option,HH *hh) {
    /*option=0:for tabless;  option=1: for classqq ;  option=2: for ctindex */
    int ii, jj, sum;
    OLink *col_head;
    col_head=malloc(sizeof(OLink)*maxnum);
    /*
    printf("huu:%d,%d\n",mm,nn);*/
    for(ii=0; ii<nn; ii++) {
        col_head[ii] = malloc(sizeof(OLNode));
        col_head[ii]->o_val=0;
        col_head[ii]->val=0;
        col_head[ii]->down=NULL;
        }
    for(ii=nn; ii<maxnum; ii++) {
        col_head[ii]=NULL;
        }
    OLNode* p;
    OLNode* q;
    for ( jj = 0 ; jj < nn ; jj++ ) {
        sum = 0;
        q=col_head[jj];
        for ( ii = 1 ; ii < mm+1 ; ii++ ) {
            if(pr[jj][ii]!=0) {
                p=malloc(sizeof(OLNode));
                p->row = ii-1;
                p->col = jj;
                /*if(jj==0&&option==2){printf("oh:%d,%d\n",ii,p->row);}*/
                p->o_val = pr[jj][ii]+shift;
                p->val = pr[jj][ii]+shift;
                sum += pr[jj][ii];
                if(option==1) {
                    p->o_gl = gamln(p->val,p->val+hh[jj].eta[ii],4);
                    p->gl = p->o_gl;
                    }
                else if(option==0) {
                    p->o_gl = gamln_0[p->val+1];
                    p->gl = p->o_gl;
                    }
                p->down=NULL;
                q->down=p;
                q=p;
                }
            }
        /*printf("clus:%d,%d\n",jj,sum);*/
        if(sum!=0) {
            col_head[jj]->o_val= sum;
            col_head[jj]->val= sum;
            if(option==1) {
                col_head[jj]->o_gl=gamln(sum,sum+hh[jj].eta[0],5);
                col_head[jj]->gl=col_head[jj]->o_gl;
                }
            }
        }
    return col_head;
    }


void CopyOLink(OLink *new_classqq,OLink *classqq,int maxclass) {
    int ii;
    OLNode* p;
    OLNode* q;
    OLNode* tmp;
    for(ii=0; ii<maxclass; ii++) {
        if(classqq[ii]==NULL) {
            new_classqq[ii]=NULL;
            }
        else {
            new_classqq[ii]=malloc(sizeof(OLNode));
            memcpy(new_classqq[ii],classqq[ii],sizeof(OLNode));
            new_classqq[ii]->down=NULL;
            q=classqq[ii]->down;
            p=new_classqq[ii];
            while(q!=NULL) {
                tmp=malloc(sizeof(OLNode));
                memcpy(tmp,q,sizeof(OLNode));
                tmp->down=p->down;
                p->down=tmp;
                q=q->down;
                p=p->down;
                }
            }
        }
    }



OLink *RightConnect(OLink *classqq,int numword,int numclass) {
    /*for faster sequential search*/
    OLink *row_head;
    OLink *tmp;
    OLNode *tmpnode;
    int ii,jj,count;
    row_head=malloc(sizeof(OLink)*numword);
    tmp=malloc(sizeof(OLink)*numclass);
    for(ii=0; ii<numclass; ii++) {
        tmp[ii]=classqq[ii]->down;
        }
    for(ii=0; ii<numword; ii++) {
        row_head[ii]=NULL;
        count=0;
        for(jj=0; jj<numclass; jj++) {
            if(tmp[jj]!=NULL&&tmp[jj]->row==ii) {
                if(row_head[ii]==NULL) {
                    row_head[ii]=malloc(sizeof(OLNode));
                    row_head[ii]->right=NULL;
                    tmpnode=row_head[ii];
                    }
                tmp[jj]->right=tmpnode->right;
                count+=tmp[jj]->val;
                tmpnode->right=tmp[jj];
                tmpnode=tmpnode->right;
                tmp[jj]=tmp[jj]->down;
                }
            }
        if(count!=0) {
            row_head[ii]->val=count;
            row_head[ii]->o_val=count;
            row_head[ii]->gl=gamln_0[count+1];/*no need to encapsule with gamln(), since the number will certainly within bound*/
            row_head[ii]->o_gl=row_head[ii]->gl;
            }
        }
    free(tmp);
    return row_head;
    }

QQ *WriteSparse(int numword,int nn,int maxnum,OLink *col_head,OLink *row_head,int shift,int del) {
    QQ *pr;
    OLNode *p;
    pr = malloc(sizeof(QQ)*nn);
    int ii, jj, mm, sum;
    int www=0;
    /*if(col_head[0]->val>500){www=1;}*/
    if(del==0) {
        /*write classnd*/
        pr[0]=malloc(sizeof(int)*nn);
        for ( jj = 0 ; jj < nn-1 ; jj ++ ) {
            if(www==1) {
                pr[0][jj]=col_head[jj]->gl;
                }
            else {
                pr[0][jj]=col_head[jj]->val;
                }
            }
        pr[0][nn-1]=0;
        }
    else {
        /*write classqq*/
        for ( jj = 0 ; jj < nn-1 ; jj ++ ) {
            pr[jj]=malloc(sizeof(int)*(numword+1));
            p=col_head[jj];
            if(p==NULL||p->val==0) {
                mm=-1;
                }
            else {
                p=p->down;
                mm=p->row+1;
                }
            for ( ii = 1 ; ii < numword+1 ; ii++ ) {
                /*if(jj==2||jj==3){printf("%d,%d,%d\n",jj,ii,p->val,p->row);}*/
                if(ii==mm) {
                    if(www==1) {
                        pr[jj][ii] = p->gl+shift;
                        }
                    else {
                        pr[jj][ii] = p->val+shift;
                        }

                    p=p->down;
                    if(p==NULL) {
                        mm=-1;
                        }
                    else {
                        mm=p->row+1;
                        }
                    }
                else {
                    pr[jj][ii] = shift;
                    }
                }

            }
        /*extra column to be 0*/
        pr[nn-1]=malloc(sizeof(int)*(numword+1));
        for ( ii = 0 ; ii < numword+1 ; ii++ ) {
            pr[nn-1][ii] = 0;
            }
        DelCrossList(col_head,row_head,numword,maxnum,del);
        }
    return pr;
    }

/*2) Local-datatt:change one element*/
int AddElement(OLink colnode,OLink rownode,int row,int col,int add,int option,double *eta) {
    /*option=0:for tabless;  option=1: for classqq */
    OLNode* q;
    OLNode* qq;
    OLNode* p;
    int new_num;
    /*row*/
    /*search index*/
    q=rownode;
    while(q->right!=NULL&&q->right->col<col) {
        q=q->right;
        }
    /**/
    if(q->right==NULL||q->right->col!=col) {
        /*no match*/
        /*printf("%d,%d\n",row,col);*/
        new_num=add;
        p = (OLNode*)malloc(sizeof(OLNode));
        p->row = row;
        p->col = col;
        p->o_val = 0;
        p->val = add;
        if(option==1) {
            p->gl =gamln(add,add+eta[1+row],4);
            }
        else {
            p->gl=gamln_0[p->val+1];
            }
        p->right=q->right;
        q->right=p;
        /*col*/
        qq=colnode;
        while(qq->down!=NULL&&qq->down->row<row) {
            qq=qq->down;
            }
        p->down=qq->down;
        qq->down=p;
        /*add =-1,1*/
        if(colnode->val==0) {
            if(option==1) {
                colnode->gl = gamln(add,add+eta[0],5);
                }
            else {
                colnode->gl = 0;
                }
            }
        else {
            if(option==1) {
                colnode->gl += add*log(colnode->val+0.5*add-0.5+eta[0]);
                }
            else {
                colnode->gl += add*log(colnode->val+0.5*add-0.5);
                }

            }
        /* }*/
        }
    else {
        /*match*/
        q=q->right;
        if(option==1) {
            if(add==1||add==-1) {
                q->gl += add*log(q->val+0.5*add-0.5+eta[1+row]);
                colnode->gl += add*log(colnode->val+0.5*add-0.5+eta[0]);
                }
            else {
                q->gl = gamln(add+q->val,add+q->val+eta[1+row],4);
                colnode->gl = gamln(colnode->val+add,colnode->val+add+eta[0],5);
                }
            }
        q->val+=add;
        if(option==0) {
            q->gl=gamln_0[q->val+1];
            }
        /*if(add==-1&&row==2){printf("dodo:%d\n",q->val);}*/
        new_num=q->val;
        }
    colnode->val+=add;
    return new_num;
    }

int AddColElement(OLink colnode,int row,int col,int add) {
    /*for ctindex only*/
    /*update=0:no update;1: update sum only;2: update sum+single */
    OLNode* q;
    OLNode* p;
    /*col*/
    /*search index*/
    q=colnode;
    while(q->down!=NULL&&q->down->row<row) {
        q=q->down;
        }
    if(colnode->val==0 || q->down==NULL||q->down->row!=row) {
        /*no match*/
        p = (OLNode*)malloc(sizeof(OLNode));
        p->row = row;
        p->col = col;
        p->o_val = 0;
        p->val = add;
        p->down=q->down;
        q->down=p;
        }
    else {
        /*match*/
        q->down->val+=add;
        }
    colnode->val+=add;

    return q->val;
    }

void ExpandRow(OLink rownodes,int *fullrow,int lastcl) {
    OLNode* q;
    memset(fullrow,0,sizeof(int)*(lastcl+1));
    /*search index*/
    q=rownodes->right;
    while(q!=NULL) {
        fullrow[q->col]=q->val;
        q=q->right;
        }
    }
void UpdateGl(OLink colnode,double *eta) {
    OLNode* q;
    colnode->gl=gamln(colnode->val,colnode->val+eta[0],5);
    colnode->o_gl=colnode->gl;
    //printf("2::%f,%d\n",colnode->gl,colnode->val);
    q=colnode->down;
    while(q!=NULL) {
        q->gl=gamln(0,q->val+eta[1+q->row],4);
        q->o_gl=q->gl;
        q=q->down;
    }
}
double ExpandCol(OLink colnodes,int*fullcol,int numword) {
    double cc=0;
    memset(fullcol,0,sizeof(int)*numword);
    OLNode* q;
    /*search index*/
    q=colnodes->down;
    while(q!=NULL) {
        fullcol[q->row]=q->val;
        cc+=q->val;
        q=q->down;
        }
    return cc;
    }

int ExpandColNzero(OLink colnodes,int*fullcol,int numword) {
    int cc=0;
    memset(fullcol,0,sizeof(int)*numword);
    OLNode* q;
    /*search index*/
    q=colnodes->down;
    while(q!=NULL) {
        fullcol[cc]=q->val;
        q=q->down;
        cc+=1;
        }
    return cc;
    }

int SearchCol(OLink colnodes,int row) {
    OLNode* q;
    OLNode* p;
    /*search index*/
    q=colnodes;
    while(q->down!=NULL&&q->down->row<=row) {
        q=q->down;
        }
    if(q->row!=row) {
        return 0;
        }
    else {
        return q->val;
        }
    }
int SearchRow(OLink rownodes,int col) {
    OLNode* q;
    int move=0;
    if(rownodes==NULL) {
        return 0;
        }
    /*search index*/
    q=rownodes;
    while(q->right!=NULL&&q->right->col<=col) {
        q=q->right;
        move=1;
        }
    if(move==0||q->col!=col) {
        return 0;
        }
    else {
        return q->val;
        }
    }

/*2) Local-tablecc/merge-table:change one table*/
void AddCol(OLink class,OLink table,OLink *rownodes,int classcol,int option,double *del_col) {
    /*option=0: tabless; option=1: classqq; option=2: pure copy*/
    OLNode* p;
    OLNode* q;
    OLNode* new;
    OLNode* tmp;
    int i=0;
    q=table->down;
    p=class;
    class->val+=table->val;
    if(option==1) {
        class->gl=del_col[i];
        i++;
        }
    /**/
    int ha=0;
    while(q->val==0) {
        q=q->down;
        }
    while(q!=NULL) {
        while(p->down!=NULL&&p->down->row<=q->row) {
            ha=1;
            p=p->down;
            }
        if(ha!=0&&p->row==q->row) {
            p->val+=q->val;
            if(option==1) {
                p->gl=del_col[i];
                /*printf("aaa:%d,%f,%d\n",i,del_col[i],p->val);*/
                i++;
                }
            }
        else {
            new = (OLNode*)malloc(sizeof(OLNode));
            memcpy(new,q,sizeof(OLNode));
            new->col=classcol;
            new->down=p->down;
            new->o_val=0;
            p->down=new;
            if(option==1) {
                new->gl=del_col[i];
                /*printf("aaa:%d,%f,%d\n",i,del_col[i],p->val);*/
                i++;
                }
            /*right connect*/
            if(option<=1) {
                tmp=rownodes[new->row];
                while(tmp->right!=NULL&&tmp->right->col<=classcol) {
                    tmp=tmp->right;
                    }
                new->right=tmp->right;
                tmp->right=new;
                p=new;
                }
            }
        q=q->down;
        while(q!=NULL&&q->val==0) {
            q=q->down;
            }

        }
    }

void DeleteCol(OLink class,OLink table,int option,double *del_col) {
    /*used for localtablecc*/
    OLNode* p;
    OLNode* q;
    OLNode* new;
    int i=0;
    q=table->down;
    p=class->down;
    class->val-=table->val;
    if(option==1) {
        /*classqq*/
        class->gl=del_col[i];
        i++;
        while(q->val==0) {
            q=q->down;
            }
        while(q!=NULL) {
            while(p->row!=q->row) {
                p=p->down;
                }
            p->val-=q->val;
            p->gl=del_col[i];
            i++;
            q=q->down;
            while(q!=NULL&&q->val==0) {
                q=q->down;
                }

            }
        }
    else {
        /*tabless*/
        while(q->val==0) {
            q=q->down;
            }
        while(q!=NULL) {
            while(p->row!=q->row) {
                p=p->down;
                }
            p->val-=q->val;
            q=q->down;
            while(q!=NULL&&q->val==0) {
                q=q->down;
                }

            }

        }
    }
void SetZero(OLink class,int option,double *eta) {
    /*option=0:for tabless;  option=1: for classqq ; option=2: for ctindex*/
    OLNode* p;
    p=class->down;
    class->val=0;
    if(option==1) {
        class->gl=gamln(0,eta[0],5);
        }
    while(p!=NULL) {
        p->val=0;
        if(option==1) {
            p->gl=gamln(0,eta[p->row+1],4);
            }
        else if(option==0) {
            p->gl=0;
            }
        p=p->down;
        }
    }
void SetCol(OLink class,int col) {
    /*option=0:for tabless;  option=1: for classqq ; option=2: for ctindex*/
    OLNode* p;
    p=class->down;
    while(p!=NULL) {
        p->col=col;
        p=p->down;
        }
    }

double delta_k(OLink col_1,OLink col_2,double *eta, int sign,double *del_col) {
    /*calculate the change on col_1 */
    int  i=0;
    double y;
    /* for priors */
    OLNode *p,*q;
    switch ( sign ) {
        case 1:
            /*add col_2 to col_1*/
            del_col[i]=gamln(col_1->val+col_2->val,col_1->val+col_2->val+eta[0],5);
            y=-del_col[i]+col_1->gl;
            /*double ta=y;
            printf("0:%f\n",y);*/
            i++;
            p=col_1->down;
            q=col_2->down;
            while(q->val==0) {
                q=q->down;
                }
            while(q!=NULL) {
                while(p->down!=NULL&&p->row<q->row) {
                    p=p->down;
                    }
                if(p->row==q->row) {
                    del_col[i]=gamln(p->val+q->val,eta[1+p->row]+p->val+q->val,4);
                    y+=-p->gl+del_col[i];
                    i++;
                    }
                else {
                    del_col[i]=gamln(q->val,q->val+eta[1+q->row],4);
                    y+=-gamln(0,eta[1+q->row],4)+del_col[i];
                    i++;
                    }
                /*if(ta+7315.89356<0&&ta+7315.89357>0)printf("%d,%d:%d,%d,%f,%f\n",q->row,p->row,q->val,p->val,-p->gl,y);  */
                q=q->down;
                while(q!=NULL&&q->val==0) {
                    q=q->down;
                    }
                }
            break;
        case 0:
            /*assign col_2 to new */
            del_col[i]=gamln(col_2->val,eta[0]+col_2->val,5);
            y=gamln(0,eta[0],5)-del_col[i];
            /*printf("cc %f,%f\n",eta[0],y);*/
            i++;
            p=col_2->down;
            while(p!=NULL&&p->val==0) {
                p=p->down;
                }
            while(p!=NULL) {
                del_col[i]=gamln(p->val,eta[1+p->row]+p->val,4);
                y-=gamln(0,eta[1+p->row],4)-del_col[i];
                /*                printf("cc %f,%f\n",eta[1+p->row],y);*/
                i++;
                p=p->down;
                while(p!=NULL&&p->val==0) {
                    p=p->down;
                    }
                }
            break;
        case -1:
            /*delete col_2 from col_1*/
            /*printf("sum:%d,%d\n",col_1->val,col_2->val);*/
            del_col[i]=gamln(col_1->val-col_2->val,col_1->val-col_2->val+eta[0],5);
            y=-del_col[i]+col_1->gl;
            //printf("1::%f,%f,%f ,%d,%d\n",y,del_col[i],col_1->gl,col_1->val,col_2->val);/**/
            i++;
            p=col_1->down;
            q=col_2->down;
            while(q->val==0) {
                q=q->down;
                }
            while(q!=NULL) {
                /*            printf("%d,%d,%d,%d\n",q->row,q->val,p->row,p->val);*/
                while(p->row!=q->row) {
                    p=p->down;
                    /*printf("f:%d,%d,%d,%d\n",q->row,q->val,p->row,p->val);*/
                    }
                del_col[i]=gamln(p->val-q->val,eta[1+p->row]+p->val-q->val,4);
                y-=p->gl-del_col[i];
                //if(fabs(p->gl-gamln(0,p->val+eta[1+p->row],4))>0.1){printf("cc: %f,%f\n",p->gl,gamln(0,p->val+eta[1+p->row],4));}
                /*printf("2::%f,%f,%f,%d,%d \n",y,p->gl,del_col[i],p->val,q->val);*/
                i++;
                q=q->down;
                while(q!=NULL&&q->val==0) {
                    q=q->down;
                    }
                }
            break;
        case 2:
            /*for the new table counting term, we do the sum_gl for two tables in the restaurant*/
            /* copy each value */
            del_col[i]=0;
            y=0;
            i++;
            p=col_1->down;
            q=col_2->down;
            while(q->val==0) {
                q=q->down;
                }
            while(q!=NULL) {
                while(p->down!=NULL&&p->row<q->row) {
                    p=p->down;
                    }
                if(p->row==q->row) {
                    del_col[i]=gamln_0[p->val+q->val+1];
                    y+=p->gl+q->gl-del_col[i];
                    i++;
                    }
                else {
                    del_col[i]=q->gl;
                    i++;
                    }
                q=q->down;
                while(q!=NULL&&q->val==0) {
                    q=q->down;
                    }
                }
            break;
        case 3:
            /*for the new table counting term, we do the sum_gl for two tables in the restaurant*/
            /* total value only */
            y=0;
            i++;
            p=col_1->down;
            q=col_2->down;
            while(q->val==0) {
                q=q->down;
                }
            while(q!=NULL) {
                while(p->down!=NULL&&p->row<q->row) {
                    p=p->down;
                    }
                if(p->row==q->row) {
                    y+=p->gl+q->gl-gamln_0[p->val+q->val+1];
                    i++;
                    }
                q=q->down;
                while(q!=NULL&&q->val==0) {
                    q=q->down;
                    }
                }
            break;
        }

    return y;
    }
/*3) for revertion*/
void Revert(OLink *rownodes,OLink *colnodes,int numword,int numclass,int option) {
    /*option=0: tabless,1:classqq,2:ctindex*/
    OLNode* p;
    OLNode* q;
    OLNode* none;
    int ii,jj,count_null;
    OLink row_head;
    OLink *tmp;
    none=malloc(sizeof(OLNode));
    none->down=NULL;
    tmp=malloc(sizeof(OLink)*numclass);
    for(ii=0; ii<numclass; ii++) {
        if(colnodes[ii]!=NULL) {
            colnodes[ii]->val=colnodes[ii]->o_val;
            if(option==1) {
                colnodes[ii]->gl=colnodes[ii]->o_gl;
                }
            tmp[ii]=colnodes[ii];
            }
        else {
            tmp[ii]=none;
            }
        }
    switch(option)    {
        case 0:
            for(ii=0; ii<numword; ii++) {
                count_null=0;
                row_head=rownodes[ii];
                for(jj=0; jj<numclass; jj++) {
                    if(tmp[jj]->down!=NULL&&tmp[jj]->down->row==ii) {
                        p=tmp[jj]->down;
                        if(p->o_val!=0) {
                            p->val=p->o_val;
                            p->gl=p->o_gl;
                            row_head=row_head->right;
                            tmp[jj]=p;
                            }
                        else {
                            /*col*/
                            tmp[jj]->down=p->down;
                            /*row*/
                            row_head->right=p->right;
                            free(p);
                            }
                        }
                    if(tmp[jj]->down==NULL) {
                        count_null+=1;
                        }
                    }
                if(count_null==numclass) {
                    break;
                    }
                }
            break;
        case 1:
            for(ii=0; ii<numword; ii++) {
                count_null=0;
                row_head=rownodes[ii];
                for(jj=0; jj<numclass; jj++) {
                    if(tmp[jj]->down!=NULL&&tmp[jj]->down->row==ii) {
                        p=tmp[jj]->down;
                        if(p->o_val!=0) {
                            p->val=p->o_val;
                            p->gl=p->o_gl;
                            row_head=row_head->right;
                            tmp[jj]=tmp[jj]->down;
                            }
                        else {
                            /*col*/
                            tmp[jj]->down=p->down;
                            /*row*/
                            row_head->right=p->right;
                            free(p);
                            }
                        }
                    if(tmp[jj]->down==NULL) {
                        count_null+=1;
                        }
                    }
                if(count_null==numclass) {
                    break;
                    }
                }
            break;
        case 2:
            for(jj=0; jj<numclass; jj++) {
                while(tmp[jj]->down!=NULL) {
                    p=tmp[jj]->down;
                    if(p->o_val!=0) {
                        p->val=p->o_val;
                        p->gl=p->o_gl;
                        tmp[jj]=p;
                        }
                    else {
                        /*col*/
                        tmp[jj]->down=p->down;
                        free(p);
                        }
                    }
                }
            break;
        }
    free(tmp);
    free(none);
    }
void Update(OLink *rownodes,OLink *colnodes,int numword,int numclass,int option) {
    /*option=0: tabless,1:classqq,2:ctindex*/
    OLNode* p;
    OLNode* q;
    OLNode* none;
    int ii,jj,count_null;
    OLink row_head;
    OLink *tmp;
    none=malloc(sizeof(OLNode));
    none->down=NULL;
    tmp=malloc(sizeof(OLink)*numclass);
    for(ii=0; ii<numclass; ii++) {
        if(colnodes[ii]!=NULL) {
            colnodes[ii]->o_val=colnodes[ii]->val;
            if(option==1) {
                colnodes[ii]->o_gl=colnodes[ii]->gl;
                }
            tmp[ii]=colnodes[ii];
            }
        else {
            tmp[ii]=none;
            }
        }
    switch(option)    {
        case 0:
            for(ii=0; ii<numword; ii++) {
                count_null=0;
                row_head=rownodes[ii];
                /*if(numclass==37&&ii==2){printf("what?\n");PrintRow(row_head);}*/
                for(jj=0; jj<numclass; jj++) {
                    if(tmp[jj]->down!=NULL&&tmp[jj]->down->row==ii) {
                        p=tmp[jj]->down;
                        /*if(numclass==37&&ii==2){printf("oo:%d\n",p->col);};*/
                        if(p->val!=0) {
                            p->o_val=p->val;
                            p->o_gl=p->gl;
                            q=row_head;
                            row_head=row_head->right;
                            /*if(numclass==31&&ii==2){printf("pp:%d\n",row_head->col);};*/
                            if(row_head->col!=p->col) {
                                printf("crap................%d\n",row_head->col);
                                }
                            /*row_head=p;*/
                            tmp[jj]=p;
                            }
                        else {
                            /*col*/
                            tmp[jj]->down=p->down;
                            /*row*/
                            row_head->right=p->right;
                            /* if(numclass==31&&ii==2){printf("qq:%d\n",row_head->col);};*/
                            free(p);
                            }
                        }
                    if(tmp[jj]->down==NULL) {
                        count_null+=1;
                        }

                    }
                if(count_null==numclass) {
                    break;
                    }
                }
            break;
        case 1:
            for(ii=0; ii<numword; ii++) {
                count_null=0;
                row_head=rownodes[ii];
                for(jj=0; jj<numclass; jj++) {
                    if(tmp[jj]->down!=NULL&&tmp[jj]->down->row==ii) {
                        p=tmp[jj]->down;
                        if(p->val!=0) {
                            p->o_val=p->val;
                            p->o_gl=p->gl;
                            row_head=row_head->right;
                            tmp[jj]=p;
                            }
                        else {
                            /*col*/
                            tmp[jj]->down=p->down;
                            /*row*/
                            row_head->right=p->right;
                            free(p);
                            }
                        }
                    if(tmp[jj]->down==NULL) {
                        count_null+=1;
                        }
                    }
                if(count_null==numclass) {
                    break;
                    }
                }
            break;
        case 2:
            for(jj=0; jj<numclass; jj++) {
                while(tmp[jj]->down!=NULL) {
                    p=tmp[jj]->down;
                    if(p->val!=0) {
                        p->o_val=p->val;
                        /*p->o_gl=p->gl;*/
                        tmp[jj]=p;
                        }
                    else {
                        /*col*/
                        tmp[jj]->down=p->down;
                        free(p);
                        }
                    }
                }
            break;
        }
    free(tmp);
    free(none);
    }
/*

void CheckGl(OLink *classqqs,int lastcl,double eta){
OLNode *p;
OLink classqq;
int i;
for(i=0;i<=lastcl;i++){
classqq=classqqs[i];
if(classqq!=NULL){
if(fabs(classqq->gl-gamln(classqq->val+eta*25))>0.00001){
printf("h::%d,%d,%f,%f\n",i,classqq->val,classqq->gl,gamln(classqq->val+eta*25));
}
p=classqq->down;
while(p!=NULL){
if(fabs(p->gl-gamln(p->val+eta))>0.00001){
printf("d::%d,%d,%d,%f,%f\n",p->row,p->col,p->val,p->gl,gamln(p->val+eta));
}
p=p->down;
}
}
}
}

void CheckGl_1(OLink *classqqs,int cl,double eta){
OLNode *p;
OLink classqq;
int i;
for(i=cl;i<=cl;i++){
classqq=classqqs[i];
if(classqq!=NULL){
if(fabs(classqq->gl-gamln(classqq->val+eta*25))>0.00001){
printf("h::%d,%d,%f,%f\n",i,classqq->val,classqq->gl,gamln(classqq->val+eta*25));
}
p=classqq->down;
while(p!=NULL){
if(fabs(p->gl-gamln(p->val,p->val+eta,4))>0.00001){
printf("d::%d,%d,%d,%f,%f\n",p->row,p->col,p->val,p->gl,gamln(p->val,p->val+eta,4));
}
p=p->down;
}
}
}
}
*/

#endif
