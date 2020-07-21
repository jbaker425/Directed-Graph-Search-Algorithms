/*  James Baker
    7/14/20
    jamesbaker425@gmail.com
*/

#include <iostream>
#include <algorithm>
using namespace std;

#include "dgraph.h"

//Helper function to find the first index of a given element in a vector
//input: a vector to find the index from, and the element whose index we want
//output: the index of the element in the vector or -1 if not found
int indexOf(vector<int> &v, int elem) {
    vector<int>::iterator i = find(v.begin(), v.end(), elem);
    //if iterator doesn't find the element, it will hit the end of the vector
    if (i != v.cend()) {
        return distance(v.begin(), i);
    }
    else {
        return -1;
    }
};

//Helper function to return whether an element is in a vector or not
//input: a vector we are checking, and the element we are looking for in the vector
//output: true if the element is in the vector, false otherwise
bool isIn(vector<int> &v, int elem) {
    for(int i = 0; i < v.size(); i++) {
        if (elem == v[i]) { return true; }
    }
    return false;
};

//Default constructor for our directed graph, sets vertex count to 0
//input: none
//output: an empty directed graph
DGraph::DGraph() { 
	this->V = 0;
}

//Adds a vertex to the graph, updates the count of vertices, the vector of vertices,
//the adjancency lists, and our visited vector
//input: the value of the vertex to be added
//output: the graph will make a space for the vertex in all the graph's vectors
void DGraph::addVertex(int v) {
    cout << "Creating vertex: " << v << endl;
    V++;
    vertices.push_back(v);
    //We want to keep the vertices vector sorted to help the other two vectors stay organzed
    sort(vertices.begin(), vertices.end());
    int n = indexOf(vertices, v);
    list<int> adjList;
    adjLists.insert(adjLists.begin()+n, adjList);
    visited.insert(visited.begin()+n, false);
}

//Adds an edge to the graph, and adds vertices to the graph if any of the given vertices
//are not in the graph
//input: the values of the source vertex and the target vertex
//output: the graph will add to it's adjacency list and potentially it's vertex list with
//any new vertices and edges
void DGraph::addEdge(int v, int w) {
    cout << "Adding edge: (" << v << "->" << w << ")\n";
    if(!isIn(vertices, v)) { addVertex(v); }
    if(!isIn(vertices, w)) { addVertex(w); }
	int i = indexOf(vertices, v);
    adjLists[i].push_back(w); // Add w to v’s list.
    adjLists[i].sort();
}

//Deletes a vertex from the graph
//input: the value of of the vertex to be deleted
//output: the udated graph without the vertex
void DGraph::deleteVertex(int v) {
    cout << "Deleting vertex: " << v << endl;
    int n = indexOf(vertices, v);
    //If the element is in the graph
    if(n != -1) {
        vertices.erase(vertices.begin()+n);
        visited.erase(visited.begin()+n);
        adjLists.erase(adjLists.begin()+n);
        V--;
    }
    else{
        cout << "Vertex " << v << " not found." << endl;
    }
}

//Deletes an edge from the graph if it exists
//input: the source vertex v, and the target vertex w
//output: the updated graph without the edge, or an error message if edge or vertex not found
void DGraph::deleteEdge(int v, int w) {
    cout << "Deleting edge: (" << v << "->" << w << ")\n";
    int n = indexOf(vertices, v);
    if(n != -1) {
        list<int>::iterator i;
        //Look in its adjacency list for the target vertex
        for(i = adjLists[n].begin(); i != adjLists[n].end(); i++) {
            if(*i == w) {
                adjLists[n].erase(i);
                return;
            }
        }
        cout << "Edge was not found in the graph." << endl;
    }
    else {
        cout << "Source vertex was not found in the graph." << endl;
    }
}

//Prints out all the vertices ibn the graph as well as the adjacency lists
//which represent the edges
//input: none
//output: the contents of the graph, vertices and edges (as adjacency lists)
void DGraph::printGraph() {
    cout << "Printing graph ..." << endl;
    //Print the vertices
    cout << "Vertices: ";
    for (int n = 0; n < V; n++) {
        if (n != V-1) 
            cout << vertices[n] << ",  ";
        else
            cout << vertices[n] << endl;
    }
    //Print the non-empty adjancency lists
    list<int>::iterator i;
    for (int n = 0; n < V; n++) {
        if(!adjLists[n].empty()) {
            cout << "Adjacent to vertex " << vertices[n] << ": ";
            for (i = adjLists[n].begin(); i != adjLists[n].end(); ++i) { 
                cout << *i << " ";
            }
            cout << endl;
        }   
    }
}

//Resets the visited vector to false so the search algorithms will work properly
//input: none
//output: the graph with its visited vector all with valus of false
void DGraph::resetVisited() {
    for(int i = 0; i < V; i++) {
        visited[i] = false;
    }
}

//Runs breadth first search on our graph and prints the order of the vertices visited
//input: the starting/source vertex
//output: the printed values, in order of BFS reaching it, of the vertiex values
void DGraph::BFS(int source) { 
	//Initialize the queue used for running BFS
	list<int> queue;
    int n = indexOf(vertices, source);
    int x = -1;
	// Mark the current vertex as visited and enqueue it
	visited[n] = true; 
	queue.push_back(source); 
	list<int>::iterator i;
    //BFS will add vertices to the queue in breadth-first order
	while(!queue.empty()) 
	{ 
		//dequeue the vertex 
		source = queue.front();
        n = indexOf(vertices, source);
		cout << source << " "; 
		queue.pop_front();
		// get all adjacent vertices of popped vertex and process each if not already visited 
		for (i = adjLists[n].begin(); i != adjLists[n].end(); i++) 
		{
            x = indexOf(vertices, *i);
			if (!visited[x] && x != -1) { 
				visited[x] = true; 
				queue.push_back(*i);
			} 
		} 
	}
    cout << endl;
}

//Bootstrap for our DFS function
//input: the value of the starting/source vertex
//output: it calls the DFShelp
void DGraph::DFS(int source) {
    DFShelp(source);
    cout << endl;
}

//Runs depth first search on our graph and prints the order of the vertices visited
//input: the value of the starting/source index
//output: the printed values, in order of DFS reaching it, of the vertiex values
void DGraph::DFShelp(int source) {
    //Grab the adjancency list of the vertex we are visiting
    int n = indexOf(vertices, source);
    visited[n] = true;
    list<int> adjList = adjLists[n];
    //Print the currently visited vertex
    cout << source << " ";
    //Run DFS recursively on every vertex in the adjacency list
    list<int>::iterator i;
    int x;
    for (i = adjList.begin(); i != adjList.end(); i++) {
        x = indexOf(vertices, *i);
        //Only visit the vertices that haven't been visited yet
        if (!visited[x]) {
            DFShelp(*i);
        }
    }    
}
