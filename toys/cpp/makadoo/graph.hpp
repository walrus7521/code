#ifndef GRAPH_
#define GRAPH_

// represents elements in the adjacency set
class neighbor
{
    friend bool operator< (const neighbor& lhs, const neighbor& rhs);
    friend bool operator== (const neighbor& lhs, const neighbor& rhs);
public:
    neighbor(int d=0, int w=0){}

    int dest; // index of vert into vinfo props
    int weight; // edge weight

};

// vertex info - map(key = vertex value, value = vertexInfo props index)
//   this class also contains visit info, and is contained within
//   the vertex class
class vertexInfo
{
};

#endif // GRAPH_
