#include <stdio.h>
#include <string.h>
// gcc -o test_fn test_fn.c

//./test_fn 0_1_2_1
int main(int argc, char* argv[]) {
    FILE *file;
   
    char loc[100], loc_fn[100];
    strcpy(loc, "./test/goodbar_");
    strcat(loc, argv[1]);

    memcpy(loc_fn,loc,sizeof(char)*24);
    strcat(loc_fn, "/gamln.txt");

    printf("location:  %s,%s\n", loc,loc_fn);
    file = fopen(loc_fn, "r" );
    int ii,ff;
    double gamln_0[10];
    for(ii=0; ii<10; ii++) {
        ff=fscanf( file, "%lf", &gamln_0[ii]);
        printf("read %d, %f \n",ii, gamln_0[ii]);
    }
    fclose(file);


}
