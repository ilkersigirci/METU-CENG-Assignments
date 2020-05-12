#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef
    struct vertex
    {   char tag; 
        char *label; 
        struct vertex *edge[4]; }
    vertex, *vp;
    
typedef 
    struct queue
    {   vp data;
        struct queue *next;} 
    queue,*pque; 

#define TAG(vp) ((vp)->tag)
#define LABEL(vp) ((vp)->label) 
#define EDGE(vp) ((vp)->edge)
#define DATA(pque) ((pque)->data)
#define NEXT(pque) ((pque)->next)

vp copyVertex(vp ver){
    int i=0;
    vp new=(vp)malloc(sizeof(vertex));
    TAG(new)=TAG(ver);
    LABEL(new)=strdup(LABEL(ver));
    EDGE(new)[0]=NULL;
    return new;
}

pque createQue( vp cpvertex){
    pque newNode = (pque)malloc(sizeof(queue));    
	DATA(newNode)=cpvertex;
    NEXT(newNode) = NULL;    
    return newNode;
}

void  enqueue(vp ver,pque * front,pque * rear){
    vp cpvertex;
    cpvertex=copyVertex(ver);
    pque newNode=createQue(cpvertex);   

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
    printf("%s\n",LABEL(DATA(front)));
}

void printQue(pque front){
    pque curr=front;
    
    while(curr)
    {
        printf("%s ",LABEL(DATA(curr)));
	    curr=NEXT(curr);
    }
    printf("\n");
}
/* ----------------------->--------------------- */
vp newVertex(vp ver){
    ver=(vp)malloc(sizeof(vertex));
    return ver;
}

void printGraph(vp head){
    vp curr=head;
    int i=0;
    for(i=0;EDGE(curr)[i];i++){
        printf("%s ",LABEL(EDGE(curr)[i]));
    }
    printf("\n");
}


int main(){

    pque front=NULL,end=NULL;
    vp ver1=NULL,ver2=NULL;
    ver1=newVertex(ver1),ver2=newVertex(ver2);        

    TAG(ver1)='a',TAG(ver2)='b',
    LABEL(ver1)="burhan",LABEL(ver2)="makbule";
    EDGE(ver1)[0]=ver2;
    EDGE(ver2)[0]=ver1;

    enqueue(ver1,&front,&end);
    enqueue(ver2,&front,&end);
    printQue(front);
    dequeue(&front);
    printQue(front); 
  



    return 0;
}