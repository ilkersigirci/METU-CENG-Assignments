#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>
#include <cassert>
#include "the3.h"
#include <chrono>
using namespace std;

int Important (int n, int**& edgeList, double*& scores);

void printVector(std::vector<int>& array){

		std::cout << "size: " << array.size() << std::endl;
		for (unsigned i = 0; i < array.size(); ++i){
				std::cout << array[i] << " ";
		}
		std::cout << std::endl;
}

bool TestTask()
{
		
	// time variables
	//clock_t begin;
	//clock_t end;
	double duration;
	int expectedTime = 500;
	int true_answer = -1;
	int solution = -1;

	// generate solution

	int n = 6;
	double* scores = new double[n];
	int** edgeList = new int*[n];
	for(int i = 0; i < n; i++) edgeList[i] = new int[n];

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
         edgeList[i][j] = input2[i][j];
      }
   }

	/* if ((begin = clock ()) == -1) 
		std::cerr << "clock err" << std::endl; */
	
	auto begin = chrono::steady_clock::now();
	solution = Important (n, edgeList, scores);
	auto end = chrono::steady_clock::now();

	/* if ((end = clock ()) == -1) 
		std::cerr << "clock err" << std::endl; */
			
	//duration = ((double)end-begin) / CLOCKS_PER_SEC * 1000000;
	//duration = (end - begin) / (double) CLOCKS_PER_SEC;
	//duration *= 1000;
	//cout << begin << " " << end << endl;
	//cout << "Elapsed time  " << duration << " vs " << expectedTime << " microsecs" << std::endl;

	cout << "Elapsed time in microseconds : " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << " µs" << endl;

	/*for(int i = 0; i < n; i++){
		cout << scores[i] <<  " ";
	}
	cout << endl;*/


	return (solution == true_answer);
}

int main()
{
	srandom(time(0));       // no need to initialize second time

	if (TestTask())
		std::cout << "PASSED TASK" << std::endl << std::endl;
	else
		std::cout << "FAILED TASK" << std::endl << std::endl;
	

	return 0;
}
