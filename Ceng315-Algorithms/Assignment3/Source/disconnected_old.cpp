#include <iostream>
#include <climits>
#include <vector>
#include <list>
#define pb push_back

using namespace std;

void addEdge(vector<int> vec[],int source,int destination){
	vec[source].pb(destination);
	vec[destination].pb(source);
}

void BFSUtil(vector<bool> &visited ,vector<int> vec[],int i){
	list<int> queue;

	visited[i] = true;
	queue.pb(i);

	vector<int> :: iterator it;

	while(!queue.empty()){

		i = queue.front();
		cout<<i<<" ";
		queue.pop_front();

		for(it = vec[i].begin(); it!= vec[i].end(); it++){

			if(visited[*it] == false){
				queue.pb(*it);
				visited[*it] = true;

			}
		}
	}
}

void BFS(vector<int> vec[],int V){

	vector<bool> visited(V,false);

	int total_disconnected_components = 0;
	for(int i=0; i<V; i++){
		if(visited[i] == false){
			BFSUtil(visited,vec,i);
			total_disconnected_components++;
		}
	}
	cout<<endl;
	cout<<total_disconnected_components<<endl;
}

int main(){
	int t;
	cin>>t;

	while(t--){

		int v;
		cin>>v;

		vector<int> graph[v];

		int e;
		cin>>e;
		for(int i=0; i<e; i++){
			int source,destination;
			cin>>source>>destination;
			addEdge(graph,source,destination);
		}
		BFS(graph,v);
	}
	return 0;
}