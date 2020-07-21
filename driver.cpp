/*  James Baker
    7/14/20
    jamesbaker425@gmail.com
*/

#include <iostream>
using namespace std;

#include "dgraph.h"

// main program 
int main() 
{ 
    //Create the graph and populate it with vertices and edges using addEdge()
    DGraph graph = DGraph(); 
    graph.addEdge(0, 3);
    graph.addEdge(0, 6);
    graph.addEdge(3, 2);
    graph.addEdge(3, 5);
    graph.addEdge(3, 8);
    graph.addEdge(2, 1);
    graph.addEdge(6, 4);
    graph.addEdge(5, 7);

    //Show data in graph and run BFS and DFS on it
    graph.printGraph();
    cout << "Breadth First Traversal for given graph (with 0 as starting node): " << endl;
    graph.BFS(0); 
    graph.resetVisited();
    cout << "Depth First Traversal for given graph (with 0 as starting node): " << endl;
    graph.DFS(0);
    graph.resetVisited();

    //Showing off delete function
    graph.deleteEdge(5, 7);
    graph.deleteVertex(7);

    //Run BFS and DFS again
    graph.printGraph();
    cout << "Breadth First Traversal for given graph (with 0 as starting node): " << endl;
    graph.BFS(0); 
    graph.resetVisited();
    cout << "Depth First Traversal for given graph (with 0 as starting node): " << endl;
    graph.DFS(0);
    graph.resetVisited();
   
    return 0; 
}