/*
dlk0138
Daniel Koelzer
12/1/2021
CSCE 3110 - Assignment 6
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue> 
#include <stack>

using namespace std;

struct vertex {				//Vertex data structure.
	int id = -1;					//ID for identification. Usable as index in Graph vertices vector.
	int distance = -1;				//Distance from root vertex (vertex 1) in BFS.
	int discoveryTime = -1;			//Discovery time for DFS
	int finishingTime = -1;			//Finishing time for DFS
	vector<int> adjacency;			//Adjacency vector to implement graph.
};

class Graph {
	public:
		int discovered = 0;					//Start with 0 vertices discovered. Used in DFS
		bool connected = true;				//Assume graph is connected until proven otherwise.
		vector<vertex*> vertices;			//All vertices
		vector<vertex*> sorted;				//Sorted vertices for output
		vector<bool> visited;				//Visited bool vector.
		vector<bool> recursiveVisited;		//Used for cyclic checking.
		stack<vertex*> Stack;				//Used in topological sort.
		
		bool isCycle();						//Main function to check if a graph has a cycle.
		bool isCycleSub(vertex* v);			//Recursive function to check for cycles.
		bool isConnected();					//BFS implementation for detecting connected graphs
		void breadthFirst();				//BFS
		void depth(vertex* v);				//Recursive function for DFS
		void depthFirst();					//DFS
		void topologicalSort();				//Topological sort using DFS
		void topologicalSortSub(vertex* v);	//Recursive function for Topological sort
		void resetGraph();					//Resets visited vector and sorted vector.
};




int main() {
	Graph g;
	string fileName;
	ifstream fileIn;
	
	while(!fileIn.is_open()) {				//File IO handling
		cout << "Enter a filename: ";
		getline(cin,fileName);
		fileIn.open(fileName);
		if(!fileIn.is_open()) {
			cout << "File not found.\n";
		}
	}
	string line;
	while(getline(fileIn,line)) {			//File parsing
		g.vertices.push_back(new vertex());
		stringstream liness;
		liness << line;
		int i = 0;
		liness >> i;
		g.vertices.back()->id = i;
		while(liness >> i) {
			g.vertices.back()->adjacency.push_back(i);
		}
		g.visited.push_back(false);
		g.recursiveVisited.push_back(false);
	}
	
	switch(toupper(fileName[0])) {			//Execution type based on file type. Assumed based on given sample input files. 
		case('B'):
			g.breadthFirst();
			//isConnected is handled in breadthFirst.
			g.isCycle();
			break;
		case('D'):
			g.depthFirst();
			g.isConnected();
			g.isCycle();
			break;
		case('T'):
			g.topologicalSort();
			g.isConnected();
			g.isCycle();
			break;
		default:
			g.breadthFirst();
			g.resetGraph();
			g.depthFirst();
			g.resetGraph();
			g.topologicalSort();
			g.isConnected();
			g.isCycle();
			break;
	}
	
	/*
	
	If the above switch statement yields undesired output for testing, use the following code
	
	g.breadthFirst();
	g.resetGraph();
	g.depthFirst();
	g.resetGraph();
	g.topologicalSort();
	g.isConnected();
	g.isCycle();
	
	*/
	
	return 0;
}

void Graph::resetGraph() {					//Resets visited vector and sorted vector.
	fill(visited.begin(),visited.end(),0);	
	sorted.clear();
}

void Graph::breadthFirst() {				//BFS
	bool cont = true;
	queue<vertex*> q;
	q.push(vertices[0]);
	int d = 0;
	while(cont) {
		if(!q.empty()) {
			int size = q.size();
			for(int i = 0; i < size; i++) {
				if(!visited[q.front()->id-1]) {
					visited[q.front()->id-1] = true;
					q.front()->distance = d;
					for(int i: q.front()->adjacency) {
						q.push(vertices[i-1]);
					}
					sorted.push_back(q.front());
				}
				q.pop();
			}
		} else {	//Account for disconnected vertices
			for(vertex* v : vertices) {
				if(!visited[v->id-1]) {
					visited[v->id-1] = true;
					connected = false;
					sorted.push_back(v);
				}
			}
		}
		
		//check if all nodes have been visited
		cont = false;
		for(bool b: visited) {
			if(!b) {
				cont = true;
				break;
			}
		}
		d++;
	}
	
	for(vertex* v: sorted) {
		cout << v->id << ": ";
		if(v->distance == -1) {
			cout << "inf";
		} else {
			cout << v->distance;
		}
		cout << endl;
	}
	
	cout << "Graph ";
	if(connected) {
		cout << "IS ";
	} else {
		cout << "IS NOT ";
	}
	cout << "connected\n";
}

void Graph::depth(vertex* v) {				//Recursive function for DFS
	if(!visited[v->id-1]) {
		discovered++;
		sorted.push_back(v);
		visited[v->id-1] = true;
		v->discoveryTime = discovered;
	}
	for(int i : v->adjacency) {
		if(!visited[i-1]) {
			vertices[i-1]->discoveryTime = discovered;
			depth(vertices[i-1]);
			vertices[i-1]->finishingTime = discovered;
		}
	}
	discovered++;
	v->finishingTime = discovered;
}

void Graph::depthFirst() {					//DFS
	discovered = 0;
	depth(vertices[0]);
	
	//Account for any disconnected vertices
	for(vertex* v : vertices) {
		if(!visited[v->id-1]) {
			depth(v);
			connected = false;	//Can handle detecting connected graphs. Ignored and instead used isConnected function using BFS.
		}
	}
		
	for(vertex* v: sorted) {
		cout << v->id << ": " << v->discoveryTime << " " << v->finishingTime << endl;
	}
}

bool Graph::isCycle() {						//Main function to check if a graph has a cycle.
	resetGraph();
	for(vertex* v : vertices) {
		if(isCycleSub(v)) {
			cout << "The graph contains a cycle.\n";
			return true;
		}
	}
	cout << "The graph does not contain a cycle.\n";
	return false;
}

bool Graph::isCycleSub(vertex* v) {			//Recursive function to check for cycles.
	if(!visited[v->id]) {
		visited[v->id] = true;
		recursiveVisited[v->id] = true;
		for(int i : v->adjacency) {
			if(!visited[i-1] && isCycleSub(vertices[i-1])) {
				return true;
			}
			else if (recursiveVisited[i-1]) {
				return true;
			}
		}
	}
	recursiveVisited[v->id] = false;
	return false;
}

bool Graph::isConnected() {					//BFS implementation for detecting connected graphs
	resetGraph();
	bool cont = true;
	queue<vertex*> q;
	q.push(vertices[0]);
	while(cont) {
		if(!q.empty()) {
			int size = q.size();
			for(int i = 0; i < size; i++) {
				if(!visited[q.front()->id-1]) {
					visited[q.front()->id-1] = true;
					for(int i: q.front()->adjacency) {
						q.push(vertices[i-1]);
					}
					sorted.push_back(q.front());
				}
				q.pop();
			}
		} else {	//Account for disconnected vertices
			for(vertex* v : vertices) {
				if(!visited[v->id-1]) {
					visited[v->id-1] = true;
					connected = false;
					sorted.push_back(v);
				}
			}
		}
		
		//check if all nodes have been visited
		cont = false;
		for(bool b: visited) {
			if(!b) {
				cont = true;
				break;
			}
		}
	}
	
	cout << "Graph ";
	if(connected) {
		cout << "IS ";
	} else {
		cout << "IS NOT ";
	}
	cout << "connected\n";
}

void Graph::topologicalSortSub(vertex* v) {	//Recursive function for Topological sort
	visited[v->id-1] = true;
	for(int i : v->adjacency) {
		if(!visited[i-1]) {
			topologicalSortSub(vertices[i-1]);
		}
	}
	Stack.push(v);
}

void Graph::topologicalSort() {				//Topological sort using DFS
	for(vertex* v : vertices) {
		if(!visited[v->id-1]) {
			topologicalSortSub(v);
		}
	}
	while(!Stack.empty()) {
		sorted.push_back(Stack.top());
		Stack.pop();
	}
	
	for(vertex* v: sorted) {
		cout << v->id << endl;
	}
}