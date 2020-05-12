#include <stdio.h>
#include <stdlib.h>
#include "exam_3_0.h"
#include "memoryCheck.h"

#define malloc __labMalloc__
#define calloc __labCalloc__
#define realloc __labRealloc__
#define free __labFree__

/*
	returns number of characters in a string
	returns 0 if string is NULL
*/
int getStringLength(char* string) {
	int i = 0;

	if (string == NULL) {
		return 0;
	}
	else {
		while (string[i] != '\0') {
			i++;
		}

		return i;
	}
}

/*
	returns 1 if strings are equal or both strings are NULL
	returns 0 if strings are not equal
*/
int areEqualStrings(char* string1, char* string2) {
	int i = 0;

	if (string1 == NULL && string2 == NULL) {
		return 1;
	}
	else if (getStringLength(string1) != getStringLength(string2)) {
		return 0;
	}
	else {
		while (string1[i] != '\0') {
			if (string1[i] != string2[i]) {
				return 0;
			}

			i++;
		}

		return 1;
	}
}

/* prints DNA or RNA */
void printGenes(char** dnaOrRna) {
	int i = 0;

	if (dnaOrRna == NULL) {
		printf("No genes found.\n");
	}
	else {
		/* while current gene is not NULL, print gene */
		while (dnaOrRna[i] != NULL) {
			/* if next gene is not NULL, print with space */
			if (dnaOrRna[i+1] != NULL) {
				printf("%s ", dnaOrRna[i]);
			}
			/* if next gene is NULL, print without space */
			else {
				printf("%s", dnaOrRna[i]);
			}

			i++;
		}
		/* print additional newline */
		printf("\n");
	}
}

/* returns complement nucleotide of given nucleotide for DNA */
char complementForDNA(char nucleotide) {
	switch (nucleotide) {
		case 'A':
			return 'T';
		case 'T':
			return 'A';
		case 'G':
			return 'C';
		case 'C':
			return 'G';
		default:
			return '?';
	}
}

/*
	returns complement nucleotide of given nucleotide for RNA
	fromDNA should be 1 if RNA is generated from DNA
	fromDNA should be 0 if RNA is generated (complemented) from RNA
*/
char complementForRNA(char nucleotide, int fromDNA) {
	if (fromDNA) {
		switch (nucleotide) {
			case 'A':
				return 'U';
			case 'T':
				return 'A';
			case 'G':
				return 'C';
			case 'C':
				return 'G';
			default:
				return '?';
		}
	}
	else {
		switch (nucleotide) {
			case 'A':
				return 'U';
			case 'U':
				return 'A';
			case 'G':
				return 'C';
			case 'C':
				return 'G';
			default:
				return '?';
		}
	}
}

/* DON'T TOUCH THE CODE ABOVE, INCLUDING THIS LINE. YOUR IMPLEMENTATIONS MAY START BELOW THIS LINE. */

char **generateDNA(char* dnaString){
	char **dna;
	int i,j,length;
	length=getStringLength(dnaString);

	if(!length) return NULL;

	dna=(char **)malloc(sizeof(char *)*(length/3+1));
	for(i=0;i<length/3;i++){
		dna[i]=(char *)malloc(sizeof(char)*3);
		for(j=0;j<3;j++){
			dna[i][j]=*dnaString++;
		}
	}
	return dna;
}
char** complementDNA(char** dna){
	char **compDna;
	int i,j,row=0;

	if(!dna) return dna;
	for(i=0;dna[i];i++) row++;

	compDna=(char **)malloc(sizeof(char *)*row);

	for(i=0;i<row;i++){
		compDna[i]=(char *)malloc(sizeof(char)*3);
		for(j=0;j<3;j++){
			compDna[i][j]=complementForDNA(dna[i][j]);
		}
	}
	return compDna;
}
int crossover(char** dna1, char** dna2, int crossoverIndex){
	int i,j,row;
	char *temp;

	if(!dna1 || !dna2) return -1;
	if(*dna1==*dna2) return -2;
	for(i=0;dna1[i];i++) row++;

	for(i=crossoverIndex;i<row;i++){
		temp=dna1[i];
		dna1[i]=dna2[i];
		dna2[i]=temp;
	}
	return 0;
}
