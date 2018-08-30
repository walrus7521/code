class subsets
{
    static boolean finished = false;
    static final int MAXCANDIDATES = 100;
    static final int NMAX = 100;
    static void backtrack(boolean a[], int k, int input) {
        boolean c[] = new boolean [MAXCANDIDATES];
        int ncandidates, i;
        if (is_a_solution(a,k,input))
            process_solution(a,k,input);
        else {
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
    static void make_move(boolean a[],int k,int n) {
    }
    static void unmake_move(boolean a[],int k,int n) {
    }
    static void process_solution(boolean a[],int k, int n) {
        System.out.printf("{");
        for(int i=1;i<=k;i++)
            if(a[i]) System.out.printf(" %d",i);
            System.out.printf(" }\n");
    }
    static boolean is_a_solution(boolean a[],int k,int n) {
        return k==n;
    }
    static int construct_candidates(boolean a[],int k,int n,boolean c[]) {
        c[0] = true;
        c[1] = false;
        return 2;
    }
    static public void main(String[] args) {
        boolean a[] = new boolean[NMAX];
        backtrack(a,0,3);		
    }
}
