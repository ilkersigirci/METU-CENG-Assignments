#ifndef _EXAM_3_0_
#define _EXAM_3_0_

/****** THESE FUNCTIONS ARE ALREADY IMPLEMENTED ******/

/*
	returns number of characters in a string
	returns 0 if string is NULL
*/
int getStringLength(char* string);

/*
	returns 1 if strings are equal or both strings are NULL
	returns 0 if strings are not equal
*/
int areEqualStrings(char* string1, char* string2);

/* prints DNA or RNA */
void printGenes(char** dnaOrRna);

/* returns complement nucleotide of given nucleotide for DNA */
char complementForDNA(char nucleotide);

/*
	returns complement nucleotide of given nucleotide for RNA
	fromDNA should be 1 if RNA is generated from DNA
	fromDNA should be 0 if RNA is generated (complemented) from RNA
*/
char complementForRNA(char nucleotide, int fromDNA);

/****** YOU NEED TO IMPLEMENT BELOW FUNCTIONS ******/

/*
	generate DNA from dnaString
	when dnaString is NULL, return NULL and do nothing
	otherwise make sure that each part of the DNA has 3 nucleotides
	e.g.	if dnaString is AGCTTGAATCGGCCTTAATGTTTT
			then DNA is in this format: AGC TTG AAT CGG CCT TAA TGT TTT
*/
char** generateDNA(char* dnaString);

/*
	generate complemented DNA from DNA
	when DNA is NULL, return NULL and do nothing
	otherwise make sure that each part of the complemented DNA is has 3 nucleotides
	complement strategy: A -> T, T -> A, G -> C, C -> G
	e.g.	if DNA is AGC TTG AAT CGG CCT TAA TGT TTT
			then complemented DNA is in this format: TCG AAC TTA GCC GGA ATT ACA AAA
*/
char** complementDNA(char** dna);

/*
	apply crossover operation with two DNAs
	when either dna1 or dna2 is NULL, return -1 and do nothing
	when dna1 and dna2 are pointing same dna, return -2 and do nothing
	otherwise apply crossover considering given crossover index and return 0
	e.g.	dna1 before crossover with index 2: AGC TTG AAT CGG CCT TAA TGT TTT
			dna2 before crossover with index 2: AGC GGG CCC TTA AAG AGA GGG AAA

			dna1 after crossover with index 2: AGC TTG CCC TTA AAG AGA GGG AAA
			dna2 after crossover with index 2: AGC GGG AAT CGG CCT TAA TGT TTT
	IMPORTANT: YOU CAN ASSUME THAT BOTH DNA1 AND DNA2 HAVE IN SAME NUMBER OF GENES
*/
int crossover(char** dna1, char** dna2, int crossoverIndex);

#endif
