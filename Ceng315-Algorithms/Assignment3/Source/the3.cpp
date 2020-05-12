#include "the3.h"

// You  can define extra functions here



// INPUT :
//            n         : number of nodes in the graph
//            edgeList  : edges in the graph
//            scores    : importance scores
// return value : 
//                 number of disconnected components

using namespace std;

/*********************************************************************************************/
void connectVertices(vector<int> vec[],int s,int d){
	vec[s].push_back(d);
	vec[d].push_back(s);
}

void BFS_Helper(vector<int> vec[], int n, vector<bool> & visited, int i){
	
	queue<int> visitedQueue;
	visitedQueue.push(i);
	visited[i] = true;

	while(visitedQueue.empty() == 0){
		i = visitedQueue.front();
		visitedQueue.pop();

		for(auto adj : vec[i]){
			if(visited[adj] == false){
				visitedQueue.push(adj);
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
void printVector(const vector<vector<int>> & weight){
	for(auto vec : weight){
		for(auto w : vec){
			if(w == INT_MAX) cout << "    " << "INF";
			else cout << "    " << w;
		}
		cout << endl;
	}
}

void floydWarshall(vector<vector<int>> & weight){  

	int n = weight.size();        

    for (int k = 0; k < n; k++){
        for (int i = 0; i < n; i++){  
            for (int j = i; j < n; j++){

				if (weight[i][k] == INT_MAX || weight[k][j] == INT_MAX) continue;

				int intermediateWeight = weight[i][k] + weight[k][j];
                if (intermediateWeight < weight[i][j]){
					weight[i][j] = intermediateWeight;
					weight[j][i] = intermediateWeight;
				}
            }  
        } 
    }
	//printVector(weight);
}

void scoreCalculation(vector<vector<int>> & weight, double*& scores){
	int n = weight.size();
	int shortest = 0, shortestWrt_Node = 0;
	double score = 0;

	for(int k = 0; k < n; k++){
		score = 0;
		for(int i = 0; i < n; i++){
			for(int j = i; j < n; j++){
				if(k == i || k == j) continue;
				if(weight[i][j] == INT_MAX) continue;
				if(weight[i][k] == INT_MAX || weight[k][j] == INT_MAX) continue;

				if(i == j) shortest = 1;
				else shortest = weight[i][j];
				shortestWrt_Node = weight[i][k] + weight[k][j];
				if (i != j) shortestWrt_Node *= 2;
				score += shortestWrt_Node / double(shortest);
			}
		}
		scores[k] = score;
	}

}
/*********************************************************************************************/

int Important (int n, int**& edgeList, double*& scores){

	if(n == 0) return 0;

	vector<vector<int>> weight(n, vector<int>(n, 0));
	vector<int> adj[n];
	int disconnectedComponent = 0;
	
	for(int i = 0; i < n; i++){
		for(int j = i; j < n; j++){

			int curr = edgeList[i][j];
			if(curr != 0) connectVertices(adj,i,j);		
			if(curr == 0 && i != j) curr = INT_MAX;
			weight[i][j] = curr;			
			weight[j][i] = curr;			
		}
	}
	/*
	int infNum = 0;
	for(int i = 0; i < n; i++){
		for(int j = i; j < n; j++){
			if(weight[i][j] == INT_MAX) infNum++;
		}
	}
	disconnectedComponent = (infNum / n) + 1;
	*/
	floydWarshall(weight);
	scoreCalculation(weight, scores);
	disconnectedComponent = BFS(adj, n);
	
	return disconnectedComponent;
}
