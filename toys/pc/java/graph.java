import java.util.Scanner;
import java.io.*;

class graph
{
	static final int MAXV = 100;
	static final int MAXDEGREE = 50;
	
	public int edges[][] = new int [MAXV+1][MAXDEGREE];
	public int degree[] = new int [MAXV+1];
	public int nvertices;
	public int nedges;
	
	graph()
	{
		nvertices = nedges = 0;
		for(int i=1;i<=MAXV;i++)
			degree[i] = 0;
	}
	
	void read_graph(boolean directed)
	{
		int x,y;
		Scanner sc = new Scanner(System.in);
		nvertices = sc.nextInt();
		int m = sc.nextInt();
		for(int i=1;i<=m;i++)
		{
			x=sc.nextInt();
			y=sc.nextInt();
			insert_edge(x,y,directed);
		}
	}
	
	void insert_edge(int x, int y, boolean directed)
	{
		if(degree[x]>MAXDEGREE)
			System.out.printf("Warning: insertion (%d, %d) exceeds max degree\n",x,y);
		edges[x][degree[x]] = y;
		degree[x]++;
		if(!directed)
			insert_edge(y,x,true);
		else
			nedges++;
	}
	
	void print_graph()
	{
		for(int i=1;i<=nvertices;i++)
		{
			System.out.printf("%d: ",i);
			for(int j=degree[i]-1;j>=0;j--)
				System.out.printf(" %d",edges[i][j]);
			System.out.printf("\n");
		}
	}
}
