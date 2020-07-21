/*  James Baker
    7/14/20
    jamesbaker425@gmail.com
*/

#ifndef DGRAPH_H
#define DGRAPH_H

#include <list>
#include <vector>

using namespace std; 
   
// A directed graph class
class DGraph { 
	public:
		DGraph();
		void addVertex(int v);
		void addEdge(int v, int w);
        void deleteEdge(int v, int w);
		void deleteVertex(int v);
        void printGraph();
		void resetVisited();
		void BFS(int source); 
		void DFS(int source);
		void DFShelp(int source);

	private:
		int V;    					// Number of vertices
		vector<int> vertices;		// Vector containing all of our vertex values
		vector<list<int>> adjLists;	// Vector containing adjacency lists
        vector<bool> visited;		// Vector with all vertices' visited status
};

#endif