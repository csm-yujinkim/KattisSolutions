# Notes on this problem

There are two subproblems to solve.
The first is to find the shortest path to each vertex in a digraph
from a certain source node to every node in the graph (including
itself, potentially). This is done using the Bellman-Ford algorithm.

Said algorithm can also detect negative cycles, through which
the cost of any path from the source can be reduced indefinitely,
by cycling through it.

However, this problem asks the programmer to also determine
if any node is included in a negative cycle.
This is done by modifying the B-F algorithm to attempt to generate
a minimum spanning tree and if said "tree" contains any cycles.
A modification of the Depth-First Search algorithm can
detect nodes in such a cycle.

