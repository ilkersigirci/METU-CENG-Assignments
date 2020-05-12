#include "linkedList.h"

/* Functions will be implemented here */

void printList(Node *head){
    while(head!=NULL){
        printf("%d",head->data);
        if(head->next!=NULL) printf("->");
        head=head->next;
    }
    printf("\n");    
}

void insertEnd(Node** list, int data){
    
    Node *curr=*list;
    Node *new_node=(Node *)malloc(sizeof(Node));
    new_node->data=data;
    new_node->next=NULL;
    if((*list)==NULL) *list=new_node;
    while(curr->next!=NULL){
         curr=curr->next;
    }
    curr->next=new_node;    
}

int occurrences(Node *head, int value){
    Node * curr=head;
    int seen=0;
    while(curr){
        if(curr->data==value){
            seen++;
        }
        curr=curr->next;
    }

    return seen;
}

Node* removeNode(Node *head, int index){
    Node * curr=head;
    Node * temp;
    int i=0;
    if(index==0){
        curr=head->next;
        head->next=NULL;
        free(head);
        head=curr;
        return head;
    }
    for(i=0;i<index-1;i++){
        curr=curr->next;
    }
    temp=curr->next;
    curr->next=temp->next;
    temp->next=NULL;
    free(temp);
    return head;
}

Node* mergeLists(Node *list1, Node *list2){
    Node * new=NULL;
    Node * curr1=list1;
    Node * curr2=list2;

    
    while(curr1 && curr2){

        insertEnd(&new,curr1->data);
        insertEnd(&new,curr2->data);
        curr1=curr1->next;
        curr2=curr2->next;
    }
    if(!curr1){
        while(curr2){
            insertEnd(&new,curr2->data);
            curr2=curr2->next;
        }
    }
    if(!curr2){
        while(curr1){
            insertEnd(&new,curr1->data);
            curr1=curr1->next;
        }
    }   

    return new;
}

Node* reverse(Node *head){
    int size=0,i=0;
    int arr[20]={0};
    Node * curr=head;

    for(i=0;curr;i++){
        arr[i]=curr->data;
        curr=curr->next;  
    }size=i;
    
    curr=head;
    for(i=size-1;curr;i--){
        curr->data=arr[i];
        curr=curr->next;      
    }     
    return head;
}