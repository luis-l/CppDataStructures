
#include "DirectedGraph.h"

int main()
{
	DirectedGraph<string> graph;

	graph.addVertex("a");
	graph.addVertex("b");
	graph.addVertex("c");
	graph.addVertex("d");
	graph.addVertex("e");
	graph.addVertex("f");
	graph.addVertex("g");

	graph.addEdge("a","b");
	graph.addEdge("a","e");

	graph.addEdge("b","a");
	graph.addEdge("b","e");
	graph.addEdge("b","c");
	graph.addEdge("b","d");

	graph.addEdge("d","f");
	graph.addEdge("d","a");

	graph.addEdge("e","f");

	graph.addEdge("f","g");
	graph.display();

	graph.removeEdge("z", "y");
	graph.removeVertex("s");

	//should display:
/*
a: b, e,
b: a, e, c, d,
c:
d: f, a,
e: f,
f: g,
g:
*/


	//Show predecessor links after doing a breadth first search:
	cout << "Predeccesor Links" << endl << endl;

	graph.BFS("a");
	graph.displayPredecessorLinks();
	cout << endl;

	graph.BFS("b");
	graph.displayPredecessorLinks();
	cout << endl;

	graph.BFS("c");
	graph.displayPredecessorLinks();
	cout << endl;

	graph.BFS("d");
	graph.displayPredecessorLinks();
	cout << endl;

	graph.BFS("e");
	graph.displayPredecessorLinks();
	cout << endl;

	graph.BFS("f");
	graph.displayPredecessorLinks();
	cout << endl;

	graph.BFS("g");
	graph.displayPredecessorLinks();
	cout << endl;


//should display:
/*
a pred is: NULL
b pred is: a
c pred is: b
d pred is: b
e pred is: a
f pred is: e
g pred is: f

a pred is: b
b pred is: NULL
c pred is: b
d pred is: b
e pred is: b
f pred is: e
g pred is: f

a pred is: NULL
b pred is: NULL
c pred is: NULL
d pred is: NULL
e pred is: NULL
f pred is: NULL
g pred is: NULL

a pred is: d
b pred is: a
c pred is: b
d pred is: NULL
e pred is: a
f pred is: d
g pred is: f

a pred is: NULL
b pred is: NULL
c pred is: NULL
d pred is: NULL
e pred is: NULL
f pred is: e
g pred is: f

a pred is: NULL
b pred is: NULL
c pred is: NULL
d pred is: NULL
e pred is: NULL
f pred is: NULL
g pred is: f

a pred is: NULL
b pred is: NULL
c pred is: NULL
d pred is: NULL
e pred is: NULL
f pred is: NULL
g pred is: NULL
*/

	//Part 3:  Use breadth first search to compute a shortest path
	cout << "shortest path from a to f: " << endl;
	graph.BFS("a");
	graph.shortestPath("a", "f");
	cout << endl;

	return 0;
};
