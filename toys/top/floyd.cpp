#include "util.h"

void floyd()
{
    REP (k, 0, V-1)
        REP (i, 0, V-1)
            REP (j, 0, V-1)
                AdjMatrix[i][j] = min(AdjMatrix[i][j], AdjMatrix[i][k] + AdjMatrix[k][j]);
}

void transitive_closure()
{
    REP (k, 0, V-1)
        REP (i, 0, V-1)
            REP (j, 0, V-1)
                d[i][j] = d[i][j] | (d[i][k] & d[k][j]);
}

void minimax()
{
    REP (k, 0, V-1)
        REP (i, 0, V-1)
            REP (j, 0, V-1)
                AdjMatrix[i][j] = min(AdjMatrix[i][j], max(AdjMatrix[i][k], AdjMatrix[k][j]));
}

int main()
{
    read_graph(DIRECTED);
    //show_dx();
    //transitive_closure();
    //show_dx();
    //show_matrix();
    //floyd(); // output is DX matrix[i][j]: dx i -> j
    //show_matrix();
    show_matrix();
    minimax();
    show_matrix();
}
