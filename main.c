#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#ifndef max
	#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif

//the maximum weight
int Pmax;
//The maximum volume
int Vmax;
//the objects we should put in the knapsack
struct Object {
    int P;
    int V;
    int Value;
};

//The 3D solution of the KnapSack problem using the dynamic programming
int knapSackDP( struct Object objects[],int length){

    int i, j, k;
    int *** DPMatrix;
    int numVolum = (Vmax/10);

    //Creation of the 3D Dynamic Programming Matrix
    DPMatrix = (int***) malloc(sizeof(int**)*(length+1));
    for(i=0; i<=(length);i++) {
        DPMatrix[i] = (int**) malloc(sizeof(int*)*(numVolum+1));
         for(j=0; j<=numVolum;j++) {
            DPMatrix[i][j] = (int*) malloc(sizeof(int)*(Pmax+1));
         }
    }

    //filling the first line with 0s cuz in that case there is nothing in the knapsack
    for(i=0; i<=length;i++) {
        for(k=0; k<=Pmax;k++) {
            DPMatrix[i][0][k] = 0;
        }
    }

    for(j=0; j<=numVolum;j++) {
        for(k=0; k<=Pmax;k++) {
            DPMatrix[0][j][k] = 0;
        }
    }

    for(i=0; i<=length;i++) {
        for(j=0; j<=numVolum;j++) {
            DPMatrix[i][j][0] = 0;
        }
    }

    for(i=1; i<=length;i++) {
        for(j=1; j<=numVolum;j++) {
            for(k=1; k<=Pmax;k++) {
                // Over volumed or over weighted (impossible to exist)
                if(objects[i-1].V/10> j||objects[i-1].P> k){
                    DPMatrix [i][j][k] = DPMatrix [i-1] [j] [k];
                }
                // the case of a fit (we take the max of it existing or not)
                else DPMatrix [i][j][k] = max((DPMatrix [i-1] [j] [k]),(DPMatrix [i-1] [j-objects[i-1].V/10] [k-objects[i-1].P])+ objects[i-1].Value);
            }
        }
    }

    //returning th last case's content since it holds the maximum value
    return DPMatrix [length][numVolum][Pmax];
}


int main()
{
    printf("Enter the maximum Volume :");
    scanf("%d",&Vmax);
    fflush(stdin);
    printf("\nEnter the maximum Weight :");
    scanf("%d",&Pmax);


    // The Vmax = 50
    // The Pmax = 8
    // The expected result is 25
    struct Object objects[8];

        objects[0].P = 2;
        objects[0].V = 10;
        objects[0].Value = 6;

        objects[1].P = 3;
        objects[1].V = 20;
        objects[1].Value = 8;

        objects[2].P = 5;
        objects[2].V = 20;
        objects[2].Value = 14;

        objects[3].P = 2;
        objects[3].V = 10;
        objects[3].Value = 6;

        objects[4].P = 4;
        objects[4].V = 20;
        objects[4].Value = 13;

        objects[5].P = 6;
        objects[5].V = 30;
        objects[5].Value = 17;

        objects[6].P = 3;
        objects[6].V = 20;
        objects[6].Value = 10;

        objects[7].P = 3;
        objects[7].V = 20;
        objects[7].Value = 10;

        clock_t begin = clock();


        // for values under or eqal to 6 it works yet for 7 and above it doesn't
        int n= knapSackDP(objects, 8);

        clock_t end = clock();

        double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

        printf("The result of knapSack is :  %d", n);
        printf("\nThe result of knapSack were calculated in  :  %lf seconds", time_spent);

    return 0;
}