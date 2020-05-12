#include "the3.h"
using namespace std;


int Important (int n, int**& edgeList, double*& scores);

int main(){

	int n = 6;
	double* scores = new double[n];
	int** arr = new int*[n];
	for(int i = 0; i < n; i++) arr[i] = new int[n];

	// 59 58.9 43 38.6667 75.4, return 1
	/* int input1[n][n] = {  
		{0, 0, 2, 5, 3},
		{0, 0, 0, 2, 3},
		{2, 0, 0, 1, 0}, 
		{5, 2, 1, 0, 4},
		{3, 3, 0, 4, 0} 
	};	 */
	// 12.5, 12.0, 24.0, 21.0, 18.67, 16.0, return 2
	int input2[n][n] = { 
		{0, 0, 0, 3, 0, 2},
		{0, 0, 3, 0, 2, 0},
		{0, 3, 0, 0, 0, 0},
		{3, 0, 0, 0, 0, 4},
		{0, 2, 0, 0, 0, 0},
		{2, 0, 0, 4, 0, 0} 
	};   

   for(int i = 0; i < n; i++){
      for(int j = 0; j < n; j++){
         arr[i][j] = input2[i][j];
      }
   }

   int disconnectedComponent = Important(n, arr, scores);
   cout << disconnectedComponent << endl;

	for(int i = 0; i < n; i++){
		cout << scores[i] <<  " ";
	}
	cout << endl;

   return 0;
}  