#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>
#include <array>
#include <set>

using namespace std;

class Graph
{
    private:
        int nverts;
        int nedges;
        int finished;
        vector< set<int> > adj;
        vector<bool> visited;
        vector<int> parent;
    public:
        Graph(int nverts)
        {
            this->nverts = nverts;
            visited.resize(nverts, false);
            parent.resize(nverts, 0);
            adj.resize(nverts, set<int>());
        }
        ~Graph() {
        }
        void addEdge(int v, int w) {
            adj[v].insert(w);
            adj[w].insert(v);
        }
        void BFS(int s) {
            queue<int> q;
            set<int>::iterator i;
            visited[s] = true;
            q.push(s);
            while (!q.empty())
            {
                s = q.front();
                q.pop();
                for(i = adj[s].begin(); i != adj[s].end(); ++i)
                {
                    if(!visited[*i])
                    {
                        visited[*i] = true;
                        q.push(*i);
                        parent[*i] = s;
                        //cout << "-> " << *i << endl;
                    }
                }
            }
        }
        void init_search() {
            nedges = 0;
            finished = 0;
            for (int i = 1; i <= nverts; i++) {
                parent[i] = -1;
                visited[i] = false;
            }
        }

        void find_path(int start, int end)
        {
            int i;
            if ((start == end) || (end == -1))
                printf("\n%d,", start);
            else {
                find_path(start, parent[end]);
                printf(" %d,", end);
            }
        }

        //Graph getTranspose();
        //bool isConnected();
        void show() {
            int s;
            set<int>::iterator i;
            printf("printing graph...\n");
            for (s = 1; s < nverts; s++) {
                if (adj[s].empty()) continue;
                printf("%02d: ", s);
                for(i = adj[s].begin(); i != adj[s].end(); ++i) {
                    printf(" (%02d), ", *i);
                }
                cout << endl;
            }
        }
};
 
#define BLOCKING '*'
#define OPEN     '.'

typedef struct {
    int key, row, col;
    char val;
} vertex_t;

class Grid
{
    private:
    public:
        int nrows, ncols, nverts;
        Graph *gr;
        vector< vector<vertex_t> > B;
        Grid(int rows, int cols) {
            this->nrows = rows;
            this->ncols = cols;
            B.resize( cols+2 , vector<vertex_t>( rows+2 ) );
            for (int r = 0; r < rows+2; r++) {
                for (int c = 0; c < cols+2; c++) {
                    B[r][c].val = BLOCKING;
                }
            }
            nverts = (nrows+2) * (ncols+2);
            gr = new Graph(nverts);
        }
        ~Grid() {
            delete gr;
        }
        void show() {

            for (int row = 1; row <= nrows; row++) {
                printf("[%03d]: ", row);
                for (int col = 1; col <= ncols; col++) {
                    printf("%c", B[row][col].val);
                }
                printf("\n");
            }
            printf("\n");
            printf("grid of vertices:\n");
            for (int row = 1; row <= nrows; row++) {
                printf("[%03d]: ", row);
                for (int col = 1; col <= ncols; col++) {
                    printf("%03d ", B[row][col].key);
                }
                printf("\n");
            }
            printf("\n");

        }

        int get_maze()
        {
            for (int row = 1; row <= nrows; row++) {
                /* add 1 to loop to grab the carriage return */
                for (int col = 1; col <= ncols+1; col++) {
                    char c = (char) getchar();
                    if (c != OPEN && c != BLOCKING) {
                        continue;
                    }
                    B[row][col].key = ((ncols+2)*row)+col;
                    B[row][col].val = c;
                    B[row][col].row = row;
                    B[row][col].col = col;
                }
            }
            nverts = (nrows+2) * (ncols+2);
            return 0;
        }

};

void grid_to_graph(Grid &g)
{
    int row, col;
    vertex_t vt, vt1, vt2, vt3, vt4, vt5, vt6, vt7, vt8;
    for (row = 1; row <= g.nrows; row++) {
        for (col = 1; col <= g.ncols; col++) {
            vt = g.B[row][col];
            //printf("[%d][%d] => v = %d => %c\n", row, col, vt.key, vt.val); // shows hose mode here
            if (vt.val != BLOCKING) {
                vt1 = g.B[row-1][col-1];
                vt2 = g.B[row-1][col];
                vt3 = g.B[row-1][col+1];
                vt4 = g.B[row][col-1];
                vt5 = g.B[row][col+1];
                vt6 = g.B[row+1][col-1];
                vt7 = g.B[row+1][col];
                vt8 = g.B[row+1][col+1];

                if (vt1.val != BLOCKING) g.gr->addEdge(vt.key, vt1.key);
                if (vt2.val != BLOCKING) g.gr->addEdge(vt.key, vt2.key);
                if (vt3.val != BLOCKING) g.gr->addEdge(vt.key, vt3.key);
                if (vt4.val != BLOCKING) g.gr->addEdge(vt.key, vt4.key);
                if (vt5.val != BLOCKING) g.gr->addEdge(vt.key, vt5.key);
                if (vt6.val != BLOCKING) g.gr->addEdge(vt.key, vt6.key);
                if (vt7.val != BLOCKING) g.gr->addEdge(vt.key, vt7.key);
                if (vt8.val != BLOCKING) g.gr->addEdge(vt.key, vt8.key);
            }
        }
    }
}

int main()
{
    int nrows, ncols, i;
    nrows = ncols = 0;
    while (EOF != scanf("%d %d\n", &nrows, &ncols)) {
        if (nrows == 0 && ncols == 0) break;
        Grid gg(nrows, ncols);
        gg.get_maze();
        gg.show();
        grid_to_graph(gg);
        //gg.gr->show();
        gg.gr->BFS(121);
        gg.gr->find_path(121, 22);
        cout << endl;
        nrows = ncols = 0;
    }

    return 0;
}


