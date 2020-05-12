// Dijkstra          -> O(E log V)    / Worst Case -> O(V^2 logV)    -> O( e + v log v)
// Dijkstra all pair -> O(V(E log V)) / Worst Case -> O(V^3 logV)
// Bellman-Ford      -> O(V^2 E)      / Worst Case -> O(V^4) 
// Floyd–Warshall    -> O(V^3)

#include <iostream>
#include <climits>
using namespace std;

#define INF 9999

void printMatrix(int n, int** dist)  //(&dist)[N][N]
{
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if (dist[i][j] == INF)	cout << "    " << "INF";                
			else cout << "    " << dist[i][j];
		}
		cout << endl;
	} 
}

void floydWarshall (int n, int** graph)
{  
    //int dist[n][n];
	int** dist = new int*[n];
	for(int i = 0; i < n; i++) dist[i] = new int[n];

  
    for (int i = 0; i < n; i++){ 
        for (int j = 0; j < n; j++){
			int curr = graph[i][j];
			if(curr == 0 && i != j) curr = INF;
			dist[i][j] = curr;
		}
	}          

    for (int k = 0; k < n; k++){
        for (int i = 0; i < n; i++){  
            for (int j = 0; j < n; j++){
				int intermediateWeight = dist[i][k] + dist[k][j];
                if (intermediateWeight < dist[i][j]){
					dist[i][j] = intermediateWeight;
				}
            }  
        } 
    }
    printMatrix(n, dist);
}  

int main()  
{
	int n = 5;
    /* int graph[n][n] = { 
		{0, 5, INF, 10},  
		{INF, 0, 3, INF},  
		{INF, INF, 0, 1},  
		{INF, INF, INF, 0}  
	}; */

	/* int input2[n][n] = { 
		{0, 0, 0, 3, 0, 2},
		{0, 0, 3, 0, 2, 0},
		{0, 3, 0, 0, 0, 0},
		{3, 0, 0, 0, 0, 4},
		{0, 2, 0, 0, 0, 0},
		{2, 0, 0, 4, 0, 0} 
	}; */

	//first example scores -> 59 58.9 43 38.6667 75.4
	// return 1

	/*
	0    5    2    3    3
    5    0    3    2    3
    2    3    0    1    5
    3    2    1    0    4
    3    3    5    4    0
	*/
	int input1[n][n] = {  
		{0, 0, 2, 5, 3},
		{0, 0, 0, 2, 3},
		{2, 0, 0, 1, 0}, 
		{5, 2, 1, 0, 4},
		{3, 3, 0, 4, 0} 
	};	

	int** arr = new int*[n];
	for(int i = 0; i < n; i++) arr[i] = new int[n];

	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++){
			arr[i][j] = input1[i][j];
		}
	}
    floydWarshall(n, arr);
    return 0;
}  