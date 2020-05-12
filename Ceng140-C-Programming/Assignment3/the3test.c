#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef
    struct vertex
    {   char tag; 
        char *label; 
        struct vertex *edge[1]; }
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

vp copyVertex(vp ver);

pque createQue( vp cpvertex){
    pque newNode = (pque)malloc(sizeof(queue));    
	DATA(newNode)=cpvertex;
    NEXT(newNode) = NULL;    
    return newNode;
}

void  enqueue(vp ver,pque * front,pque * end){
    vp cpvertex;
    cpvertex=copyVertex(ver);
    pque newNode=createQue(cpvertex);   

    if(*front==NULL && *end==NULL)
    {
        *front=newNode;
        *end=newNode;
        return;         
    } 
	  
    NEXT(*end)=newNode;
    *end=newNode;       
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

/*************************************************************************/

vp newVertex(char *label,int edgeNumber){
    vp ver = malloc(sizeof(vertex) + (sizeof(vp)*(edgeNumber+1)));   /*edge saysini bulmak lazim*/
    LABEL(ver)  = label;
    TAG(ver) = '0';
    return ver;
}

vp copyVertex(vp ver){
    int i=0;
    vp new=(vp)malloc(sizeof(vertex));
    TAG(new)=TAG(ver);
    LABEL(new)=strdup(LABEL(ver));
    EDGE(new)[0]=NULL;
    return new;
}

void newEdge(vp ver, vp edge, int i){
	EDGE(ver)[i] = edge;
}


void printGraph(vp node){
	int i;
	if(TAG(node) == '1') return;
	TAG(node) = '1';
	printf("%s => ",LABEL(node));
	for(i=0;EDGE(node)[i];i++)  printf("%s ",LABEL(EDGE(node)[i]));
    i=0;
	printf("\n");
	for(i=0;EDGE(node)[i];i++)  printGraph(EDGE(node)[i]);
} 

void bfs(vp node,pque * front,pque * end){
	int i;
	if(TAG(node) == '1') return;
	TAG(node) = '1';
	printf("%s => ",LABEL(node));
	for(i=0;EDGE(node)[i];i++)  printf("%s ",LABEL(EDGE(node)[i]));
    i=0;
	printf("\n");
	enqueue(node,front,end);
	for(i=0;EDGE(node)[i];i++){
		bfs(EDGE(node)[i],front,end);
	}	
}



int main(){
	pque front=NULL,end=NULL;

	vp supernode = newVertex("burhan",3);
	vp makbule = newVertex("makbule",2);
	vp sahika = newVertex("sahika",1);
	vp sacit = newVertex("sacit",1);
	vp sertac = newVertex("sertac",1);

	vp supernode2 = newVertex("makbule",2);
	vp cem = newVertex("cem",0);
	vp burhan = newVertex("burhan",1);
	vp osman = newVertex("osman",2);
	vp asli = newVertex("asli",2);
	vp sahika2 = newVertex("sahika",1);

    newEdge(supernode,makbule,0);
	newEdge(supernode,sacit,1);
	newEdge(supernode,sahika,2);

	newEdge(makbule,supernode,0);
	newEdge(makbule,sahika,1);

	newEdge(sacit,sertac,0);

	newEdge(sertac,sacit,0);

	newEdge(sahika,sacit,0);

 /*********************************************/

	newEdge(supernode2,burhan,0);
	newEdge(supernode2,sahika2,1);

	newEdge(burhan,asli,0);

	newEdge(asli,cem,0);
	newEdge(asli,osman,1);

	newEdge(osman,asli,0);
	newEdge(osman,sahika2,1);

	newEdge(sahika2,osman,0);
/*
    printGraph(supernode);
    printf("\n");
    printGraph(supernode2);
	printf("\n");  

	printf("Queue\n");  */
	bfs(supernode,&front,&end);
	printQue(front); 

    return 0;
}
