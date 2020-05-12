#include <stdio.h>
#include <stdlib.h>

void bareiss(int numMatrix[][6],int nextMatrix[][6],int row,int col,int pivIndex,int prevPiv){

    int i=0,j=0,pivot=numMatrix[pivIndex][pivIndex];    
    
    for(i=0;i<row;i++){
        if(i==pivIndex){
            for(j=0;j<col;j++){
            nextMatrix[i][j]=numMatrix[i][j];
            }
            continue;
        } 
        for(j=0;j<col;j++){
            nextMatrix[i][j]=(pivot*numMatrix[i][j]
            -numMatrix[i][pivIndex]*numMatrix[pivIndex][j])/prevPiv;
        } 
    }  /*
    printf("NUM\n");
    for(i=0;i<row;i++){
        for(j=0;j<col;j++){            
            printf("%d \t",numMatrix[i][j]);
        }
        printf("\n");
    }
    printf("--------------------------------------------\n");

    printf("Next\n");
    for(i=0;i<row;i++){
        for(j=0;j<col;j++){
            printf("%d \t",nextMatrix[i][j]);
        }
        printf("\n");
    }   */

     
    if(pivIndex<row){
        bareiss(nextMatrix,numMatrix,row,col,pivIndex+1,numMatrix[pivIndex][pivIndex]);
    } 
          
    
}  

int main(){

    int i=0,j=0,row=5,col=6;


    int numMatrix[5][6]={{3,8,1,-12,-4,-2},{1,0,0,-1,0,0},
    {4,4,3,-40,-3,-1},{0,2,1,-3,-2,0},{0,1,0,-12,0,0}};

    int nextMatrix[5][6]={{3,8,1,-12,-4,-2},{1,0,0,-1,0,0},
    {4,4,3,-40,-3,-1},{0,2,1,-3,-2,0},{0,1,0,-12,0,0}};    

    bareiss(numMatrix,nextMatrix,row,col,0,1);     


    for(i=0;i<row;i++){
        for(j=0;j<col;j++){
            printf("%d \t",nextMatrix[i][j]);
        }
        printf("\n");
    }
    /*
     printf("--------------------------------------------\n");

    for(i=0;i<row;i++){
        for(j=0;j<col;j++){
            printf("%d \t",nextMatrix[i][j]);
        }
        printf("\n");
    }    */

    return 0;
}