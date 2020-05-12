#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node * next;
};

typedef struct node Node;

void addbetween(struct node * prev ,int value){
    struct node * new_node=(struct node *)malloc(sizeof(struct node));
    new_node->data=value;
    new_node->next=prev->next;        
    prev->next=new_node;
}

void addend(struct node * head,int value){
    struct node * new_node=(struct node *)malloc(sizeof(struct node));
    struct node * temp;
    temp=head;

    while(temp->next!=NULL){
        temp=temp->next;
    }
    new_node->data=value;
    temp->next=new_node;
    new_node->next=NULL;
}

void delnode(struct node ** head,int index){

    struct node * curr;
    struct node * temp;

    if(index==0){  
        curr=(*head)->next;
        (*head)->next=NULL;
        free(*head);
        *head=curr;
    }
} 

void printll(struct node *head){
    while(head!=NULL){
        printf("%d ",head->data);
        head=head->next;
    }
    printf("\n");
}  


int main(){

    struct node * head=(struct node *)malloc(sizeof(struct node));
    struct node * el1=(struct node *)malloc(sizeof(struct node));
    struct node * el2=(struct node *)malloc(sizeof(struct node));

    head->data=7;
    head->next=el1;

    el1->data=8;
    el1->next=el2;

    el2->data=9;
    el2->next=NULL;




    return 0;
}