#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"

int main(){
    
    Node *list1 = NULL;
	Node *list2 = NULL;
	Node *merged;

	insertEnd(&list1, 1);
	insertEnd(&list1, 2);
	insertEnd(&list1, 3);
	insertEnd(&list1, 4);
	insertEnd(&list1, 5);

	insertEnd(&list2, 2);
	insertEnd(&list2, 4);
	insertEnd(&list2, 6);
	
	printf("List1: ");
	printList(list1);
	
	printf("List2: ");
	printList(list2);
    
    printf("#occurence of 4: %d\n", occurrences(list1, 4));

    list1 = removeNode(list1, 1);
    list1 = removeNode(list1, 2);
    printf("After removal: ");
    printList(list1);

    merged = mergeLists(list1, list2);
    printf("Merged: ");
    printList(merged);

    printf("Reversed of list2: ");
    printList(reverse(list2));

    return 0;
}