class queens
{
	static boolean finished = false;
	static final int MAXCANDIDATES = 100;
	static final int NMAX = 100;
	static int solution_count = 0;
	static void backtrack(int a[], int k, int input)
	{
		int c[] = new int [MAXCANDIDATES];
		int ncandidates, i;
		if (is_a_solution(a,k,input))
			process_solution(a,k,input);
		else
		{
			k++;
			ncandidates = construct_candidates(a,k,input,c);
			for (i=0; i<ncandidates; i++) {
				a[k] = c[i];
				make_move(a,k,input);
				backtrack(a,k,input);
				if (finished) return;
				unmake_move(a,k,input);
			}
		}
	}
	static void make_move(int a[],int k,int n)
	{
	}
	static void unmake_move(int a[],int k,int n)
	{
	}
	static void process_solution(int a[],int k, int n)
	{
		solution_count++;
	}
	static boolean is_a_solution(int a[],int k,int n)
	{
		return k==n;
	}
	static int construct_candidates(int a[],int k,int n, int c[])
	{
		int i,j;
		boolean legal_move=true;
		int ret = 0;
		for(i=1;i<=n;i++)
		{
			legal_move=true;
			for(j=1;j<k;j++)
			{
				if(Math.abs(k-j)==Math.abs(i-a[j]))
					legal_move=false;
				if(i==a[j])
					legal_move=false;
			}
			if(legal_move)
			{
				c[ret]=i;
				ret++;
			}
		}
		return ret;
	}
	static public void main(String[] args)
	{
		int a[] = new int[NMAX];
		int i;
		for (i=1; i<=10; i++) 
		{
			solution_count = 0;
			finished = false;
			backtrack(a,0,i);
			System.out.printf("n=%d  solution_count=%d\n",i,solution_count);
		}
	}
}
