#include "graph.h"
#include <iostream>

int main() {
    Graph aGraph("teststuff.txt");
    aGraph.findPath(0,5);
    cout << "Finding the path from node 0 to node 5: " << endl;
    aGraph.dump();

    aGraph.findPath(2,2);
    cout << "Finding the path from node 2 to itself: " << endl;
    aGraph.dump();
    aGraph.findPath(4,0);
    cout << "Finding the path from node 4 to node 0: " << endl;
    aGraph.dump();

    Graph bGraph;
    bGraph.findPath(1,14);
    cout << "Finding the path from node 1 to node 14 in an empty Graph object: " << endl;
    bGraph.dump();

    return 0;
}
