#include <iostream>
#include <fstream>
#include <set>

//#include "ftsoftds/include/d_graph.h"
//#include "ftsoftds/include/d_util.h"

using namespace std;

int main()
{
    //graph with vertices of type char
 //   graph<char> demoGraph;

    set<char> edgeSet;

    ifstream graphIn;

//    graphIn.open("graphIO.dat");
//    graphIn >> demoGraph;

    //edgeSet = demoGraph.getNeighbors('A');

    edgeSet.insert('a'); 
    edgeSet.insert('b');
    edgeSet.insert('c');

    //for ( auto it = mset.begin(); it != mset.end(); it++ )
    //    std::cout << *it;

    cout << "Neighbors of A are: " << endl;
    for(auto n : edgeSet) {
        cout << n << endl;
    }  

    // output the graph
//    cout << demoGraph << endl;

    return 0;
}
