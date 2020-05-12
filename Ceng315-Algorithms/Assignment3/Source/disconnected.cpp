#include <iostream>
#include <climits>
#include <vector>
#include <list>

using namespace std;

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

int main(){
	int n = 6;
	/* int input1[n][n] = {  
		{0, 0, 2, 5, 3},
		{0, 0, 0, 2, 3},
		{2, 0, 0, 1, 0}, 
		{5, 2, 1, 0, 4},
		{3, 3, 0, 4, 0} 
	}; */
	int input2[n][n] = { 
		{0, 0, 0, 3, 0, 2},
		{0, 0, 3, 0, 2, 0},
		{0, 3, 0, 0, 0, 0},
		{3, 0, 0, 0, 0, 4},
		{0, 2, 0, 0, 0, 0},
		{2, 0, 0, 4, 0, 0}
	};

	vector<vector<int>> weight(n, vector<int>(n, 0));
	vector<int> adj[n];
	
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			int curr = input2[i][j];
			if(curr == 0 && i != j) curr = INT_MAX;
			weight[i][j] = curr;
			if(curr != INT_MAX) connectVertices(adj,i,j);
		}
	}
   //floydWarshall(weight);
	int disconnectedComponent = BFS(adj, n);
	cout << disconnectedComponent << endl;

    return 0;
}
