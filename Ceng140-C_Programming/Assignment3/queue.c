#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct queue{
    char * data;
    struct queue *next;
} queue,*pque;

#define DATA(pque) ((pque)->data)
#define NEXT(pque) ((pque)->next)

pque createQue( char * str){
    pque newNode = (pque)malloc(sizeof(queue));
    
	DATA(newNode)=strdup(str);
    /*DATA(newNode)=str; */
    NEXT(newNode) = NULL;    
    return newNode;
}

void  enqueue(char * str,pque * front,pque * rear){
    
    pque newNode=createQue(str);


    if(*front==NULL && *rear==NULL)
    {
        *front=newNode;
        *rear=newNode;
        return;         
    } 
	  
    NEXT(*rear)=newNode;
    *rear=newNode;       
}

void dequeue(pque * front){
    pque ori=*front;
    pque temp=NEXT(ori);
    free(ori);
    *front=temp;

}

void printFront(pque front){
    printf("%s\n",DATA(front));
}

void printQue(pque front){
    pque curr=front;
    
    while(curr)
    {
        printf("%s ",DATA(curr));
	    curr=NEXT(curr);
    }
    printf("\n");
}



int main(){

    pque front=NULL,end=NULL;
    char * str1="ali";
    char * str2="ilker";    
    enqueue(str1,&front,&end);
    enqueue(str2,&front,&end);
    printQue(front); 
    printFront(front);
    dequeue(&front);
    printQue(front); 




    return 0;
}