// Dijkstra          -> O(E log V)    / Worst Case -> O(V^2 logV)    -> O( e + v log v)
// Dijkstra all pair -> O(V(E log V)) / Worst Case -> O(V^3 logV)
// Bellman-Ford      -> O(V^2 E)      / Worst Case -> O(V^4) 
// Floyd–Warshall    -> O(V^3)

#include <iostream>
#include <climits>
#include <vector>
#include <list>
using namespace std;

/*********************************************************************************************/
void connectVertices(vector<int> vec[],int s,int d){
	vec[s].push_back(d);
	vec[d].push_back(s);
}

void BFS_Helper(vector<int> vec[], int n, vector<bool> & visited, int i){
	
	list<int> visitedQueue;
	visitedQueue.push_back(i);
	visited[i] = true;

	while(visitedQueue.empty() == 0){
		i = visitedQueue.front();
		visitedQueue.pop_front();

		for(auto adj : vec[i]){
			if(visited[adj] == false){
				visitedQueue.push_back(adj);
				visited[adj] = true;
			}
		}
	}
}

int BFS(vector<int> vec[], int n){

	vector<bool> visited(n, false);
	int disconnectedComponents = 0;

	for(int i = 0; i < n; i++){
		if(visited[i] == false){
			BFS_Helper(vec, n, visited, i);
			disconnectedComponents++;
		}
	}
	return disconnectedComponents;
}
/*********************************************************************************************/
void printVector(const vector<vector<int>> & weight){  //(&weight)[N][N]
	for(auto vec : weight){
		for(auto w : vec){
			if(w == INT_MAX) cout << "    " << "INF";
			else cout << "    " << w;
		}
		cout << endl;
	}
}

void printPath_Helper(const vector<vector<int>> & path, int i, int j){
	int n = path.size();
	if (path[i][j] == i) return;

	printPath_Helper(path, i, path[i][j]);
	cout << path[i][j] << "->";
}

void printPath(const vector<vector<int>> & path){

	int n = path.size();
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			if (i != j && path[i][j] != -1){
				cout << "Shortest Path between " << i << "-" << j << " : "\
				<< i << "->"; printPath_Helper(path, i, j); cout << j << endl;
			}
		}
	}
}

void floydWarshall(vector<vector<int>> & weight){  

	int n = weight.size();
	vector<vector<int>> path(n, vector<int>(n, 0));
  
    for (int i = 0; i < n; i++){ 
        for (int j = 0; j < n; j++){

			if(i == j) path[i][j] = 0;
			else if(weight[i][j] != INT_MAX) path[i][j] = i;
			else path[i][j] = -1;
		}
	}          

    for (int k = 0; k < n; k++){
        for (int i = 0; i < n; i++){  
            for (int j = 0; j < n; j++){

				if (weight[i][k] == INT_MAX || weight[k][j] == INT_MAX) continue;

				int intermediateWeight = weight[i][k] + weight[k][j];
                if (intermediateWeight < weight[i][j]){
					weight[i][j] = intermediateWeight;
					path[i][j]   = path[k][j];
				}
            }  
        } 
    }
	//printVector(weight);
	//printPath(path);
}

void scoreCalculation(vector<vector<int>> & weight, double*& scores){
	int n = weight.size();
	int shortest = 0, shortestWrt_Node = 0;
	double score = 0;

	for(int k = 0; k < n; k++){
		score = 0;
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				if(k == i || k == j) continue;
				if(weight[i][j] == INT_MAX) continue;
				if(weight[i][k] == INT_MAX || weight[k][j] == INT_MAX) continue;

				if(i == j) shortest = 1;
				else shortest = weight[i][j];
				shortestWrt_Node = weight[i][k] + weight[k][j];
				score += shortestWrt_Node / double(shortest);
			}
		}
		scores[k] = score;
	}

}
/*********************************************************************************************/

int main(){

	//int** arr = new int*[n];
	//for(int i = 0; i < n; i++) arr[i] = new int[n];

	int n = 5;
	double* scores = new double[n];
	// 59 58.9 43 38.6667 75.4
	// return 1
/*
	0    5    2    3    3
    5    0    3    2    3
    2    3    0    1    5
    3    2    1    0    4
    3    3    5    4    0
*/
/*
	Shortest Path from vertex 0 to vertex 1 is (0 2 3 1)
	Shortest Path from vertex 0 to vertex 2 is (0 2)
	Shortest Path from vertex 0 to vertex 3 is (0 2 3)
	Shortest Path from vertex 0 to vertex 4 is (0 4)
	Shortest Path from vertex 1 to vertex 0 is (1 3 2 0)
	Shortest Path from vertex 1 to vertex 2 is (1 3 2)
	Shortest Path from vertex 1 to vertex 3 is (1 3)
	Shortest Path from vertex 1 to vertex 4 is (1 4)
	Shortest Path from vertex 2 to vertex 0 is (2 0)
	Shortest Path from vertex 2 to vertex 1 is (2 3 1)
	Shortest Path from vertex 2 to vertex 3 is (2 3)
	Shortest Path from vertex 2 to vertex 4 is (2 0 4)
	Shortest Path from vertex 3 to vertex 0 is (3 2 0)
	Shortest Path from vertex 3 to vertex 1 is (3 1)
	Shortest Path from vertex 3 to vertex 2 is (3 2)
	Shortest Path from vertex 3 to vertex 4 is (3 4)
	Shortest Path from vertex 4 to vertex 0 is (4 0)
	Shortest Path from vertex 4 to vertex 1 is (4 1)
	Shortest Path from vertex 4 to vertex 2 is (4 0 2)
	Shortest Path from vertex 4 to vertex 3 is (4 3)
*/
	int input1[n][n] = {  
		{0, 0, 2, 5, 3},
		{0, 0, 0, 2, 3},
		{2, 0, 0, 1, 0}, 
		{5, 2, 1, 0, 4},
		{3, 3, 0, 4, 0} 
	};	
	// 12.5, 12.0, 24.0, 21.0, 18.67, 16.0
	// return 1
	/* int input2[n][n] = { 
		{0, 0, 0, 3, 0, 2},
		{0, 0, 3, 0, 2, 0},
		{0, 3, 0, 0, 0, 0},
		{3, 0, 0, 0, 0, 4},
		{0, 2, 0, 0, 0, 0},
		{2, 0, 0, 4, 0, 0} 
	}; */

	vector<vector<int>> weight(n, vector<int>(n, 0));
	vector<int> adj[n];
	
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){

			int curr = input1[i][j];
			if(curr != 0) connectVertices(adj,i,j);		
			if(curr == 0 && i != j) curr = INT_MAX;
			weight[i][j] = curr;
			
		}
	}
	floydWarshall(weight);

	printVector(weight);

	scoreCalculation(weight, scores);

	for(int i = 0; i < n; i++){
		cout << scores[i] <<  " ";
	}
	cout << endl;

	//int disconnectedComponent = BFS(adj, n);
	//cout << disconnectedComponent << endl;

    return 0;
}  