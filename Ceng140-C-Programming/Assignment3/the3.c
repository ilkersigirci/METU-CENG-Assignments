#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef
    struct vertex
    {   char tag; 
        char *label; 
        struct vertex *edge[4]; }
    vertex, *vp;

#define TAG(vp) ((vp)->tag) 
#define LABEL(vp) ((vp)->label) 
#define EDGE(vp) ((vp)->edge)


vp merge(vp graph1, vp graph2);

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
void search(vp supernode){
    
} 

int main(){
    
    vp p0=NULL,p1=NULL,p2=NULL,p3=NULL,p4=NULL;  /*all are pointer*/    
    p0=newVertex(p0),p1=newVertex(p1),p2=newVertex(p2);
    p3=newVertex(p3),p4=newVertex(p4);


    TAG(p0)='0',TAG(p1)='0',TAG(p2)='0',TAG(p3)='0',TAG(p4)='0';
    LABEL(p0)="burhan",LABEL(p1)="makbule",LABEL(p2)="sacit";
    LABEL(p3)="sahika",LABEL(p4)="sertac";
    EDGE(p0)[0]=p1,EDGE(p0)[1]=p2,EDGE(p0)[2]=p3;EDGE(p0)[3]=NULL;
    EDGE(p1)[0]=p0,EDGE(p1)[1]=p3;EDGE(p1)[2]=NULL;
    EDGE(p2)[0]=p4;EDGE(p2)[1]=NULL;
    EDGE(p3)[0]=p2;EDGE(p3)[1]=NULL;
    EDGE(p4)[0]=p2;EDGE(p4)[1]=NULL;



   /*      
    printf("%s\n",LABEL(p));
    printf("%s\n",LABEL(EDGE(p)[0]));
    printf("%c\n",TAG(p1));
    printf("%s\n",LABEL(EDGE(p)[1]));
    printf("%s\n",LABEL(EDGE(p)[2]));  */

    printGraph(p0);
    printGraph(p1);
    printGraph(p2);
    printGraph(p3);
    printGraph(p4);
    free(p0);
    free(p1);
    free(p2);
    free(p3);
    free(p4);








    return 0;
}
