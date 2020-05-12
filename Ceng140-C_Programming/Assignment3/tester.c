#include "the3.h"
#include <stdio.h>
#include <stdlib.h>
vp make_vertex(char *label, int edge_n){
	vp new_node = calloc(1,sizeof(vertex) + (sizeof(vp)*(edge_n+1)));
	LABEL(new_node)  = label;
	TAG(new_node) = '0';
	return new_node;
}
void newEdge(vp base, vp edge, int i){
	EDGE(base)[i] = edge;
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

int main(){
	vp result = NULL;
	vp supernode = make_vertex("burhan",3);
	vp makbule = make_vertex("makbule",2);
	vp sahika = make_vertex("sahika",1);
	vp sacit = make_vertex("sacit",1);
	vp sertac = make_vertex("sertac",1);

	vp supernode2 = make_vertex("makbule",2);
	vp cem = make_vertex("cem",0);
	vp burhan = make_vertex("burhan",1);
	vp osman = make_vertex("osman",2);
	vp asli = make_vertex("asli",2);
	vp sahika2 = make_vertex("sahika",1);

	newEdge(supernode,makbule,0);
	newEdge(supernode,sacit,1);
	newEdge(supernode,sahika,2);

	newEdge(makbule,supernode,0);
	newEdge(makbule,sahika,1);

	newEdge(sacit,sertac,0);

	newEdge(sertac,sacit,0);

	newEdge(sahika,sacit,0);

	newEdge(supernode2,burhan,0);
	newEdge(supernode2,sahika2,1);

	newEdge(burhan,asli,0);

	newEdge(asli,cem,0);
	newEdge(asli,osman,1);

	newEdge(osman,asli,0);
	newEdge(osman,sahika2,1);

	newEdge(sahika2,osman,0);

	printGraph(supernode);

	return 0;
}