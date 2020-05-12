// C program for Finite Automata Pattern searching 
// Algorithm 
#include<stdio.h> 
#include<string.h> 
#define NO_OF_CHARS 256 

int getNextState(char *pat, int M, int state, int x) 
{ 
	// If the character c is same as next character 
	// in pattern,then simply increment state 
	if (state < M && x == pat[state]) 
		return state+1; 

	// ns stores the result which is next state 
	int ns, i; 

	// ns finally contains the longest prefix 
	// which is also suffix in "pat[0..state-1]c" 

	// Start from the largest possible value 
	// and stop when you find a prefix which 
	// is also suffix 
	for (ns = state; ns > 0; ns--) 
	{ 
		if (pat[ns-1] == x) 
		{ 
			for (i = 0; i < ns-1; i++) 
				if (pat[i] != pat[state-ns+1+i]) 
					break; 
			if (i == ns-1) 
				return ns; 
		} 
	} 

	return 0; 
} 

/* This function builds the TF table which represents4 
	Finite Automata for a given pattern */
void computeTF(char *pat, int M, int TF[][NO_OF_CHARS]) 
{ 
	int state, x; 
	for (state = 0; state <= M; ++state) 
		for (x = 0; x < NO_OF_CHARS; ++x) 
			TF[state][x] = getNextState(pat, M, state, x); 
} 

/* Prints all occurrences of pat in txt */
void search(char *pat, char *txt) 
{ 
	int M = strlen(pat); 
	int N = strlen(txt); 

	int TF[M+1][NO_OF_CHARS]; 

	computeTF(pat, M, TF); 

	// Process txt over FA. 
	int i, state=0; 
	for (i = 0; i < N; i++) 
	{ 
		state = TF[state][txt[i]]; 
		if (state == M) 
			printf ("\n Pattern found at index %d", 
										i-M+1); 
	} 
} 

// Driver program to test above function 
int main() 
{ 
	char *txt = "AABAACAADAABAAABAA"; 
	char *pat = "AABA"; 
	search(pat, txt); 
	return 0; 
} 
/****************************************************************************************/

// Efficient Solution 

#include <bits/stdc++.h> 
using namespace std; 
#define NO_OF_CHARS 256 
  
/* This function builds the TF table  
which represents Finite Automata for a  
given pattern */
void computeTransFun(char* pat, int M, int TF[][NO_OF_CHARS]) 
{ 
    int i, lps = 0, x; 
  
    // Fill entries in first row 
    for (x = 0; x < NO_OF_CHARS; x++) 
        TF[0][x] = 0; 
    TF[0][pat[0]] = 1; 
  
    // Fill entries in other rows 
    for (i = 1; i <= M; i++) { 
        // Copy values from row at index lps 
        for (x = 0; x < NO_OF_CHARS; x++) 
            TF[i][x] = TF[lps][x]; 
  
        // Update the entry corresponding to this character 
        TF[i][pat[i]] = i + 1; 
  
        // Update lps for next row to be filled 
        if (i < M) 
            lps = TF[lps][pat[i]]; 
    } 
} 
  
/* Prints all occurrences of pat in txt */
void search(char pat[], char txt[]) 
{ 
    int M = strlen(pat); 
    int N = strlen(txt); 
  
    int TF[M + 1][NO_OF_CHARS]; 
  
    computeTransFun(pat, M, TF); 
  
    // process text over FA. 
    int i, j = 0; 
    for (i = 0; i < N; i++) { 
        j = TF[j][txt[i]]; 
        if (j == M) { 
            cout << "pattern found at index " << i - M + 1 << endl; 
        } 
    } 
} 
  
/* Driver code */
int main() 
{ 
    char txt[] = "GEEKS FOR GEEKS"; 
    char pat[] = "GEEKS"; 
    search(pat, txt); 
    return 0; 
} 